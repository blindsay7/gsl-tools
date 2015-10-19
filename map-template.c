/*
  Template for FP map style functions
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "double_matrix.h"


Double_Array *get_args( int, const char ** );
bool args_OK( int, const Double_Array *, const Double_Matrix * );
void cleanup( Double_Array *, Double_Matrix * );
void op_and_print( const Double_Array *, const Double_Matrix * );

Double_Matrix *data;

int
main( int argc, char **argv ) {
    Double_Array *args = get_args(argc, (const char **) argv);
    
    data = double_matrix_new();

    yyparse(data);

    if ( ! args_OK( argc, args, data ) ) {
        cleanup( args, data );

        return 1;
    }

    op_and_print( args, data );

    cleanup( args, data );
    
    return 0;
}


Double_Array *
get_args( int argc, const char **argv ) {
    size_t arg_no = 0;
    Double_Array *args = double_array_new( );

    
    for ( arg_no = 1; arg_no < argc; arg_no++ ) {
        /* For error checking.  See strtod() */
        char *endptr = NULL;
        double new_arg = strtod( argv[ arg_no ], &endptr );

        if ( 0 == new_arg && endptr == argv[ arg_no ] ) {
            fprintf( stderr, "Argument (%s) is not a valid number\n", argv[ arg_no ] );

            cleanup( args, NULL );
            return NULL;
        }

        args = double_array_add( args, new_arg );
    }

    return args;
}


void
cleanup( Double_Array *array, Double_Matrix *matrix ) {
    if ( NULL != array ) {
        double_array_free( array );
    }

    if ( NULL != matrix ) {
        double_matrix_free( matrix );
    }
}


bool
args_OK( int argc, const Double_Array *args, const Double_Matrix *data ) {
    if ( 1 == argc ) {
        fprintf( stderr, "Argument required.\n" );
        return false;
    } else if ( NULL == args ) {
        /* message would have been provided in get_args() */
        return false;
    } else if ( 1 != double_array_size( args ) && double_array_size( args ) != double_matrix_width( data ) ) {
        fprintf( stderr, "%s\n%s\n", "Argument-column count mismatch",
            "Supply either 1 argument or column number arguments" );
        return false;
    }

    return true;
}


void
op_and_print( const Double_Array *args, const Double_Matrix *data ) {
    size_t row;
    
    for ( row = 0; row < double_matrix_depth( data ); row++ ) {
        size_t col;

        for ( col = 0; col < double_matrix_width( data ); col++ ) {

            if ( 0 != col ) {
                printf( " " );
            }
            
            printf( "%.10g", double_matrix_get( data, col, row )
#ifdef OP_SHIFT
                +
#elif OP_SCALE
                *
#endif
                ( 1 == double_array_size( args ) ? double_array_get( args, 0 ) : double_array_get( args, col ) )
                    );
        }

        printf( "\n" );
    }

}
