#pragma once

#include <stdbool.h>

int regresja_init(unsigned n, float * buffer, float delta);
float regresja( float val );
bool regresja_ready();
