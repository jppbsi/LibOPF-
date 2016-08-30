#include "graph.h"

int main(int argc, char **argv){
	Graph *g = NULL, *tmp = NULL;
        
        g = CreateGraph(100,2);
        DestroyGraph(&g);
	
	g = ReadGraph(argv[1]);
	tmp = CopyGraph(g);
        DestroyGraph(&g);

	WriteGraph(tmp, "temp.opf");
	DestroyGraph(&tmp);

	return 0;
}
