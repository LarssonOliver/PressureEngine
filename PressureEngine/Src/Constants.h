#pragma once

#define PRESSURE_TICKRATE 60;
#define PRESSURE_TICKTIME 0.01666f;

#define PRESSRE_FOV 70.f
#define PRESSRE_NEAR_PLANE 0.1f		// If changed, change in waterfragshader.
#define PRESSRE_FAR_PLANE 1000.f	// If changed, change in waterfragshader.

#define PRESSURE_GRAVITY 1.0388f	// pow(9.82, 1/60)