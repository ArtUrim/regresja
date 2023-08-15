#include <stdio.h>
#include "regresja.h"

#define N 10
#define STEPS 5
float buffer[STEPS];

int main()
{
	regresja_init( STEPS, buffer, 0.1f ); 
	for( int i = 0; i < N; i++ )
	{
		float val = regresja( (float)i );
		if( true == regresja_ready() )
		{
			printf( "Iter %d: %f\n", i, val );
		} else {
			printf( "Iter %d, regresja nie gotowa\n", i );
		}
	}

	return 0;

}
