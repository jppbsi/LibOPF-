/*
  Copyright (C) <2016> <Alexandre Xavier Falco and Joo Paulo Papa>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  please see full copyright in COPYING file.
  -------------------------------------------------------------------------
  written by A.X. Falco <afalcao@ic.unicamp.br> and by J.P. Papa
  <papa.joaopaulo@gmail.com>, Aug 30th 2016

  This program is a collection of functions to manage the Optimum-Path Forest (OPF)
  classifier.
*/

#include "heap.h"

/*--------- Memory Allocation -------------*/
/* It creates a heap.
Parameters:
n: number of heap nodes
cost: array with the costs of each node */
Heap *CreateHeap(int n, float *cost){
    if(n < 1 || !cost) Error("Invalid input", "CreateHeap");
    
    Heap *H = NULL;
    int i;
    
    H = (Heap *) malloc(sizeof(Heap));
    if(H){
        H->n = n;
        H->cost = cost;
        H->color = NULL; H->color = (char *)malloc(sizeof(char)*n);
        H->pixel = NULL; H->pixel = (int *)malloc(sizeof(int)*n);
        H->pos = NULL; H->pos = (int *)malloc(sizeof(int)*n);
        H->last = -1;
        H->removal_policy = MINVALUE;
        
        if (!H->color || !H->pos || !H->pixel) Error("Cannot allocate memory space","CreateHeap");
        
        for (i = 0; i < H->n; i++){
            H->color[i] = WHITE;
            H->pos[i] = -1;
            H->pixel[i] = -1;
    }
  }else Error("Cannot allocate memory space","CreateHeap");

  return H;
}

/* It deallocates a heap.
Parameters:
H: pointer to the heap */
void DestroyHeap(Heap **H){
    Heap *aux = *H;
  
    if(!aux) Error("Invalid input", "DestroyHeap");
    
    if(aux->pixel) free(aux->pixel);
    if (aux->color) free(aux->color);
    if (aux->pos) free(aux->pos);
    free(aux);
    *H = NULL;
}

/*--------- Auxiliary Functions -------------*/
/* It resets the heap.
Parameters:
H: heap to be reset */
void ResetHeap(Heap *H){
    int i;
    
    if(!H) Error("Invalid input", "ResetHeap");
    
    for(i = 0; i < H->n; i++) {
        H->color[i] = WHITE;
        H->pos[i]   = -1;
        H->pixel[i] = -1;
    } 
    H->last = -1;
}

/* It sets the removal policy.
Parameters:
H: heap
policy: 0 is MINVALUE and 1 is MAXVALUE */
void SetRemovalPolicyHeap(Heap *H, char policy){
    if(!H) Error("Invalid input", "SetRemovalPolicyHeap");
    
    if(H->removal_policy != policy){
        H->removal_policy = policy;
        ResetHeap(H);
    }
}

/* It verifies whether the heap is full or not.
Parameters:
H: heap */
char IsFullHeap(Heap *H){
    if(!H) Error("Invalid input", "IsFullHeap");
  
    if(H->last == (H->n - 1)) return 1;
    else return 0;
}

/* It verifies whether the heap is empty or not.
Parameters:
H: heap */
char IsEmptyHeap(Heap *H){
    if(!H) Error("Invalid input", "IsEmptyHeap");
    
    if(H->last == -1) return 1;
    else return 0;
}

/* It goes upwards in the heap.
Parameters:
H: heap
i: id of the heap node */
void GoUpHeap(Heap *H, int i){
    if(!H || i < 0) Error("Invalid input", "GoUpHeap");
    
    int j = HEAP_DAD(i);

    if(H->removal_policy == MINVALUE){
        while ((i > 0) && (H->cost[H->pixel[j]] > H->cost[H->pixel[i]])){
            Change(&H->pixel[j], &H->pixel[i]);
            H->pos[H->pixel[i]] = i;
            H->pos[H->pixel[j]] = j;
            i = j;
            j = HEAP_DAD(i);
        }      
    }
    else{ /* removal_policy == MAXVALUE */
        while ((i > 0) && (H->cost[H->pixel[j]] < H->cost[H->pixel[i]])){
            Change(&H->pixel[j], &H->pixel[i]);
            H->pos[H->pixel[i]] = i;
            H->pos[H->pixel[j]] = j;
            i = j;
            j = HEAP_DAD(i);
        }
    }
}

/* It goes downwards in the heap.
Parameters:
H: heap
i: id of the heap node */
void GoDownHeap(Heap *H, int i){
    if(!H || i < 0) Error("Invalid input", "GoDownHeap");
    
    int j, left = HEAP_LEFTSON(i), right = HEAP_RIGHTSON(i);

    j = i;
    if(H->removal_policy == MINVALUE){
        if((left <= H->last) && (H->cost[H->pixel[left]] < H->cost[H->pixel[i]]))
            j = left;
        if((right <= H->last) && (H->cost[H->pixel[right]] < H->cost[H->pixel[j]]))
            j = right;
    }
    else{ /* removal_policy == MAXVALUE */
        if((left <= H->last) && (H->cost[H->pixel[left]] > H->cost[H->pixel[i]]))
            j = left;
        if((right <= H->last) && (H->cost[H->pixel[right]] > H->cost[H->pixel[j]]))
            j = right;
    }

    if(j != i){
        Change(&H->pixel[j], &H->pixel[i]);
        H->pos[H->pixel[i]] = i;
        H->pos[H->pixel[j]] = j;
        GoDownHeap(H, j);
    }
}

/* It inserts a new heap node p.
Parameters:
H: heap
p: identifier of the new node to be inserted */
char InsertHeap(Heap *H, int p){
    if(!H || p < 0) Error("Invalid input", "InsertHeap");
    
    if(!IsFullHeap(H)){
        H->last++;
        H->pixel[H->last] = p;
        H->color[p] = GRAY;
        H->pos[p] = H->last;
        GoUpHeap(H, H->last);
        return 1;
    }else return 0;
}

/* It removes heap node p.
Parameters:
H: heap
p: identifier of node to be removed */
char RemoveHeap(Heap *H, int *p){
    if(!H || *p < 0) Error("Invalid input", "RemoveHeap");
    
    if (!IsEmptyHeap(H)){
        *p = H->pixel[0];
        H->pos[*p] = -1;
        H->color[*p] = BLACK;
        H->pixel[0] = H->pixel[H->last];
        H->pos[H->pixel[0]] = 0;
        H->pixel[H->last] = -1;
        H->last--;
        GoDownHeap(H, 0);
        return 1;
    }else return 0;
}

/* It updates the heap value at position p.
Parameters:
H: heap
p: position of the heap node
value: new value */
void UpdateHeap(Heap *H, int p, float value){
    if(!H || p < 0) Error("Invalid input", "UpdateHeap");
    
    H->cost[p] = value;
    
    if(H->color[p] == WHITE) InsertHeap(H, p);
    else GoUpHeap(H, H->pos[p]);
}