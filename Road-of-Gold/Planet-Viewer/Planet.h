#pragma once

struct Node;

//���R���̐����ƃ}�b�v��̎��_�ړ����s��
struct Planet
{
	DynamicTexture mapTexture;
	Texture outlineTexture;

	Planet();
	bool	loadVoronoiMap();
	void	generateBiome();
};

extern Planet planet;