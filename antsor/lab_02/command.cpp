#include "command.h"

command_t *movcom(float dx, float dy)
{
	command_t *com = new command_t;
	if (!com)
		return nullptr;
	com->type = MOVE_COM;
	com->args.movarg.dx = dx;
	com->args.movarg.dy = dy;
	return com;
}

command_t *sclcom(float kx, float ky, Point pm)
{
	command_t *com = new command_t;
	if (!com)
		return nullptr;
	com->type = SCALE_COM;
	com->args.sclarg.kx = kx;
	com->args.sclarg.ky = ky;
	com->args.sclarg.pm = pm;
	return com;
}

command_t *rotcom(int deg, Point pc)
{
	command_t *com = new command_t;
	if (!com)
		return nullptr;
	com->type = ROTATE_COM;
	com->args.rotarg.deg = deg;
	com->args.rotarg.pc = pc;
	return com;
}
