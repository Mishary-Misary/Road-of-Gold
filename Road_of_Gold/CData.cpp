#include"CData.h"
Array<CData> cData = {
	{
		L"�؂���",
		{},
		{
			0,  1, 1000,    100,	//�ؒY
			{}
		}
	},
	{
		L"�S�z�R�J����",
		{},
		{
			1,  1, 1000,    100,	//�S�z��
			{}
		}
	},
	{
		L"����E�l",
		{},
		{
			2,  1, 1000,    0,	//����
			{
				{ 0,  5 },		//�ؒY
				{ 1,  5 }		//�S�z��
			}
		}
	},
	{
		L"�R�m",
		{},
		{
			3,  1, 1000,    0,	//���̗�
			{
				{ 2,  1 }		//����
			}
		}
	},
	{
		L"��ΐE�l",
		{},
		{
			4,  1, 1000,    0,	//���
			{
				{ 3,  1 }		//���̗�
			}
		}
	},
	{
		L"�M��",
		{
			{ 4,  1000, 10000 },//���
			{ 5,   100,  1000 }	//����
		},
		{ -1 }	//���Y�Ȃ�
	},
	{
		L"�p���E�l",
		{
			{ 0,   100,   500 }	//�ؒY
		},
		{ -1 }	//���Y�Ȃ�
	},
	{
		L"����E�l",
		{},
		{
			5,  1, 1000,  100,	//����
			{
				{ 0,  1 },		//�ؒY
				{ 1,  1 }		//�S�z��
			}
		}
	}
};