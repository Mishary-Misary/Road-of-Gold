#pragma once
#include"Sandglass.h"

struct Customer
{
	Sandglass	sandgrass;
	int		walletID;
	double	rate;	//�S�J�X�^�}�[���̎����ۗL��

	Customer(double _rate);
	Wallet&	wallet() const;
};