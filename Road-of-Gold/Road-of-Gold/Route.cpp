#include"Route.h"

void	Route::addVehicle()
{
	//�t���[�g��
	for (auto& r : routes)
	{
		if (r.fromUrban == toUrban && r.toUrban == fromUrban && r.isSeaRoute == isSeaRoute)
		{
			r.numVehicles++;
		}
	}
	numVehicles++;
}
void	Route::pullVehicle()
{
	//�t���[�g��
	for (auto& r : routes)
	{
		if (r.fromUrban == toUrban && r.toUrban == fromUrban && r.isSeaRoute == isSeaRoute)
		{
			r.numVehicles--;
		}
	}
	numVehicles--;
}