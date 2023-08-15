#include "regresja.h"

static float regr_val = 0.0f;
static float vals[REGRESS_N] = { 0.0f };
static unsigned last_val = 0;
static unsigned n = 0;

int regresja_init(unsigned n, unsigned delta)
{
	return 0;
}

float regresja( float val );
