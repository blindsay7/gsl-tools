#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <gsl/gsl_permutation.h>
#include <gsl/gsl_sf_gamma.h>

int
main(int argc, char *argv[]){
	gsl_permutation *P;
	size_t l;

	if(2!=argc){
		return 1;
	}

	l=strlen(argv[1]);

	if(GSL_SF_FACT_NMAX<l){
		printf("String too long\n");
		return 1;
	}

	P=gsl_permutation_calloc(l);
	assert(NULL!=P);

	do{
		size_t *d=gsl_permutation_data(P),i;

		for(i=0;i<l;i++)
			printf("%c",argv[1][d[i]]);

		printf("\n");
	}while(GSL_SUCCESS==gsl_permutation_next(P));

	return 0;
}
