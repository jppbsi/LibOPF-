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
    
    int *label = NULL, *nelems = NULL, i, totelems = 0;
    
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
    
    while(totelems > 0){
        i = RandomInteger(0, src->nnodes-1);
        if(src->node[i].status != NIL){
            
      /*if (nelems[sg->node[i].truelabel]>0){// copy node to sg1
	(*sg1)->node[i1].position = sg->node[i].position;
	for (j=0; j < (*sg1)->nfeats; j++)
	  (*sg1)->node[i1].feat[j]=sg->node[i].feat[j];
	(*sg1)->node[i1].truelabel = sg->node[i].truelabel;
	i1++;
	nelems[sg->node[i].truelabel] = nelems[sg->node[i].truelabel] - 1;
	sg->node[i].status = NIL;
	totelems--;
      }*/
        }
    }


    
    free(label);
    free(nelems);
    
}

/*

  
  
  i1=0;
  while(totelems > 0){
    i = RandomInteger(0,sg->nnodes-1);
    if (sg->node[i].status!=NIL){
      if (nelems[sg->node[i].truelabel]>0){// copy node to sg1
	(*sg1)->node[i1].position = sg->node[i].position;
	for (j=0; j < (*sg1)->nfeats; j++)
	  (*sg1)->node[i1].feat[j]=sg->node[i].feat[j];
	(*sg1)->node[i1].truelabel = sg->node[i].truelabel;
	i1++;
	nelems[sg->node[i].truelabel] = nelems[sg->node[i].truelabel] - 1;
	sg->node[i].status = NIL;
	totelems--;
      }
    }
  }

  i2=0;
  for (i=0; i < sg->nnodes; i++){
    if (sg->node[i].status!=NIL){
      (*sg2)->node[i2].position = sg->node[i].position;
      for (j=0; j < (*sg2)->nfeats; j++)
	(*sg2)->node[i2].feat[j]=sg->node[i].feat[j];
      (*sg2)->node[i2].truelabel = sg->node[i].truelabel;
      i2++;
    }
  }

  free(nelems);
}*/