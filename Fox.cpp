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
	RemainingTurns = -1;
	ReproducedAtTurn = 0;
	Gender = rand() % 2;
	Age = 0;
	FeedingAgain = false;

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
			//TODO Find random  bunny from a list which doesnt have ghost bunnies; assert how to usewe , when to use
			//use const if things dont change
			const int randomId = rand() % numOfBunnies;
			Bunny* BunnyToEat = static_cast<Bunny*>(System->EntitiesMap[EntityType::Bunny][randomId]);

			if (BunnyToEat && !BunnyToEat->Ghost)
			{
				std::cout << "Fox " << Name << " Ate " << BunnyToEat->Name << std::endl;
				System->EntitiesMap[EntityType::Bunny][randomId]->RemainingTurns = 5;

				if (!BunnyToEat->Mutant)
				{
					BunnyToEat->Ghost = true;

					if (!FeedingAgain && System->GetGrassAmount() < (20 * EcosystemData::MaxGrass / 100))
					{
						const bool FeedAgainChance = (rand() % 100 <= 50); // TODO loop for feeding number of times

						if (FeedAgainChance)
						{
							FeedingAgain = true;
							Feed(System);
						}
					}
				}
				else
				{
					const bool death = ((rand() % 100) <= 30);
					if (death)
					{
						return false;
					}
				}
				
				FeedingAgain = false;
				return true;
			}
		}

		std::cout << "Fox " << Name << " Starved " << std::endl;
	}

	return Age < HuntingAge;
}

void Fox::Reproduce(Ecosystem* System)
{
	//todo AdultFox->ReproduceAge > 0 no need to check
	//TODO apply the indentations and cast
	if ((Age >= ReproduceAge) && (RemainingTurns <= 0) && (ReproducedAtTurn < System->Turn))
	{
		if (Gender == 0)
		{
			ReproducedAtTurn = System->Turn;

			for (auto it = System->EntitiesMap[EntityType::Fox].begin(); it != System->EntitiesMap[EntityType::Fox].end(); ++it)
			{
				Fox* AdultFox = dynamic_cast<Fox*>((*it));

				if ((AdultFox->Gender == 1) && (AdultFox->ReproduceAge > 0) && (AdultFox->Age >= AdultFox->ReproduceAge) && (AdultFox->RemainingTurns <= 0) && (AdultFox->ReproducedAtTurn < System->Turn))
				{
					AdultFox->ReproducedAtTurn = System->Turn;
					std::cout << "Fox " << Name << " reproduced with " << (*it)->Name << std::endl;
					System->AddReproducedEntity(EntityType::Fox, new Fox(System));
					break;
				}
			}
		}
	}
}

void Fox::Kill()
{
	std::cout << "Fox " << Name << " is dead! " << std::endl;
}