#include "graph.h"

int main(int argc, char **argv){
	Graph *g = NULL;
        
        g = CreateGraph(100,2);
        DestroyGraph(&g);
	
	g = ReadGraph(argv[1]);
        DestroyGraph(&g);
	
        g = ReadGraph(argv[1]);
	WriteGraph(g, "temp.opf");
	DestroyGraph(&g);

	return 0;
}
