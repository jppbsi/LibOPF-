#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "common.h"

/*--------- Data types ----------------------------- */
typedef struct _Node {
  int label; // predicted label
  int root; // id of the root node
  int pred; // id of predecessor node
  int truelabel; // true label (if it is known)
  int id; //index in the feature space
}Node;

typedef struct _Graph {
  Node *node; // sample nodes
  int nnodes; // number of nodes (samples)
  int nfeats;  //number of features
  int nlabels; //number of labels (classes)
} Graph;

/*----------- Constructor and destructor ------------------------*/
Graph *CreateGraph(int nnodes, int nfeats); // It allocates the graph
void DestroyGraph(Graph **sg); // It deallocates the graph

/*void WriteSubgraph(Subgraph *g, char *file); //write subgraph to disk
Subgraph *ReadSubgraph(char *file);//read subgraph from opf format file
Subgraph *CopySubgraph(Subgraph *g);//Copy subgraph (does not copy Arcs)

void CopySNode(SNode *dest, SNode *src, int nfeats); //Copy nodes
void SwapSNode(SNode *a, SNode *b); //Swap nodes*/

#endif
