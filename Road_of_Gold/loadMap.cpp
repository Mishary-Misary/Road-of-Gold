#include"Planet.h"
#include"Node.h"
#include"Urban.h"
#include"BiomeData.h"
#include"Incident.h"
#include"Scuttle.h"
#include"Group.h"
#include"Nation.h"

void	loadMap()
{
	//Map�f�[�^�̑I��
	auto items = FileSystem::DirectoryContents(L"Map/");

	for (auto& item : items)
	{
		if (FileSystem::IsDirectory(item) && FileSystem::Exists(item + L"BiomeData.bin"))
		{
			//Planet�f�[�^�̃��[�h
			{
				JSONReader reader(item + L"Planet.json");
				auto j = reader[L"Planet"][L"StartTime"];

				planet.sandglass.timer = j[L"Year"].getOr<int>(0) * 360 + (j[L"Month"].getOr<int>(0) - 1) * 30 + (j[L"Day"].getOr<int>(0) - 1);
			}

			//�o�C�I�[���f�[�^�̃��[�h
			{
				BinaryReader reader(item + L"BiomeData.bin");

				for (auto& n : nodes)
				{
					reader.read(n.biomeType);

					//Node�ɐF�̓K�p
					n.color = n.data().color.lerp(RandomColor(), 0.05);
				}
			}

			//Urbans�f�[�^�̃��[�h
			if (FileSystem::Exists(item + L"Urbans.json"))
			{
				JSONReader reader(item + L"Urbans.json");

				for (auto json : reader[L"Urbans"].arrayView())
					urbans.emplace_back(json);

				for (auto& u : urbans)
					for (auto& b : u.baskets)
						b.joinedUrban = &u;
			}

			//Incidents�f�[�^�̃��[�h
			if (FileSystem::Exists(item + L"Incidents.json"))
			{
				incidentsJson = JSONReader(item + L"Incidents.json");
				for (auto json : incidentsJson[L"Incidents"].arrayView())
					incidents.emplace_back(json);
			}

			//Groups�f�[�^�̃��[�h
			if (FileSystem::Exists(item + L"Groups.json"))
			{
				auto json = JSONReader(item + L"Groups.json");

				for (auto j : json[L"Groups"].arrayView())
					groups.emplace_back(j);
			}

			//Nations�f�[�^�̃��[�h
			if (FileSystem::Exists(item + L"Nations.json"))
			{
				auto json = JSONReader(item + L"Nations.json");

				for (auto j : json[L"Nations"].arrayView())
					nations.emplace_back(j);
				for (auto n : nations)
				{
					for (auto u : n.ownUrbans) u->joinedNation = &n;
				}
			}

			return;
		}
	}
	LOG_ERROR(L"�L����Map�f�[�^��������܂���ł���");
	System::Exit();
}