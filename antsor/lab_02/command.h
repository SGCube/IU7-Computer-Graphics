#ifndef COMMAND_H
#define COMMAND_H

#include "point.h"

typedef enum { MOVE_COM, SCALE_COM, ROTATE_COM } action_t;

struct command_t
{
	action_t type;
	union
	{
		struct
		{
			float dx;
			float dy;
		} movarg;
		struct
		{
			float kx;
			float ky;
			Point pm;
		} sclarg; 
		struct
		{
			int deg;
			Point pc;
		} rotarg;
	} args;
};

command_t *movcom(float dx, float dy);
command_t *sclcom(float kx, float ky, Point pm);
command_t *rotcom(int deg, Point pc);

#endif // COMMAND_H
