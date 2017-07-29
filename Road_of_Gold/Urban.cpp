#include"Urban.h"
#include"Node.h"
#include"JSON.h"
#include"Route.h"
#include"GlobalVariables.h"

Array<Urban> urbans;
Urban* selectedUrban;

Urban::Urban()
	: id(int(urbans.size()))
	, name(L"")
	, joinedNodeID(-1)
	, timer(0.5 + getPos().mPos.x / TwoPi)
	, day(0)
{
	resource.resize(rData.size());
	jobEfficiency.resize(cData.size());
	avgIncome.resize(cData.size());

	const Array<int> numCitizen = {
		300,//J­Ò
		10,	//Ø±è
		10,	//©|El
		20,	//ël
		10,	//d§Ä®
		5,	//t
		5,	//t
		5,
		5,
	};

	for (int i = 0; i < int(iData.size()); i++) baskets.emplace_back(i, id);
	for (int i = 0; i < int(Min(cData.size(), numCitizen.size())); i++)
		for (int j = 0; j < numCitizen[i]; j++) citizens.emplace_back(int(citizens.size()), i, id);
}
String	Urban::getTimeAsString() const { return  Format(int(timer * 24)).lpad(2, '0') + L":" + Format(int(timer * 24 * 60) % 60).lpad(2, '0'); }
void	Urban::update()
{
	timer += timeSpeed;
	if (timer >= 1.0)
	{
		timer -= 1.0;
		day++;

		//EfficiencyÌXV
		{
			Array<int>	usedResource(rData.size());
			for (auto c : citizens)
				for (auto rID : cData[c.citizenType].job.needResourceID) usedResource[rID]++;

			for (auto i : step(int(cData.size())))
			{
				double efficiency = 1.0;
				for (auto j : cData[i].job.needResourceID)
				{
					if (resource[j] == 0) efficiency = 0.0;
					else if (resource[j] < usedResource[j]) efficiency *= (double(resource[j]) / double(usedResource[j]));
				}
				jobEfficiency[i] = efficiency;
			}
		}

		//AvgIncomeÌC³
		for (auto i : step(int(cData.size())))
		{
			int num = 0;
			int sum = 0;
			for (auto& c : citizens)
			{
				if (c.citizenType == i)
				{
					num++;
					sum += c.avgIncome();
				}
			}
			if (num > 0) avgIncome[i] = sum / num;
		}
		for (auto& c : citizens)
		{
			c.incomeLog.push_front(0);
			c.incomeLog.pop_back();
		}

		//sêì
		for (auto& b : baskets)
		{
			//¿iáº
			for (auto& r : b.rings) r.price = Max(1, int(r.price*0.95));

			//`[gÌXV
			b.chart.push_front(b.tradeLog.isEmpty() ? b.chart.front() : int(b.tradeLog.sum() / double(b.tradeLog.size())));
			b.tradeLog.clear();
			b.chart.pop_back();
		}
		for (auto i : step(int(cData.size())))
		{
			int sum = 0;
			int num = 0;
			for (auto& c : citizens)
			{
				if (c.citizenType == i)
				{
					num++;
					sum += c.money / 10;
					c.money -= c.money / 10;
				}
			}
			if (num > 0)
			{
				for (auto& c : citizens)
					if (c.citizenType == i)
						c.money += sum / num;
			}
		}
	}

	//s¯ÌXV
	for (auto& c : citizens)
		c.update();
}