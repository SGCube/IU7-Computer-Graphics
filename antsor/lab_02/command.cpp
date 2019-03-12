#include "command.h"

void set_move(command_t *com, double dx, double dy)
{
	if (com)
	{
		com->type = MOVE_COM;
		com->args.movarg.dx = dx;
		com->args.movarg.dy = dy;
	}
}

void set_scale(command_t *com, double kx, double ky, Point pm)
{
	if (com)
	{
		com->type = SCALE_COM;
		com->args.sclarg.kx = kx;
		com->args.sclarg.ky = ky;
		com->args.sclarg.pm = pm;
	}
}

void set_rotate(command_t *com, int deg, Point pc)
{
	if (com)
	{
		com->type = ROTATE_COM;
		com->args.rotarg.deg = deg;
		com->args.rotarg.pc = pc;
	}
}

void save_house(command_t *com, House &house_state)
{
	if (com)
	{
		com->type = ZEROSC_COM;
		com->args.house_state = House(house_state);
	}
}
