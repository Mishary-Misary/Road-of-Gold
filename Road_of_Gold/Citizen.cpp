#include"Urban.h"
#include"GlobalVariables.h"
#include"JSON.h"


Citizen::Citizen(int _id, int _citizenType, int _joinedUrbanID)
	: citizenType(_citizenType)
	, money(00)
	, timer(Random(0.0, 1.0))
	, joinedUrbanID(_joinedUrbanID)
	, id(_id)
	, price(100)
	, hapiness(0)
	, progress(0)
	, tmr(Random(99) + 100)
{
	incomeLog.resize(100);
}
int		Citizen::avgIncome() const
{
	return int(incomeLog.sum() / double(incomeLog.size()));
}
void	Citizen::update()
{
	auto& u = urbans[joinedUrbanID];

	timer += timeSpeed;
	if (timer >= 1.0)
	{
		timer -= 1.0;

		//転職の判定

		tmr--;
		if (tmr == 0)
		{
			tmr = 100;
			if (RandomBool(0.1) && (u.citizens.count_if([this](Citizen c) { return c.citizenType == citizenType; }) > 1 || u.jobEfficiency[citizenType] == 0.0))
			{
				auto avg = avgIncome();
				//if (avg < 150)
				{
					//citizenType = 0;
				}
				//else
				{
					for (auto i : step(int(cData.size())))
					{
						if (avg < u.avgIncome[i])
						{
							avg = u.avgIncome[i];
							citizenType = i;

							int num = 0;
							int sum = 0;
							for(auto& c: u.citizens)
								if (c.citizenType == i) { num++; sum += c.price; }
							if (num > 0) price = sum / num;
						}
					}
				}
			}
		}

		money = Max(0, money - 50);	//生活費の支払い

		auto& cJob = cData[citizenType].job;

		//仕事が達成可能かどうか判定
		int totalCost = cJob.cost - cJob.wage;
		bool flag = true;
		for (auto& p : cJob.consume)
		{
			if (u.baskets[p.itemID].getNumItem() < p.numConsume) { flag = false; break; }
			totalCost += u.baskets[p.itemID].getCost(p.numConsume);
		}

		//仕事の実行
		progress += u.jobEfficiency[citizenType];
		if (progress >= 1.0)
		{
			progress -= 1.0;
			if (totalCost < money)
			{
				if (flag)	//もし、必要な材料が市場に出ていれば
				{
					//材料の購入
					for (auto& p : cJob.consume)
						u.baskets[p.itemID].buyItem(p.numConsume);

					//商品の販売
					for (auto& p : cJob.product)
						u.baskets[p.itemID].addRing(1 + int(price*Random(1.1, 1.2)), p.numProduct, this);

					//費用の支払い
					addMoney(-totalCost);
				}

				//娯楽としての購買
				Array<Basket*> buyList;	//購買履歴
				for (;;)
				{
					Basket* best = nullptr;	//有力候補
					double	earn = 0.0;		//コスパ
					for (int i = 0; i < int(iData.size()); i++)
					{
						auto& b = u.baskets[i];
						if (!b.rings.isEmpty() && !buyList.any([&b](const Basket* t) {return t == &b; }) && (best == nullptr || iData[i].value / double(b.rings.front().price) > earn))
						{
							earn = iData[i].value / double(b.rings.front().price);
							best = &b;
						}
					}
					if (best != nullptr && best->rings.front().price <= money) {
						money -= best->rings.front().price;
						buyList.emplace_back(best);
						best->buyItem(1);
					}
					else break;
				}
				hapiness = 0;
				for (auto& b : buyList)
				{
					hapiness += iData[b->itemType].value;
				}
				for (int i = 0;; ++i)
					if (1 << i > money) { hapiness += i * 100; break; }
				money = 0;
			}
			else addMoney(60);	//労働者として働く
		}
	}
}

void	Citizen::addMoney(int _amount)
{
	incomeLog.front() += _amount;
	money += _amount;
}