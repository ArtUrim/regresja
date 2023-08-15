#include "regresja.h"

enum regresja_state {
	Uninitialized = 0,
	Initialized,
	Filled
};

static struct {
	float regr_val;
	float * buffer;
	float delta;
	unsigned last_val;
	unsigned n;
	float sxy;
	float sy;
	float coeff_sy;
	enum regresja_state reg_state;
	
} regresja_config = {0};

int regresja_init(unsigned n, float * buffer, float delta)
{
	regresja_config.regr_val = 0.0f;
	regresja_config.buffer = buffer;
	regresja_config.delta = 12.0f/(delta*n*(n*n-1));
	regresja_config.last_val = 0;
	regresja_config.n = n;
	regresja_config.sxy = 0.0f;
	regresja_config.sy = 0.0;
	regresja_config.coeff_sy = (float)(n+1)*0.5f;
	regresja_config.reg_state = Initialized;
	return 0;
}

float regresja( float val )
{
	if( regresja_config.reg_state == Uninitialized )
	{
		return 0.0f;
	}
	else if( regresja_config.reg_state == Initialized )
	{
		regresja_config.buffer[regresja_config.last_val] = val;
		regresja_config.sy  += val;
		regresja_config.sxy += val*(regresja_config.last_val+1);
	} else {
		regresja_config.sxy -= regresja_config.sy;
		regresja_config.sxy += regresja_config.n*val;

		regresja_config.sy  += val;
		regresja_config.sy  -= regresja_config.buffer[regresja_config.last_val];
		regresja_config.buffer[regresja_config.last_val] = val;
	}

	regresja_config.last_val++;
	if( regresja_config.last_val == regresja_config.n ) 
	{
		if( regresja_config.reg_state == Initialized )
		{
			regresja_config.reg_state = Filled;
		}

		regresja_config.last_val = 0;
	}

	if( regresja_config.reg_state == Filled )
	{
		regresja_config.regr_val = regresja_config.delta *
			( regresja_config.sxy - regresja_config.coeff_sy*regresja_config.sy);
	}
	return regresja_config.regr_val;
}

bool regresja_ready()
{
	if( regresja_config.reg_state == Filled )
		return true;

	return false;
}
