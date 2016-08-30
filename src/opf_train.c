#include "graph.h"

int main(int argc, char **argv){
	Graph *g = NULL;
        
        g = CreateGraph(100,2);
        DestroyGraph(&g);
	
	g = ReadGraph(argv[1]);
        DestroyGraph(&g);
	
        WriteGraph(g, "temp.opf");
	return 0;
}
