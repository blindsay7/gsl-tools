/*
  Template for applications of single array GSL functions
*/

#include <stdio.h>

#ifdef SINGLE_ARG
# include <stdlib.h>
#endif

#include <gsl/gsl_statistics_double.h>

#ifdef SORT_DATA
# include <gsl/gsl_sort.h>
#endif

#include "columns.h"
#include "double_matrix.h"

#define SINGLE_STEP 1

Double_Matrix *data = NULL;

extern int yyparse(void);

int
main(int argc, char *argv[]) {
	size_t i = 0;
#ifdef SINGLE_ARG
	char *endptr = NULL;
	double arg;
#endif

#ifdef SINGLE_ARG
	if (2 != argc) {
		fprintf(stderr, "Argument required.\n");
		return 1;
	}

	arg = strtod(argv[1], &endptr);

	if (0 == arg && endptr == argv[ 1 ]) {
		fprintf(stderr, "Argument (%s) is not a valid number\n", argv[1]);
		return 1;
	}
#endif

	data = double_matrix_new();

	yyparse();

	for (i = 0; i < double_matrix_width(data); i++) {
#ifdef SORT_DATA
		gsl_sort(double_matrix_col_mut_data(data, i), SINGLE_STEP, double_matrix_depth(data));
#endif

		if (0 != i)
			printf( " " );

		printf("%.10g",
			FUNC_NAME(double_matrix_col_data(data, i), SINGLE_STEP, double_matrix_depth(data)
#ifdef SINGLE_ARG
		    , arg
#endif
			)
		);
	}

	printf("\n");

	double_matrix_free(data);

	return 0;
}
