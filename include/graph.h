#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "common.h"

/*--------- Data types ----------------------------- */
typedef struct _Node {
  int label; /* predicted label */
  int root; /* id of the root node */
  int pred; /* id of predecessor node */
  int truelabel; /* true label (if it is known) */
  int id; /* index in the feature space */
  double *feat; /* features */
}Node;

typedef struct _Graph {
  Node *node; /* sample nodes */
  int nnodes; /* number of nodes (samples) */
  int nfeats; /* number of features */
  int nlabels; /* number of labels (classes) */
  int *ordered_list_of_nodes; /* ordered (increasing order of cost) list of training nodes to speed up classification */
} Graph;

/*----------- Constructor and destructor ------------------------*/
Graph *CreateGraph(int nnodes, int nfeats); /* It allocates the graph. */
void DestroyGraph(Graph **g); /* It deallocates the graph. */

/* ---------- Input/Output --------------------------------------*/
void WriteGraph(Graph *g, char *file); /* It writes the graph to disk. */
Graph *ReadGraph(char *file); /* It reads the graph from an OPF format file. */

/* ---------- Auxiliary --------------------------------------*/
Graph *CopyGraph(Graph *g); /* It copies a graph (it does not copy arcs). */
void CopyNode(Node *cpy, Node *src, int nfeats); /* It copies a given node. */

/*
void SwapSNode(SNode *a, SNode *b); //Swap nodes*/

#endif
