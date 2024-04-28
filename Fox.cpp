#include "Fox.h"
#include "Ecosystem.h"
#include<iostream>
#include"Bunny.h"
#include"Ecosystem.h"

Fox::Fox() : HuntingAge(EcosystemData::FoxHuntingAge), FeedingAgainCounter(0),
Super(EntityType::Grass, Ecosystem::GetEcosystem()->RandomName(4), 
	EcosystemData::FoxReproduceAge, EcosystemData::FoxDeathAge, 
	EcosystemData::FoxFoodAmount, EntityType::Grass, 
	rand() % 2 ? Gender::Female : Gender::Male, static_cast<Color>(rand() % sizeof(Color)))
{
	std::cout << "Fox " << Name << " is born! " << std::endl;
	Ecosystem::GetEcosystem()->count++;
}

bool Fox::AgeUp()
{
	if (RemainingTurns > 0)
	{
		RemainingTurns--;
	}

	Reproduced = false;
	++Age;

	if (Age >= DeathAge)
	{
		std::cout << "Fox " << Name << " aged up! " << std::endl;
	}

	return Age < DeathAge;
}

bool Fox::Feed()
{
	if (Age < HuntingAge)
	{
		return true;
	}

	std::vector<std::shared_ptr<Entity>>& Bunnies = Ecosystem::GetEcosystem()->EntitiesMap[EntityType::Bunny];
	int numOfBunnies = Bunnies.size();

	if (numOfBunnies == 0)
	{
		std::cout << "Fox " << Name << " Starved " << std::endl;
		return false;
	}

	const int randomId = rand() % numOfBunnies;
	Bunny* BunnyToEat = static_cast<Bunny*>(Bunnies[randomId].get());

	if (BunnyToEat)
	{
		bool CanDieEatingBunny = false;
		std::cout << "Fox " << Name << " Ate " << BunnyToEat->Name << std::endl;

		if (!BunnyToEat->IsMutant)
		{
			BunnyToEat->RemainingTurns = EcosystemData::BunnyGhostTurns;
			BunnyToEat->IsGhost = true;
			std::cout << "Bunny " << BunnyToEat->Name << " Became ghost " << std::endl;
			Ecosystem::GetEcosystem()->AddEntity(EntityType::GhostBunny, Bunnies[randomId]);
		}
		else
		{
			RemainingTurns = EcosystemData::FoxReproBanTurns;
			BunnyToEat->Kill();
			CanDieEatingBunny = ((rand() % 100) <= EcosystemData::FoxDeathDeathChanceEatingMutant);
		}

		Bunnies.erase(Bunnies.begin() + randomId);

		if (CanDieEatingBunny)
		{
			return false;
		}

		const bool FeedAgainChance = (rand() % 100 <= EcosystemData::FoxFeedAgainChance);
		const bool IsGrassLess = Ecosystem::GetEcosystem()->GetGrassAmount() < (EcosystemData::FoxFeedAgainChanceWithGrassAmount * EcosystemData::MaxGrass / 100);

		if (FeedAgainChance && (FeedingAgainCounter == 0) && IsGrassLess)
		{
			FeedingAgainCounter = EcosystemData::FoxFeedAgainCount;

			for (int i = FeedingAgainCounter; i > 0; --i)
			{
				std::cout << "Fox " << Name << " Feeding Again " << std::endl;
				Feed();
			}
		}

		return true;
	}
}


bool Fox::CanReproduce()
{
	return (Age >= ReproduceAge) && (RemainingTurns <= 0) && !Reproduced;
}

void Fox::Reproduce()
{
	if ((EntityGender != Gender::Male) || !CanReproduce())
	{
		return;
	}

	Reproduced = true;
	std::vector<std::shared_ptr<Entity>>& Entities = Ecosystem::GetEcosystem()->EntitiesMap[EntityType::Fox];

	for (auto it = Entities.begin(); it != Entities.end(); ++it)
	{
		Fox* AdultFox = static_cast<Fox*>((*it).get());

		if ((AdultFox->EntityGender == Gender::Female) && AdultFox->CanReproduce())
		{
			AdultFox->Reproduced = true;
			std::cout << "Fox " << Name << " reproduced with " << (*it)->Name << std::endl;
			Ecosystem::GetEcosystem()->AddReproducedEntity(EntityType::Fox, new Fox());
			break;
		}
	}
}

void Fox::Kill()
{
	std::cout << "Fox " << Name << " is dead! " << std::endl;
}

Fox::~Fox()
{
	Ecosystem::GetEcosystem()->count--;
}