/*!
 * Self-growing matrix of double values
 */

#ifndef _DOUBLE_MATRIX_H_
#define _DOUBLE_MATRIX_H_

#include "double_array.h"


/*!
 * Structure to hold an array of Double_Array objects
 */
typedef struct {
    Double_Array **columns;

    size_t column_count;
} Double_Matrix;


Double_Matrix *double_matrix_new( void );
Double_Matrix *double_matrix_add( Double_Matrix *, size_t, double );
void double_matrix_free( Double_Matrix * );
double double_matrix_get( const Double_Matrix *, size_t, size_t );
size_t double_matrix_width( const Double_Matrix * );
size_t double_matrix_depth( const Double_Matrix * );
const double *double_matrix_col_data( const Double_Matrix *, size_t );
double *double_matrix_col_mut_data( const Double_Matrix *, size_t );


#endif /* _DOUBLE_MATRIX_H_ */
