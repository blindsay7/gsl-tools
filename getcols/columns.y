%{
#include <stdbool.h>
#include <stdio.h>

#include "double_matrix.h"

static bool have_first = false;
static unsigned int line_no = 1;
static unsigned int col_no = 0;
extern Double_Matrix *data;

int yylex();

void yyerror(const char *str) {
	fprintf(stderr, "error: %s on line %i\n", str, line_no);
}

int yywrap(void) {
	return 1;
}

%}

%union {
	double val;
}

%token <val> NUMBER

%%

listing: /* empty */
    |
    listing line '\n' {
        col_no = 0;
        line_no++;

        if (!have_first)
            have_first = true;
    }
    ;

line: /* empty */
    |
    line NUMBER {
        if (have_first && col_no >= ((Double_Matrix *) data)->column_count) {
            yyerror("Column count mismatch");
            YYERROR;
        }

        double_matrix_add(data, col_no, $2);

        col_no++;
    }
    ;
