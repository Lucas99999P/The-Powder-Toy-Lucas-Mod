#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);

void Element::Element_GGOO()
{
	Identifier = "DEFAULT_PT_GGOO";
	Name = "GGOO";
	Colour = PIXPACK(0x8f8f8f);
	MenuVisible = 1;
	MenuSection = SC_LIQUID;
	Enabled = 1;

	Advection = 0.6f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.98f;
	Loss = 0.95f;
	Collision = 0.0f;
	Gravity = 0.1f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 2;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 20;

	Weight = 30;

	DefaultProperties.temp = R_TEMP - 2.0f + 273.15f;
	HeatConduct = 29;
	Description = "Grey goo. Eats everything.";

	Properties = TYPE_LIQUID|PROP_LIFE_DEC|PROP_NEUTPASS;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = 0.05f;
	LowTemperatureTransition = PT_GGOS;
	HighTemperature = 5000f;
	HighTemperatureTransition = PT_FIRE;

	Update = &update;
}

static int update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry;
	for (rx=-1; rx<2; rx++)
		for (ry=-1; ry<2; ry++)
			if (BOUNDS_CHECK && (rx || ry))
			{
				r = pmap[y+ry][x+rx];
				if (!r)
					continue;
				if (TYP(r) != PT_GGOO && TYP(r) != PT_DMND)
				{
					if (TYP(r) == PT_PROT)
				{
					if (surround_space && RNG::Ref().chance(10 + int(sim->pv[(y+ry)/CELL][(x+rx)/CELL]), 100))
					{
						sim->create_part(i, x, y, PT_GGOO);
						return 1;
					}
					else if (!(rndstore & 0x7))
					{
						if (TYP(r) != PT_PROT)
						{
							parts[ID(r)].tmp2 = TYP(r);
							parts[ID(r)].tmp3 = 0;
							if (parts[i].tmp4)
							{
								parts[ID(r)].tmp4 = parts[i].tmp4 + 1;
							}
							else
							{
								parts[ID(r)].tmp4 = 0;
								sim->part_change_type(ID(r), x+rx, y+ry, PT_GGOO);
							}
						}
					}
				}
			}
	return 0;
}
