#include "opf.h"

int main(int argc, char **argv){
	Graph *g = NULL, *tmp = NULL, *g2 = NULL;
        
        g = CreateGraph(100,2);
        DestroyGraph(&g);
	
	g = ReadGraph(argv[1]);
	tmp = CopyGraph(g);
        DestroyGraph(&g);

	WriteGraph(tmp, "temp.opf");
	DestroyGraph(&tmp);
	
	opf_SplitSubgraph(g, &tmp, &g2, 0.1);
	DestroyGraph(&tmp);
	DestroyGraph(&g2);
	
	return 0;
}
