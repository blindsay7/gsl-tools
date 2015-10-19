/*!
 * Self growing array of Double_Arrays.
 */

#include <assert.h>
#include <stdlib.h>


#include "double_matrix.h"


/*! Starting column count. */
#define INITIAL_COLUMN_COUNT 1


/*!
 * Create a new double matrix.
 *
 * \return Initialize Double_Matrix object.
 */
Double_Matrix *
double_matrix_new( void ) {
    unsigned int i = 0;
    Double_Matrix *newMatrix = malloc( sizeof( Double_Matrix ) );

    assert( NULL != newMatrix );

    newMatrix->columns = malloc( sizeof( Double_Array * ) * INITIAL_COLUMN_COUNT );

    assert( NULL != newMatrix->columns );

    for ( i = 0; i < INITIAL_COLUMN_COUNT; i++ ) {
        newMatrix->columns[ i ] = double_array_new( );
    }

    newMatrix->column_count = INITIAL_COLUMN_COUNT;

    return newMatrix;
}


/*!
  Add a value to a matrix.

  Will grow the matrix if necessary.

  Column index starts at zero.

  \param matrix Matrix to add value to.
  \param column Column to add value to.
  \param new_value Value to insert into matrix.
  \return Pointer to Double_Matrix after value insertion.
*/
Double_Matrix *
double_matrix_add( Double_Matrix *matrix, size_t column, double new_value ) {
    assert( NULL != matrix );

    /* request for a column beyond the matrix capacity */
    if ( column >= matrix->column_count ) {
        unsigned int i = 0;
        /* the matrix will be grown to facilitate entry into the requested column */
        size_t new_capacity = column + 1;
        
        matrix->columns = realloc( matrix->columns,
            sizeof( Double_Array * ) * new_capacity );

        assert( NULL != matrix->columns );

        for ( i = matrix->column_count; i < new_capacity; i++ ) {
            matrix->columns[ i ] = double_array_new( );
        }

        matrix->column_count = new_capacity;
    }

    double_array_add( matrix->columns[ column ], new_value );

    return matrix;
}


/*!
  Free memory associated with a Double_Matrix object.

  \param matrix Double_Matrix to delete.
*/
void
double_matrix_free( Double_Matrix *matrix ) {
    unsigned int i = 0;
    
    assert( NULL != matrix );

    for ( i = 0; i < matrix->column_count; i++ ) {
        double_array_free( matrix->columns[ i ] );
    }

    free( matrix->columns );
    free( matrix );
}


/*!
  Retrieve a value from a double matrix.

  \param matrix The matrix to pull a value from.
  \param column The column to access.
  \param row The row to access.
  \return The requested value.
*/
double
double_matrix_get( const Double_Matrix *matrix, size_t column, size_t row ) {
    assert( NULL != matrix );
    assert( column < matrix->column_count );

    return double_array_get( matrix->columns[ column ], row );
}


/*!
  Retrieve the width (column count) of a matrix.

  \param matrix The matrix to query.
  \return The number of columns.
*/
size_t
double_matrix_width( const Double_Matrix *matrix ) {
    assert( NULL != matrix );

    return matrix->column_count;
}


/*!
  Retrieve the depth (row count) of a matrix.

  \param matrix The matrix to query.
  \return The number of rows.
*/
size_t
double_matrix_depth( const Double_Matrix *matrix ) {
    assert( NULL != matrix );

    return double_array_size( matrix->columns[ 0 ] );
}


/*!
  Retrieve a column of constant data from a matrix.

  \param matrix The matrix to query.
  \param column The column to retrieve.
  \return Pointer to the column data.
*/
const double *
double_matrix_col_data( const Double_Matrix *matrix, size_t column ) {
    assert( NULL != matrix );
    assert( column < matrix->column_count );

    return double_array_data( matrix->columns[ column ] );
}

/*!
  Retrieve a column of mutable data from a matrix.

  \param matrix The matrix to query.
  \param column The column to retrieve.
  \return Pointer to the column data.
*/
double *
double_matrix_col_mut_data( const Double_Matrix *matrix, size_t column ) {
    assert( NULL != matrix );
    assert( column < matrix->column_count );

    return double_array_mut_data( matrix->columns[ column ] );
}
