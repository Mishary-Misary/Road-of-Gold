#include"Planet.h"
#include"Node.h"
#include"BiomeData.h"

void	initPlanet()
{
	//VoronoiMap�̓ǂݍ���
	Image image(L"assets/nodeMap/voronoiMap.png");

	for (auto p : step(image.size()))
	{
		auto& n = nodes.at(image[p.y][p.x].r + (image[p.y][p.x].g << 8) + (image[p.y][p.x].b << 16));

		image[p.y][p.x] = n.color;
	}

	//mapTexture�ɓK�p
	planet.mapTexture = Texture(image);
	Log(L"MapTextrue�̍쐬������");
}