#pragma once

#include"Casket.h"
#include"Export.h"

struct Wallet;
struct VehicleData;
struct Fleet;
struct Pos;
struct Urban;
struct Route;

enum struct Code
{
	Move,	//引数のIDの都市に移動
	Jump,	//引数の番地にジャンプ
	Wait,	//一日休止
	Buy,
	Sell,
	MVol,	//最大容量
};

struct Vehicle
{
	int		vehicleType;
	int		walletID;
	Casket	cargo;
	double	routeProgress;
	double	sleepTimer;
	Urban*	nowUrban;
	Route*	route;
	Export	exportLog;
	bool	stopFlag;	//trueならば事業を中断
	Optional<int>	topPrice;	//購入最高価格

	int		maxVolume;
	int		reader;
	double	timer;	//運用期間
	double	period;	//一周するのに要する時間
	Array<std::pair<Code, int>> chain;

	Vehicle(int _vehicleType, Urban* _nowUrban);
	VehicleData&	data() const;
	Vec2	pos() const;
	Wallet&	wallet() const;
	bool	mouseOver() const;
};

extern Array<Vehicle> vehicles;

void	updateVehicles();
void	drawVehicles();