/*!
 * Self-growing array of double values
 */

#ifndef _DOUBLE_ARRAY_H_
#define _DOUBLE_ARRAY_H_


#include <sys/types.h>


/*!
 * Structure to hold an array of doubles and required accounting information.
 */
typedef struct {
    /*! Simple c-array of doubles. */
    double *values;
    /*! Number of values stored in array. */
    u_int32_t count;
    /*! Capacity of array. */
    u_int32_t capacity;
} Double_Array;


Double_Array * double_array_new( void );
Double_Array * double_array_add( Double_Array *, double );
void double_array_free( Double_Array * );
double double_array_get( const Double_Array *, size_t );
size_t double_array_size( const Double_Array * );
const double *double_array_data( const Double_Array * );
double *double_array_mut_data( const Double_Array * );

#endif /* _DOUBLE_ARRAY_H_ */
