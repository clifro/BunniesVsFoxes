#include "Fox.h"
#include "Ecosystem.h"
#include<iostream>
#include"Bunny.h"

Fox::Fox(Ecosystem* system)
{
	HuntingAge = 2;
	FoodType = EntityType::Bunny;
	FoodAmount = 1;
	DeathAge = 20;
	ReproduceAge = 2;
	Age = 0;

	if (system)
	{
		Name = system->RandomName(4);
		std::cout << "Fox " << Name << " is born! " << std::endl;
	}
}

bool Fox::AgeUp(Ecosystem* system)
{
	if (RemainingTurns > 0)
	{
		RemainingTurns--;
	}

	++Age;
	return Age < DeathAge;
}

bool Fox::Feed(Ecosystem* System)
{
	if (System && (Age >= HuntingAge))
	{
		int numOfBunnies = System->EntitiesMap[EntityType::Bunny].size();

		if (numOfBunnies > 0)
		{
			int randomId = rand() % numOfBunnies;
			std::string bunnyName = System->EntitiesMap[EntityType::Bunny][randomId]->Name;
			std::cout << "Fox " << Name << " Ate " << bunnyName << std::endl;

			if (System->EntitiesMap[EntityType::Bunny][randomId]->ReproduceAge > 0)
			{
				System->EntitiesMap[EntityType::Bunny][randomId]->RemainingTurns = 5;
				Bunny* BunnyFood = dynamic_cast<Bunny*>(System->EntitiesMap[EntityType::Bunny][randomId]);

				if (BunnyFood)
				{
					BunnyFood->Ghost = true;
				}
			}

			return true;
		}
		else
		{
			std::cout << "Fox " << Name << " Starved " << std::endl;
		}
	}

	return Age < HuntingAge;
}

void Fox::Reproduce(Ecosystem* System)
{
	if ((Age >= ReproduceAge) && (RemainingTurns <= 0))
	{
		std::cout << "Fox " << Name << " reproduced! " << std::endl;
	}
}

void Fox::Kill()
{
	std::cout << "Fox " << Name << " is dead! " << std::endl;
}