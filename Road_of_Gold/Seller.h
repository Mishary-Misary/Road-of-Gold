#pragma once

#include"Casket.h"

struct Wallet;

struct Seller
{
	int		walletID;	//�U�荞�ݐ�
	Casket	casket;
	int		target;		//�̔���
	int		progress;	//�i�s�x
	int		period;		//�^�p����

	Seller(int _walletID, Casket _casket, int _period);
	Wallet&	wallet() const;
};