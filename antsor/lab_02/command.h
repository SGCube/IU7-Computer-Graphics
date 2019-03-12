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

void set_move(command_t *com, float dx, float dy);
void set_scale(command_t *com, float kx, float ky, Point pm);
void set_rotate(command_t *com, int deg, Point pc);

#endif // COMMAND_H
