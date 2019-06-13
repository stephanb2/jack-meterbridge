#ifndef MAIN_H
#define MAIN_H

#include <SDL.h>
#include <jack/jack.h>

#define MAX_METERS 32
/*
#define MET_VU  1 // The meter display type
#define MET_PPM 2
#define MET_DPM 3
#define MET_JF  4
#define MET_SCO 5
*/

enum meterType {
	MET_VU = 1,
	MET_PPM = 2,
	MET_DPM = 3,
	MET_JF = 4,
	MET_SCO = 5
};

extern SDL_Surface *screen, *meter, *meter_buf;
extern SDL_Rect win, dest[MAX_METERS];

extern jack_port_t *input_ports[MAX_METERS];
extern jack_port_t *output_ports[MAX_METERS];

extern int num_meters;
extern int num_scopes;
extern int meter_freeze;
extern float env[MAX_METERS];

extern float bias;

#endif
