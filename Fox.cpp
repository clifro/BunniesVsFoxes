#include "Fox.h"
#include "Ecosystem.h"
#include<iostream>

Fox::Fox(Ecosystem* system)
{
	FoodType = EntityType::Grass;
	FoodAmount = 2;
	DeathAge = 10;
	ReproduceAge = 2;
	Age = 0;

	if (system)
	{
		Name = system->RandomName(4);
		std::cout << "Fox " << Name << " is born! " << std::endl;
	}
}

bool Fox::AgeUp()
{
	++Age;

	return Age < DeathAge;
}

bool Fox::Feed(Ecosystem* System)
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

void Fox::Reproduce(Ecosystem* System)
{
	if (Age >= ReproduceAge)
	{
		std::cout << "Fox " << Name << " reproduced! " << std::endl;
	}
}

void Fox::Kill()
{
	std::cout << "Fox " << Name << " is dead! " << std::endl;
}