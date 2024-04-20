#include "Bunny.h"
#include "Ecosystem.h"
#include<iostream>

const int MutantChance = 2;



Bunny::Bunny(Ecosystem* system, Entity* Mother) : Parent(Mother)
{
	//USE INITIALIZER LIST
	Parent = Mother;
	ColorAssigned = Mother ? Mother->ColorAssigned : static_cast<Color>(rand() % sizeof(Color));
	RemainingTurns = -1;
	FoodType = EntityType::Grass;
	FoodAmount = 2; //TODO USE CONSTS
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

	bool ConvertToMutant = ((rand() % 100) <= MutantChance); //use consts

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
	if (Ghost && RemainingTurns > 0) //TODO Naming, IsGhost IsMutant
	{
		RemainingTurns--;

		return RemainingTurns != 0;
	}
	
	++Age;
	return Age < DeathAge;
}

bool Bunny::Feed(Ecosystem* System)
{
	if (System) // no need to check
	{
		if (Ghost)
		{
			return true;
		}

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
	if (!Mutant && !Ghost && (Age >= ReproduceAge) && (ReproducedAtTurn < System->Turn)) // TODO GETTER
	{
		//TODO
		/*if (!x)
		{
			return;
		}
		if (!y)
		{
			return;
		}*/
		//TODO use bool for ReproducedAtTurn
		if (Gender == 0) // TODO Use male female enum , COMBINE THIS CHECK
		{
			for (auto it = System->EntitiesMap[EntityType::Bunny].begin(); it != System->EntitiesMap[EntityType::Bunny].end(); ++it)
			{
				Bunny* AdultBunny = static_cast<Bunny*>((*it)); // USE DYNAMIC LESS FREQUENT

				if (AdultBunny)
				{
					AdultBunny->ReproducedAtTurn = System->Turn;
					//TODO order my age 

					if ((AdultBunny->Gender == 1) && (AdultBunny->ReproduceAge > 0) && (AdultBunny->Age >= AdultBunny->ReproduceAge) && !AdultBunny->Mutant && !AdultBunny->Ghost)
					{
						std::cout << "Bunny " << Name << " reproduced with " << AdultBunny->Name << std::endl;
						System->AddReproducedEntity(EntityType::Bunny, new Bunny(System, AdultBunny));
					}
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