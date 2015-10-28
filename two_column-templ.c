/*
  Template for GSL functions which operate on X-Y value pairs
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#if defined(OP_FITLINE)
#define OP_LINEST
#define OP_CORRELATION
#endif

#if defined(OP_LINEST)
# include <gsl/gsl_fit.h>
#endif
#if defined(OP_CORRELATION)
# include <gsl/gsl_statistics_double.h>
#endif

#include "double_matrix.h"

#define SINGLE_STEP 1
#define X_DATA 0
#define Y_DATA 1


#if defined(OP_LINEST)
typedef struct {
	double C0;
	double C1;
	double COV00;
	double COV01;
	double COV11;
	double SUMSQ;
} Fit_Data;


Fit_Data *get_fit_data(const Double_Matrix *);
double get_estimate(const Fit_Data *, double);
#endif /* defined(OP_LINEST) */

extern int yyparse(void *);

Double_Matrix *data = NULL;

int
main(int argc, char *argv[]) {
	/*size_t i = 0;*/
#if defined(SINGLE_ARG)
	char *endptr = NULL;
	double arg;
#endif
#if defined(OP_LINEST)
	Fit_Data *fit_data = NULL;
#endif
#if defined(OP_CORRELATION)
	double correlation = 0.0;
#endif


#if defined(SINGLE_ARG)
	if (2 == argc) {
		arg = strtod(argv[ 1 ], &endptr);

		if (0 == arg && endptr == argv[1]) {
			fprintf(stderr, "Argument (%s) is not a valid number\n", argv[ 1 ]);
			return 1;
		}
	} else {
		fprintf(stderr, "Argument required\n");
		return 1;
	}
#else
	if (1 != argc) {
		fprintf(stderr, "No argument required.\n");
		return 1;
	}
#endif

	data = double_matrix_new();

	yyparse(data);

	if (2 != double_matrix_width(data)) {
		fprintf(stderr, "Must provide X data in column 1 and Y data in column 2\n");

		double_matrix_free(data);

		return 1;
	}

#if defined(OP_LINEST)
	fit_data = get_fit_data(data);

#if defined(OP_FITLINE)
	printf("m:%.10g\nb:%.10g\nR²:", fit_data->C1, fit_data->C0);
#else
	printf("%.10g\n", get_estimate(fit_data, arg));
#endif /* defined(OP_FITLINE) */

	free(fit_data);
#endif /* defined(OP_LINEST) */
#if defined(OP_CORRELATION)
	correlation = gsl_stats_correlation(double_matrix_col_data(data, X_DATA), SINGLE_STEP,
	    double_matrix_col_data(data, Y_DATA), SINGLE_STEP,
	    double_matrix_depth(data));

	printf("%.10g\n", correlation);
#endif

	double_matrix_free(data);

	return 0;
}

#if defined(OP_LINEST)
Fit_Data *
get_fit_data(const Double_Matrix *matrix) {
	Fit_Data *result = malloc(sizeof(Fit_Data));

	assert(NULL != result);

	gsl_fit_linear(double_matrix_col_data(matrix, X_DATA), SINGLE_STEP,
		double_matrix_col_data(matrix, Y_DATA), SINGLE_STEP,
		double_matrix_depth(matrix),
		&result->C0,
		&result->C1,
		&result->COV00,
		&result->COV01,
		&result->COV11,
		&result->SUMSQ);

	return result;
}


double
get_estimate(const Fit_Data *eqn, double x) {
	double y, y_error;

	gsl_fit_linear_est(x, eqn->C0, eqn->C1, eqn->COV00, eqn->COV01, eqn->COV11, &y, &y_error);

	return y;
}
#endif /* defined(OP_LINEST) */
