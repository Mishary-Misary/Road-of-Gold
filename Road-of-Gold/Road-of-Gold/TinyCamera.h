#pragma once
#include"Pos.h"

struct TinyCamera
{
	RectF	restrictedRegion;	//���_�ړ������̈�
	RectF	drawingRegion;		//���z�`��̈�
	RectF	smoothDrawingRegion;//���`��̈�
	Optional<Pos>	gazePoint;	//�����_

	TinyCamera();
	void	update();
	Pos		getCursorPos() const;
	Mat3x2	getMat3x2(int _delta = 0) const;
	Transformer2D createTransformer(int _delta = 0) const;
};

extern TinyCamera tinyCamera;