#include "regresja.h"

int regresja_init(RegresjaConfig *pConfig, unsigned n, float * buffer, float delta)
{
	pConfig->regr_val = 0.0f;
	pConfig->buffer = buffer;
	pConfig->delta = 12.0f/(delta*n*(n*n-1));
	pConfig->last_val = 0;
	pConfig->n = n;
	pConfig->sxy = 0.0f;
	pConfig->sy = 0.0;
	pConfig->coeff_sy = (float)(n+1)*0.5f;
	pConfig->reg_state = Initialized;
	return 0;
}

float regresja( RegresjaConfig *pConfig, float val )
{
	if( pConfig->reg_state == Uninitialized )
	{
		return 0.0f;
	}
	else if( pConfig->reg_state == Initialized )
	{
		pConfig->buffer[pConfig->last_val] = val;
		pConfig->sy  += val;
		pConfig->sxy += val*(pConfig->last_val+1);
	} else {
		pConfig->sxy -= pConfig->sy;
		pConfig->sxy += pConfig->n*val;

		pConfig->sy  += val;
		pConfig->sy  -= pConfig->buffer[pConfig->last_val];
		pConfig->buffer[pConfig->last_val] = val;
	}

	pConfig->last_val++;
	if( pConfig->last_val == pConfig->n ) 
	{
		if( pConfig->reg_state == Initialized )
		{
			pConfig->reg_state = Filled;
		}

		pConfig->last_val = 0;
	}

	if( pConfig->reg_state == Filled )
	{
		pConfig->regr_val = pConfig->delta *
			( pConfig->sxy - pConfig->coeff_sy*pConfig->sy);
	}
	return pConfig->regr_val;
}

bool regresja_ready( RegresjaConfig *pConfig )
{
	if( pConfig->reg_state == Filled )
		return true;

	return false;
}
