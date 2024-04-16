#include "MutantBunny.h"
#include "Ecosystem.h"

bool MutantBunny::Feed(Ecosystem* System)
{
	if (System)
	{
		if (System->GetGrassAmount() >= FoodAmount)
		{
			System->ConsumeGrass(FoodAmount);
			return true;
		}
	}

	return false;
}

void MutantBunny::Reproduce(Ecosystem* System)
{

}

void MutantBunny::Kill()
{

}