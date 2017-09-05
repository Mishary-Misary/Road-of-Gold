#include"BiomeData.h"
#include"EnergyData.h"
#include"VehicleData.h"
#include"ItemData.h"
Array<EnergyData>	energyData;
Array<BiomeData>	biomeData;
Array<VehicleData>	vehicleData;
Array<ItemData>		itemData;

int		BiomeData::id() const { return int(this - &biomeData.front()); }
int		EnergyData::id() const { return int(this - &energyData.front()); }
int		VehicleData::id() const { return int(this - &vehicleData.front()); }
int		ItemData::id() const { return int(this - &itemData.front()); }

void	loadData()
{
	JSONReader json;

	json.open(L"Assets/ItemData.json");
	for (auto j : json[L"ItemData"].arrayView())
		itemData.emplace_back(j);
	Log(L"ItemData�̓ǂݍ��݊��� size = ", itemData.size());

	json.open(L"Assets/BiomeData.json");
	for (auto j : json[L"BiomeData"].arrayView())
		biomeData.emplace_back(j);
	Log(L"BiomeData�̓ǂݍ��݊��� size = ", biomeData.size());

	json.open(L"Assets/EnergyData.json");
	for (auto j : json[L"EnergyData"].arrayView())
		energyData.emplace_back(j);
	Log(L"EnergyData�̓ǂݍ��݊��� size = ", energyData.size());

	json.open(L"Assets/VehicleData.json");
	for (auto j : json[L"VehicleData"].arrayView())
		vehicleData.emplace_back(j);
	Log(L"VehicleData�̓ǂݍ��݊��� size = ", vehicleData.size());
}

BiomeData::BiomeData(const JSONValue& _json)
	: name(_json[L"Name"].getOr<String>(L""))
	, color(_json[L"Color"].getOr<String>(L"#FFFFFF"))
	, movingCost(_json[L"MovingCost"].getOr<double>(1.0))
	, isSea(_json[L"IsSea"].getOr<bool>(false))
{}
EnergyData::EnergyData(const JSONValue& _json)
	: name(_json[L"Name"].getOr<String>(L""))
{}
ItemData::ItemData(const JSONValue& _json)
	: name(_json[L"Name"].getOr<String>(L""))
	, value(_json[L"Value"].getOr<int>(0))
	, color(_json[L"Color"].getOr<String>(L"#FFFFFF"))
	, icon(_json[L"Icon"].getOr<String>(L""))
{}
VehicleData::VehicleData(const JSONValue& _json)
	: name(_json[L"Name"].getOr<String>(L""))
	, speed(_json[L"Speed"].getOr<double>(1.0))
	, volume(_json[L"Volume"].getOr<int>(100))
	, range(_json[L"Range"].getOr<double>(1.0))
	, isShip(_json[L"IsShip"].getOr<bool>(false))
{}
EnergyData*	getEnergyData(const String& _name)
{
	for (auto& e : energyData)
	{
		if (e.name == _name) return &e;
	}
	return nullptr;
}
BiomeData*	getBiomeData(const String& _name)
{
	for (auto& e : biomeData)
	{
		if (e.name == _name) return &e;
	}
	return nullptr;
}
ItemData*	getItemData(const String& _name)
{
	for (auto& e : itemData)
	{
		if (e.name == _name) return &e;
	}
	return nullptr;
}
VehicleData*	getVehicleData(const String& _name)
{
	for (auto& e : vehicleData)
	{
		if (e.name == _name) return &e;
	}
	return nullptr;
}
int	getEnergyType(const String& _name)
{
	for (auto& e : energyData)
	{
		if (e.name == _name) return e.id();
	}
	return -1;
}
int	getBiomeType(const String& _name)
{
	for (auto& e : biomeData)
	{
		if (e.name == _name) return e.id();
	}
	return -1;
}
int	getItemType(const String& _name)
{
	for (auto& e : itemData)
	{
		if (e.name == _name) return e.id();
	}
	return -1;
}
int	getVehicleType(const String& _name)
{
	for (auto& e : vehicleData)
	{
		if (e.name == _name) return e.id();
	}
	return -1;
}