#pragma once

//����̃}�b�v�ł͏�ɓ���Route���쐬����邱�Ƃ��ۏ؂���Ȃ���΂Ȃ�Ȃ��B

struct Path;
struct Urban;

struct Route
{
	Array<Path*> paths;
	Urban*	fromUrban;
	Urban*	toUrban;
	bool	isSeaRoute;
	double	movingCost;

	Route(Urban* _fromUrban, Urban* _toUrban, Array<Path*> _paths, bool _isSeaRoute, double _movingCost)
		: fromUrban(_fromUrban)
		, toUrban(_toUrban)
		, isSeaRoute(_isSeaRoute)
		, movingCost(_movingCost)
	{
		paths = _paths;
	}
};

extern Array<Route> routes;

void	initRoutes();
void	drawRotues();
void	drawRotue(const Route& _r, const Color& _color);