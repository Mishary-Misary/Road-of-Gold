#pragma once

struct Wallet;
struct CitizenData;

struct Citizen
{
	int		citizenType;
	int		walletID;
	int		targetRevenue;	//目標売り上げ
	double	jobProgress;
	Array<int>	incomeLog;
	double	personality;
	double	jobEfficiency;
	int		avgIncome;

	Citizen(int _citizenType);
	CitizenData&	data() const;
	Wallet&	wallet() const;
};