#include "Bunny.h"
#include "Ecosystem.h"
#include "EcosystemData.h"
#include<iostream>

Bunny::Bunny(std::shared_ptr<Entity> Mother) : Parent(Mother), IsGhost(false), IsMutant(false),
Super(EntityType::Grass, Ecosystem::GetEcosystem()->RandomName(4), 
	EcosystemData::BunnyReproduceAge, EcosystemData::BunnyDeathAge, 
	EcosystemData::BunnyFoodAmount, EntityType::Grass, 
	rand() % 2 ? Gender::Female : Gender::Male,
	Mother ? Mother->ColorAssigned : static_cast<Color>(rand() % sizeof(Color)))
{
	bool ConvertToMutant = ((rand() % 100) <= EcosystemData::BunnyMutantChance);
	std::string GenderText = (static_cast<int>(EntityGender) ? "Female" : "Male");
	Ecosystem::GetEcosystem()->count++;

	if (ConvertToMutant)
	{
		DeathAge = EcosystemData::BunnyMutantDeathAge;
		FoodAmount = EcosystemData::BunnyMutantFoodAmount;
		ReproduceAge = EcosystemData::BunnyMutantReproduceAge;
		Name = "Mutant " + Name;
		IsMutant = ConvertToMutant;
	}
	
	std::cout << "Bunny " << Name << " is born! " << GenderText << std::endl;
}

bool Bunny::AgeUp()
{
	if (IsGhost && RemainingTurns > 0)
	{
		RemainingTurns--;

		return RemainingTurns != 0;
	}
	
	Reproduced = false;
	++Age;

	if (Age >= DeathAge)
	{
		std::cout << "Bunny " << Name << " aged up! " << std::endl;
	}

	return Age < DeathAge;
}

bool Bunny::Feed()
{
	if (IsGhost)
	{
		return true;
	}

	if (Ecosystem::GetEcosystem()->GetGrassAmount() >= FoodAmount)
	{
		Ecosystem::GetEcosystem()->ConsumeGrass(FoodAmount);
		std::cout << "Bunny " << Name << " ate! " << std::endl;
		return true;
	}

	std::cout << "Bunny " << Name << " starved! " << std::endl;
	return false;
}

bool Bunny::CanReproduce()
{
	return !IsMutant && !IsGhost && (Age >= ReproduceAge) && !Reproduced;
}

void Bunny::Reproduce()
{
	if ((EntityGender != Gender::Male) || !CanReproduce())
	{
		return;
	}

	std::vector<std::shared_ptr<Entity>>& Entities = Ecosystem::GetEcosystem()->EntitiesMap[EntityType::Bunny];

	for (auto it = Entities.begin(); it != Entities.end(); ++it)
	{
		Bunny* AdultBunny = static_cast<Bunny*>((*it).get());

		if (!AdultBunny)
		{
			return;
		}

		//TODO order by age 

		if ((AdultBunny->EntityGender == Gender::Female) && AdultBunny->CanReproduce())
		{
			AdultBunny->Reproduced = true;
			std::cout << "Bunny " << Name << " reproduced with " << AdultBunny->Name << std::endl;
			Ecosystem::GetEcosystem()->AddReproducedEntity(EntityType::Bunny, new Bunny((*it)));
		}
	}
}

void Bunny::Kill()
{
	if (IsGhost)
	{
		std::cout << "Ghost Bunny " << Name << " goes to the afterlife! " << std::endl;

		if (!Parent.expired())
		{
			std::cout << "Mother " << Parent.lock()->Name << " Finally accepts the death of " << Name << std::endl;
		}
	}
	else
	{
		std::cout << "Bunny " << Name << " is dead! " << std::endl;
	}

	Ecosystem::GetEcosystem()->count--;
}