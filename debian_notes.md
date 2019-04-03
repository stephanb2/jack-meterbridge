

## Build dependencies

libsdl-dev libsdl-image1.2-dev  libjack-jackd2-dev

TODO: makefile doesn't pick the missing libsdl-image library



vu_meters.c:11:17: error: static declaration of ‘buf_rect’ follows non-static declaration
 static SDL_Rect buf_rect[MAX_METERS];
                 ^~~~~~~~
In file included from vu_meters.c:6:0:
main.h:11:22: note: previous declaration of ‘buf_rect’ was here
 extern SDL_Rect win, buf_rect[MAX_METERS], dest[MAX_METERS];
                      ^~~~~~~~
In file included from vu_meters.c:7:0:
