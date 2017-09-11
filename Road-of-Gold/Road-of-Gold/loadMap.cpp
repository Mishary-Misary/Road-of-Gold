#include"Planet.h"
#include"Node.h"
#include"Urban.h"
#include"BiomeData.h"
#include"Incident.h"
#include"Scuttle.h"
#include"Group.h"
#include"Nation.h"
#include"UI.h"

void	selectMap()
{
	auto items = FileSystem::DirectoryContents(L"assets/map/").filter([](const FilePath& _path) {
		return FileSystem::IsDirectory(_path) && FileSystem::Exists(_path + L"BiomeData.bin");
	});
	if (items.isEmpty())
	{
		LOG_ERROR(L"�g�p�\�ȃ}�b�v�����݂��܂���");
		System::Exit();
		return;
	}


	for (;;)
	{
		(*ui.fonts[32])(L"�g�p����}�b�v��I�����Ă�������").draw();
		for (int i = 0; i < int(items.size()); i++)
		{
			Rect rect(0, 48 + i * 48, Window::Size().x, 48);
			rect.draw(rect.mouseOver() ? ColorF(Palette::White, 0.5) : Color(0, 0)).drawFrame(2, 0, Palette::White);
			(*ui.fonts[32])(FileSystem::BaseName(items[i])).draw(0, 48 + i * 48);
			if (rect.leftClicked())
			{
				loadMap(items[i]);
				return;
			}
		}
		if (!System::Update()) return;
	}
}
void	loadMap(const FilePath& _path)
{
	//Planet�f�[�^�̃��[�h
	{
		JSONReader reader(_path + L"Planet.json");
		auto j = reader[L"StartTime"];

		planet.sandglass.timer = j[L"Year"].getOr<int>(0) * 360 + (j[L"Month"].getOr<int>(1) - 1) * 30 + (j[L"Day"].getOr<int>(1) - 1);
	}

	//�o�C�I�[���f�[�^�̃��[�h
	{
		BinaryReader reader(_path + L"BiomeData.bin");

		for (auto& n : nodes)
		{
			reader.read(n.biomeType);

			//Node�ɐF�̓K�p
			n.color = n.data().color.lerp(RandomColor(), 0.05);
		}
	}

	//MapImage�̍쐬or�ǂݍ���
	{
		if (FileSystem::Exists(_path + L"MapImage.png"))
		{
			planet.mapTexture = Texture(_path + L"MapImage.png");
		}
		else
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
		}
	}

	//Urbans�f�[�^�̃��[�h
	if (FileSystem::Exists(_path + L"Urbans.json"))
	{
		JSONReader reader(_path + L"Urbans.json");

		for (auto json : reader.arrayView())
			urbans.emplace_back(json);

		for (auto& u : urbans)
			for (auto& b : u.baskets)
				b.joinedUrban = &u;
	}

	//Incidents�f�[�^�̃��[�h
	if (FileSystem::Exists(_path + L"Incidents.json"))
	{
		incidentsJson = JSONReader(_path + L"Incidents.json");
		for (auto json : incidentsJson.arrayView())
			incidents.emplace_back(json);
	}

	//Groups�f�[�^�̃��[�h
	if (FileSystem::Exists(_path + L"Groups.json"))
	{
		auto json = JSONReader(_path + L"Groups.json");

		for (auto j : json.arrayView())
			groups.emplace_back(j);
	}

	//Nations�f�[�^�̃��[�h
	if (FileSystem::Exists(_path + L"Nations.json"))
	{
		auto json = JSONReader(_path + L"Nations.json");

		for (auto j : json.arrayView())
			nations.emplace_back(j);
		for (auto n : nations)
		{
			for (auto u : n.ownUrbans) u->joinedNation = &n;
		}
	}
}