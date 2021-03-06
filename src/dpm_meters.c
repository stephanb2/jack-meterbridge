#include <math.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_thread.h>

#include "main.h"
#include "find_image.h"
#include "envelopes.h"

int peaks[MAX_METERS];
int ptime[MAX_METERS];
int ovrtime[MAX_METERS];

int iec_scale(float db);

const static int sdl_delay = 80;
const static float decay = 1.0f - 0.08f;

void load_graphics_dpm()
{
	unsigned int i;

	meter = find_image("iec268-18-scale.png");
	meter_buf = find_image("iec268-18-scale.png");

	for (i=0; i<MAX_METERS; i++) {
		peaks[i] = 0;
		ptime[i] = 0;
	}
}

int iec_scale(float db) {
         float def = 0.0f; /* Meter deflection %age */
 
         if (db < -70.0f) {
                 def = 0.0f;
         } else if (db < -60.0f) {
                 def = (db + 70.0f) * 0.25f;
         } else if (db < -50.0f) {
                 def = (db + 60.0f) * 0.35f + 2.5f;
         } else if (db < -40.0f) {
                 def = (db + 50.0f) * 1.00f + 6.0f;
         } else if (db < -30.0f) {
                 def = (db + 40.0f) * 1.45f + 16.0f;
         } else if (db < -20.0f) {
                 def = (db + 30.0f) * 1.95f + 30.5f;
         } else if (db < 0.0f) {
                 def = (db + 20.0f) * 2.50f + 50.0f;
         } else {
                 def = 100.0f;
         }
 
         return (int)(def * 2.16f);
}

int gfx_thread_dpm(void *foo)
{
	unsigned int i;
	int height;
	static float lp[MAX_METERS];
	SDL_Rect r, ovr;
	Uint32 black = SDL_MapRGB(screen->format, 0, 28, 52);
	Uint32 red = SDL_MapRGB(screen->format, 255, 64, 32);
	Uint32 orange = SDL_MapRGB(screen->format, 240, 120, 0);
	Uint32 yellow = SDL_MapRGB(screen->format, 200, 180, 0);

	while (1) {
		for (i=0; i<num_meters; i++) {
			const float peak = env_read(i);
			lp[i] = lp[i] * decay;
			if (peak > lp[i]) lp[i] = peak;
			height = iec_scale(20.0f * log10f(lp[i] * bias));
			r.x = dest[i].x + 7;
			r.y = dest[i].y + 16;
			r.w = 9;
			r.h = 217; //220 - height;
			SDL_FillRect(screen, &r, black);
			ovr.x = r.x;
			ovr.y = dest[i].y + 4;
			ovr.w = r.w;
			ovr.h = 4;
			//SDL_FillRect(screen, &ovr, black);

			r.h = height;
			r.y = dest[i].y + 232 - height; //231 - height
			SDL_FillRect(screen, &r, orange);

			// peak hold and OVR light
			if (height > peaks[i]) {
				peaks[i] = height;
				ptime[i] = 0;
			} else if (ptime[i]++ > 20) {
				peaks[i] = height;
			}
			r.h = 2;
			r.y = dest[i].y + 231 - peaks[i];
			if (r.y < 16) {
				r.y = 16;
			}
			SDL_FillRect(screen, &r, yellow);

			// OVR hold 2x the duration of peak holds
			if (height >= 216) {
				SDL_FillRect(screen, &ovr, red);
				ovrtime[i] =0;
			} else if (ovrtime[i]++ > 40) {
				SDL_FillRect(screen, &ovr, black);
			}

		}
		SDL_UpdateRects(screen, 1, &win);
		SDL_Delay(sdl_delay);
	}

	return 0;
}
