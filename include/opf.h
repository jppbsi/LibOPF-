#ifndef _OPF_H_
#define _OPF_H_

#include <limits.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <float.h>

#include "graph.h"

/*------------ Auxiliary functions ------------------------------ */
void opf_SplitSubgraph(Graph *src, Graph **g1, Graph **g2, double p); /* It splits a source graph into two parts such that the size of the first part is given by a percentual p of samples. */

#endif
