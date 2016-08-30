#include "graph.h"

int main(int argc, char **argv){
	Graph *g = NULL;
        
        g = CreateGraph(100,2);
        DestroyGraph(&g);
        
        return 0;
}