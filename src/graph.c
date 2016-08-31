/*
  Copyright (C) <2016> <Alexandre Xavier Falc‹o and Jo‹o Paulo Papa>

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
  written by A.X. Falc‹o <afalcao@ic.unicamp.br> and by J.P. Papa
  <papa.joaopaulo@gmail.com>, Aug 30th 2016

  This program is a collection of functions to manage the Optimum-Path Forest (OPF)
  classifier.
*/

#include "graph.h"

/*----------- Constructor and destructor ------------------------*/
/* It allocates the graph.
Parameters:
nnodes:number of samples (nodes)
nefeats: number os features (dimensionality of the feature space) */
Graph *CreateGraph(int nnodes, int nfeats){
    Graph *g = NULL;
    int i;
    
    if(nnodes <= 0 || nfeats <= 0) Error("Invalid input", "CreateGraph");
    
    g = (Graph *)malloc(sizeof(Graph));
    g->nnodes = nnodes;
    g->nfeats = nfeats;
    g->ordered_list_of_nodes = (int *) malloc(g->nnodes*sizeof(int));
    g->node = NULL; g->node = (Node *)malloc(g->nnodes*sizeof(Node));
    if(!g->node) Error("Cannot allocate nodes", "CreateGraph");
    
    for(i = 0; i < g->nnodes; i++){
        g->node[i].id = i;
        g->node[i].feat = AllocFloatArray(g->nfeats);
    }
    
    return g;
}

/* It deallocates the graph.
Parameters:
g: graph to be deallocated */
void DestroyGraph(Graph **g){
    Graph *tmp = NULL;
    int i;
    
    tmp = *g;
    
    if(!tmp) Error("Invalid input", "DestroyGraph");
    
    for(i = 0; i < tmp->nnodes; i++)
        free(tmp->node[i].feat);
    free(tmp->node);
    free(tmp->ordered_list_of_nodes);
    free(tmp);
    *g = NULL;
}

/* ---------- Input/Output --------------------------------------*/
/* It writes the graph to disk.
Parameters:
g: input graph
file: output file name */
void WriteGraph(Graph *g, char *file){
    FILE *fp = NULL;
    int i, j;
    
    if(!g || !file) Error("Invalid input", "WriteGraph");

    fp = fopen(file, "wb");
    fwrite(&g->nnodes, sizeof(int), 1, fp);
    fwrite(&g->nlabels, sizeof(int), 1, fp);
    fwrite(&g->nfeats, sizeof(int), 1, fp);
    
    for (i = 0; i < g->nnodes; i++){
        fwrite(&g->node[i].id, sizeof(int), 1, fp);
        fwrite(&g->node[i].truelabel, sizeof(int), 1, fp);
        for (j = 0; j < g->nfeats; j++)
            fwrite(&g->node[i].feat[j], sizeof(float), 1, fp);
    }
    fclose(fp);
}

/* It reads the graph from an OPF format file.
Parameters:
file: input file name */
Graph *ReadGraph(char *file){
    Graph *g = NULL;
    FILE *fp = NULL;
    int i, j, nnodes, nlabels, nfeats;
    char msg[128];
    
    if(!file) Error("Invalid input", "ReadGraph");
    if((fp = fopen(file, "rb")) == NULL){
        sprintf(msg, "%s%s", "Unable to open file ", file);
        Error(msg, "ReadGraph");
    }
    
    if(fread(&nnodes, sizeof(int), 1, fp) != 1) Error("Could not read the number of nodes", "ReadGraph");
    if(fread(&nlabels, sizeof(int), 1, fp) != 1) Error("Could not read the number of labels", "ReadGraph");
    if(fread(&nfeats, sizeof(int), 1, fp) != 1) Error("Could not read the number of features", "ReadGraph");
    
    g = CreateGraph(nnodes, nfeats);
    g->nlabels = nlabels;
    
    for (i = 0; i < g->nnodes; i++){
        if(fread(&g->node[i].id, sizeof(int), 1, fp) != 1) Error("Could not read node position", "ReadGraph");      
        if(fread(&g->node[i].truelabel, sizeof(int), 1, fp) != 1) Error("Could not read node true label", "ReadGraph");

        for (j = 0; j < g->nfeats; j++)
            if(fread(&g->node[i].feat[j], sizeof(float), 1, fp) != 1) Error("Could not read node features", "ReadGraph");	
   }
   fclose(fp);
   
   return g;
}

/* ---------- Auxiliary --------------------------------------*/
/* It copies a graph (it does not copy arcs).
Parameters:
g: graph to be copied
*/
Graph *CopyGraph(Graph *g){
    Graph *cpy = NULL;
    int i;
    
    if(!g) Error("Invalid input", "CopyGraph");
    
    cpy = CreateGraph(g->nnodes, g->nfeats);
    cpy->nlabels = g->nlabels;
    
    for(i = 0; i < g->nnodes; i++){
        CopyNode(&cpy->node[i], &g->node[i], g->nfeats);
        cpy->ordered_list_of_nodes[i] = g->ordered_list_of_nodes[i];
    }
    
    return cpy;   
}

/* It copies a given node.
Parameters:
dest: destiny node
src: source node
nfeats: number of features */
void CopyNode(Node *dest, Node *src, int nfeats){
    if(!src || nfeats < 1) Error("Invalid input", "CopyNode");
        
    memcpy(dest->feat, src->feat, nfeats*sizeof(float));
    dest->label = src->label;
    dest->truelabel = src->truelabel;
    dest->pred = src->pred;
    dest->root = src->root;
    dest->id = src->id;
    dest->status = src->status;
}