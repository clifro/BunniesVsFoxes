#include "Bunny.h"
#include "Ecosystem.h"
#include<iostream>

Bunny::Bunny(Ecosystem* system, Entity* Mother)
{
	Parent = Mother;
	ColorAssigned = Mother ? Mother->ColorAssigned : static_cast<Color>(rand() % sizeof(Color));
	RemainingTurns = -1;
	FoodType = EntityType::Grass;
	FoodAmount = 2;
	DeathAge = 10;
	ReproduceAge = 2;
	ReproducedAtTurn = 0;
	Age = 0;
	Gender = rand() % 2;
	Ghost = false;

	if (system)
	{
		Name = system->RandomName(4);
	}

	bool ConvertToMutant = ((rand() % 100) <= 2);

	if (ConvertToMutant)
	{
		DeathAge = 50;
		FoodAmount = 4;
		ReproduceAge = 0;
		Name = "Mutant " + Name;
		std::cout << Name << " is born! " << Gender << std::endl;
		Mutant = ConvertToMutant;
	}
	else
	{
		Mutant = false;
		std::cout << "Bunny " << Name << " is born! " << Gender << std::endl;
	}
}

bool Bunny::AgeUp(Ecosystem* system)
{
	if (Ghost && RemainingTurns > 0)
	{
		RemainingTurns--;

		if (RemainingTurns == 0)
		{
			return false;
		}

		return true;
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
	if (!Mutant && !Ghost && (Age >= ReproduceAge) && (ReproducedAtTurn < System->Turn))
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
	if (Ghost)
	{
		std::cout << "Ghost Bunny " << Name << " goes to the afterlife! " << std::endl;

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