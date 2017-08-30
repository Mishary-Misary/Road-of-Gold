#include"BiomeData.h"
#include"EnergyData.h"
#include"CitizenData.h"
#include"VehicleData.h"
#include"ItemData.h"

int		BiomeData::id() const { return int(this - &biomeData.front()); }
int		CitizenData::id() const { return int(this - &citizenData.front()); }
int		EnergyData::id() const { return int(this - &energyData.front()); }
int		ItemData::id() const { return int(this - &itemData.front()); }
int		VehicleData::id() const { return int(this - &vehicleData.front()); }

void	loadData()
{
	JSONReader biomeDataJson(L"Assets/BiomeData.json");
	for (auto json : biomeDataJson[L"BiomeData"].arrayView())
		biomeData.emplace_back(json);
	Log(L"BiomeData�̓ǂݍ��݊��� size = ", biomeData.size());

	JSONReader energyDataJson(L"Assets/EnergyData.json");
	for (auto json : energyDataJson[L"EnergyData"].arrayView())
		energyData.emplace_back(json);
	Log(L"EnergyData�̓ǂݍ��݊��� size = ", energyData.size());

	JSONReader citizenDataJson(L"Assets/CitizenData.json");
	for (auto json : citizenDataJson[L"CitizenData"].arrayView())
		citizenData.emplace_back(json);
	Log(L"CitizenData�̓ǂݍ��݊��� size = ", citizenData.size());

	JSONReader vehicleDataJson(L"Assets/VehicleData.json");
	for (auto json : vehicleDataJson[L"VehicleData"].arrayView())
		vehicleData.emplace_back(json);
	Log(L"VehicleData�̓ǂݍ��݊��� size = ", vehicleData.size());

	JSONReader itemDataJson(L"Assets/ItemData.json");
	for (auto json : itemDataJson[L"ItemData"].arrayView())
		itemData.emplace_back(json);
	Log(L"ItemData�̓ǂݍ��݊��� size = ", itemData.size());

}

CitizenData::CitizenData(const JSONValue& _json)
	: name(_json[L"Name"].getOr<String>(L""))
	, wage(_json[L"Wage"].getOr<int>(0))
	, cost(_json[L"Cost"].getOr<int>(0))
	, product(_json[L"Product"])
	, needEnergyType(-1)
{
	//needEnergyType�̎Q��
	for (auto i : step(int(energyData.size())))
	{
		if (energyData[i].name == _json[L"NeedEnergy"].getOr<String>(L""))
		{
			needEnergyType = i;
			break;
		}
	}

}
EnergyData*	getEnergyData(const String& _name)
{
	for (auto& e : energyData)
	{
		if (e.name == _name) return &e;
	}
	return nullptr;
}