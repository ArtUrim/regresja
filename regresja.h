#pragma once

#include <stdbool.h>

enum regresja_state {
	Uninitialized = 0,
	Initialized,
	Filled
};

typedef struct {
	float regr_val;
	float * buffer;
	float delta;
	unsigned last_val;
	unsigned n;
	float sxy;
	float sy;
	float coeff_sy;
	enum regresja_state reg_state;
	
} RegresjaConfig;

int regresja_init(RegresjaConfig *pConfig, unsigned n, float * buffer, float delta);
float regresja( RegresjaConfig *pConfig, float val );
bool regresja_ready( RegresjaConfig *pConfig );
