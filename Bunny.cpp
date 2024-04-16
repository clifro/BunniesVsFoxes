#include "Bunny.h"
#include "Ecosystem.h"
#include<iostream>

Bunny::Bunny(Ecosystem* system)
{
	FoodType = EntityType::Grass;
	FoodAmount = 2;
	DeathAge = 10;
	ReproduceAge = 2;
	Age = 0;

	if (system)
	{
		Name = system->RandomName(4);
		std::cout << "Bunny " << Name << " is born! " << std::endl;
	}
}

bool Bunny::AgeUp()
{
	++Age;

	return Age > DeathAge;
}

bool Bunny::Feed(Ecosystem* System)
{
	if (System)
	{
		if (System->GetGrassAmount() >= FoodAmount)
		{
			System->ConsumeGrass(FoodAmount);
			std::cout << "Bunny " << Name << " ate! " << std::endl;
			return true;
		}
	}

	std::cout << "Bunny " << Name << " starved! " << std::endl;
	return false;
}

void Bunny::Reproduce(Ecosystem* System)
{
	if (ReproduceAge >= Age)
	{
		std::cout << "Bunny " << Name << " reproduced! " << std::endl;
	}
}

void Bunny::Kill()
{
	std::cout << "Bunny " << Name << " is dead! " << std::endl;
}