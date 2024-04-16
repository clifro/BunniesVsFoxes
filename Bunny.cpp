#include "Bunny.h"
#include "Ecosystem.h"
#include<iostream>

Bunny::Bunny(Ecosystem* system, Entity* Mother)
{
	Parent = Mother;
	RemainingTurns = -1;
	FoodType = EntityType::Grass;
	FoodAmount = 2;
	DeathAge = 10;
	ReproduceAge = 2;
	ReproducedAtTurn = 0;
	Age = 0;
	Gender = rand() % 2;

	if (system)
	{
		Name = system->RandomName(4);
		std::cout << "Bunny " << Name << " is born! " << Gender << std::endl;
	}
}

bool Bunny::AgeUp(Ecosystem* system)
{
	if (RemainingTurns > 0)
	{
		RemainingTurns--;

		if (RemainingTurns == 0)
		{
			return false;
		}

		return true;
	}

	if (ReproduceAge > 0)
	{
		bool ConvertToMutant = ((rand() % 100) <= 2);

		if (ConvertToMutant)
		{
			std::cout << "Bunny " << Name << " turned into Mutant! " << Gender << std::endl;
			DeathAge = 50;
			FoodAmount = 4;
			ReproduceAge = 0;
			Name = "Mutant " + Name;
		}
	}
	
	++Age;
	return Age < DeathAge;
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
	if ((ReproduceAge > 0) && (Age >= ReproduceAge) && (ReproducedAtTurn < System->Turn))
	{
		if (Gender == 0)
		{
			for (auto it = System->EntitiesMap[EntityType::Bunny].begin(); it != System->EntitiesMap[EntityType::Bunny].end(); ++it)
			{
				(*it)->ReproducedAtTurn = System->Turn;

				if (((*it)->Gender == 1) && ((*it)->ReproduceAge > 0) && ((*it)->Age >= (*it)->ReproduceAge))
				{
					std::cout << "Bunny " << Name << " reproduced with " << (*it)->Name << std::endl;
					System->AddEntity(EntityType::Bunny, new Bunny(System, (*it)), true);
				}
			}
		}
	}
}

void Bunny::Kill()
{
	if (RemainingTurns >= 0)
	{
		std::cout << "Ghost Bunny " << Name << " is dead! " << std::endl;

		if (Parent)
		{
			std::cout << "Mother " << Parent->Name << " Finally accepts the death of " << Name << std::endl;
		}
	}
	else
	{
		std::cout << "Bunny " << Name << " is dead! " << std::endl;
	}
}