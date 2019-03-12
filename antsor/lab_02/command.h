#ifndef COMMAND_H
#define COMMAND_H

#include "point.h"

typedef enum { MOVE, SCALE, ROTATE } action_t;

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

#endif // COMMAND_H
