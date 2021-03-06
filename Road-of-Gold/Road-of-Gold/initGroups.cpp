#include"Group.h"
#include"Vehicle.h"
#include"Urban.h"
#include"VehicleData.h"

void	initGroups()
{
	if (urbans.isEmpty())
	{
		Output << L"都市が存在しないために交易ユニット展開に失敗しました";
		return;
	}

	INIReader iniReader(L"assets/config.ini");
	int numVehicles = iniReader.getOr<int>(L"Groups", L"NumVehicles", 0);

	vehicles.reserve(numVehicles);
	for (int i = 0; i < numVehicles; i++) vehicles.emplace_back(vehicleData.choice().id(), &urbans.choice());
}