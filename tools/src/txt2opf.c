#include <stdio.h>
#include <stdlib.h>
#include "opf.h"

int main(int argc, char **argv){
	if (argc != 3){
		fprintf(stderr,"\nusage txt2opf <P1> <P2>\n");
		fprintf(stderr,"\nP1: input file name in the OPF ASCII format");
		fprintf(stderr,"\nP2: output file name in the OPF binary format\n");
		exit(-1);
	}

	fprintf(stderr, "\nProgram to convert files written in the OPF ASCII format to the OPF binary format.");

	FILE *fpIn = NULL,*fpOut = NULL;
	int nnodes, nfeats, nlabels, i, j, id, label;
	char msg[128];
	double aux;

	fpIn = fopen(argv[1],"r");
	fpOut = fopen(argv[2],"wb");

	if(!fpIn){
	    sprintf(msg, "%s%s", "Unable to open file ", argv[1]);
	    Error(msg, "txt2opf");
	}
	
	if(fscanf(fpIn,"%d",&nnodes) != 1) Error("Could not read number of samples", "txt2opf");
	fwrite(&nnodes,sizeof(int),1,fpOut);

	if(fscanf(fpIn,"%d",&nlabels) != 1) Error("Could not read number of classes", "txt2opf");
	fwrite(&nlabels,sizeof(int),1,fpOut);

	if(fscanf(fpIn,"%d",&nfeats) != 1) Error("Could not read number of features", "txt2opf");
	fwrite(&nfeats,sizeof(int),1,fpOut);
	
	for(i = 0; i < nnodes; i++){
		if(fscanf(fpIn,"%d",&id) != 1) Error("Could not read sample id", "txt2opf");
		fwrite(&id,sizeof(int),1,fpOut);
	  
		if(fscanf(fpIn,"%d",&label) != 1) Error("Could not read sample label", "txt2opf");
		fwrite(&label,sizeof(int),1,fpOut);
	  
		for(j = 0; j < nfeats; j++){
			if(fscanf(fpIn,"%lf",&aux) != 1) Error("Could not read sample feature", "txt2opf");
			fwrite(&aux,sizeof(double),1,fpOut);
		}
	}

	fclose(fpIn);
	fclose(fpOut);

	fprintf(stderr,"\nSummary ---");
	fprintf(stderr,"\nNumber of samples: %d",nnodes);
	fprintf(stderr,"\nNumber of classes: %d",nlabels);
	fprintf(stderr,"\nNumber of features: %d",nfeats);
		
	return 0;
}
