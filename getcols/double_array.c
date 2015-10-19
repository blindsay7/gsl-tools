/*!
 * Self growing array of double values.
 */

#include <assert.h>
#include <stdlib.h>

#include "double_array.h"

/*! Starting array size. */
#define INITIAL_DOUBLE_ARRAY_SIZE 16


/*!
 * Create a new double array.
 *
 * \return Initialized Double_Array object.
 */
Double_Array *
double_array_new( void ) {
    Double_Array *newArray = malloc( sizeof( Double_Array ) );

    assert( NULL != newArray );

    newArray->values = malloc( sizeof( double ) * INITIAL_DOUBLE_ARRAY_SIZE );

    assert( NULL != newArray->values );

    newArray->count = 0;
    newArray->capacity = INITIAL_DOUBLE_ARRAY_SIZE;

    return newArray;
}

/*!
 * Add a value to an array.
 *
 * Will grow the array if necessary.
 *
 * \param array Array to add value to.
 * \param newValue Value to insert into array.
 * \return Pointer to Double_Array after value insertion.
 */
Double_Array *
double_array_add( Double_Array *array, double newValue ) {

    assert( NULL != array );
    
    if ( array->count == array->capacity ) {
        /* array is full, allocate more memory by doubling capacity */
        array->values = realloc( array->values,
            sizeof( double ) * array->capacity * 2 );

        assert( NULL != array->values );
        
        array->capacity *= 2;
    }

    array->values[ array->count ] = newValue;
    array->count++;
    
    return array;
}


/*!
 * Free memory associated with a Double_Array object.
 *
 * \param array Double_Array to delete.
 */
void
double_array_free( Double_Array *array ) {
    assert( NULL != array );
    
    free( array->values );
    free( array );
}


/*!
  Retrive a value from a double array.

  \param array The array to pull a value from.
  \param index The index into the array.
  \return The selected value.
*/
double
double_array_get( const Double_Array *array, size_t index ) {
    assert( NULL != array );
    assert( index < array->count );

    return array->values[ index ];
}


/*!
  Retrieve the size of an array.

  \param array The array to query.
  \return The number of items in the array.
*/
size_t
double_array_size( const Double_Array *array ) {
    assert( NULL != array );

    return array->count;
}


/*!
  Retrieve the data stored in an array.

  \param array The array to query.
  \return Pointer to the array data.
*/
const double *
double_array_data( const Double_Array *array ) {
    assert( NULL != array );

    return array->values;
}


/*!
  Retrieve the data stored in an array in a mutable form.

  \param array The array to query.
  \return Pointer to the array data.
*/
double *
double_array_mut_data( const Double_Array *array ) {
    assert( NULL != array );

    return array->values;
}
