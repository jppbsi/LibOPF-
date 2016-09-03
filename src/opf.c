#include "opf.h"

/*------------ Auxiliary functions ------------------------------ */
/* It splits a source graph into two parts such that the size of the first part is given by a percentual p of samples.
Parameters:
src: source graph to be partitioned
g1: output graph #1
g2: output graph #1
p: percentage from src to be allocayted to g1 */
void opf_SplitSubgraph(Graph *src, Graph **g1, Graph **g2, double p){
    if(!src || p <=0 || p >= 1) Error("Invalid input", "opf_SplitSubgraph");
    
    int *label = NULL, *nelems = NULL, i, j, z, totelems = 0;
    
    label = AllocIntArray(src->nlabels+1);
    nelems = AllocIntArray(src->nlabels+1);
    
    for(i = 0; i < src->nnodes; i++){
        src->node[i].status = 0;
        label[src->node[i].truelabel]++;
    }
    
    for(i = 0; i < src->nnodes; i++)
        nelems[src->node[i].truelabel] = MAX((int)p*label[src->node[i].truelabel], 1);
    
    for (i = 1; i <= src->nlabels; i++)
        totelems+= nelems[i];
        
    *g1 = CreateGraph(totelems, src->nfeats); (*g1)->nlabels = src->nlabels;
    *g2 = CreateGraph(src->nnodes-totelems, src->nfeats); (*g2)->nlabels = src->nlabels;
    
    z = 0;
    while(totelems > 0){
        i = RandomInteger(0, src->nnodes-1);
        if(src->node[i].status != NIL){
            if(nelems[src->node[i].truelabel] > 0){
		(*g1)->node[z].id = src->node[i].id;
		for(j = 0; j < (*g1)->nfeats; j++)
		    (*g1)->node[z].feat[j] = src->node[i].feat[j];
		(*g1)->node[z].truelabel = src->node[i].truelabel;
		z++;
		nelems[src->node[i].truelabel] = nelems[src->node[i].truelabel]-1;
		src->node[i].status = NIL;
		totelems--;
	    }
        }
    }

    z = 0;
    for(i = 0; i < src->nnodes; i++){
	if (src->node[i].status != NIL){
	    (*g2)->node[z].id = src->node[i].id;
	    for (j = 0; j < (*g2)->nfeats; j++)
		(*g2)->node[z].feat[j] = src->node[i].feat[j];
	    (*g2)->node[z].truelabel = src->node[i].truelabel;
	    z++;
	}
    }
    
    free(label);
    free(nelems);
}