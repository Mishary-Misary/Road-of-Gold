#pragma once

struct Sandglass
{
	double	timer;

	Sandglass(double _timer = 0);
	bool	update();	//�������t���܂������ꍇtrue

	int		year() const { return int(timer / 360); }
	int		day() const { return int(timer) % 360; }
	int		hour() const { return int(timer * 24) % 24; }
	int		minute() const { return int(timer * 24 * 60) % 60; }
};