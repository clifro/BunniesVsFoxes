#include "Bunny.h"
#include "Ecosystem.h"
#include "EcosystemData.h"
#include<iostream>

Bunny::Bunny() : IsGhost(false), IsMutant(false), 
Super(EntityType::Grass, Ecosystem::GetEcosystem()->RandomName(4),
	EcosystemData::BunnyReproduceAge, EcosystemData::BunnyDeathAge,
	EcosystemData::BunnyFoodAmount, EntityType::Grass,
	rand() % 2 ? Gender::Female : Gender::Male,
	static_cast<Color>(rand() % sizeof(Color)))
{
	bool ConvertToMutant = ((rand() % 100) <= EcosystemData::BunnyMutantChance);
	std::string GenderText = (static_cast<int>(EntityGender) ? "Female" : "Male");
	Ecosystem::GetEcosystem()->count++;

	if (ConvertToMutant)
	{
		MakeMutant();
	}

	std::cout << "Bunny " << Name << " is born! " << GenderText << std::endl;
}

Bunny::Bunny(std::shared_ptr<Entity>& Mother) : Bunny()
{
	if (!std::weak_ptr<Entity>(Mother).expired())
	{
		ColorAssigned = Mother->ColorAssigned;
	}
}

void Bunny::MakeMutant()
{
	DeathAge = EcosystemData::BunnyMutantDeathAge;
	FoodAmount = EcosystemData::BunnyMutantFoodAmount;
	ReproduceAge = EcosystemData::BunnyMutantReproduceAge;
	Name = "Mutant " + Name;
	IsMutant = true;
}

void Bunny::DisplayStatus()
{
	std::string status = Name;

	if (!IsGhost)
	{
		status += " Age:" + std::to_string(Age);
	}
	else
	{
		status += " Ghost for " + std::to_string(RemainingTurns) + " Turns ";
	}

	std::cout << status << std::endl;
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

	if (IsMutant && (BitByMutantAtTurn < Ecosystem::GetEcosystem()->Turn))
	{
		Bite();
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

void Bunny::Bite()
{
	std::vector<std::shared_ptr<Entity>>& Entities = Ecosystem::GetEcosystem()->EntitiesMap[EntityType::Bunny];
	for (auto it = Entities.begin(); it != Entities.end(); ++it)
	{
		Bunny* AdultBunny = static_cast<Bunny*>((*it).get());

		if (AdultBunny->IsMutant)
		{
			continue;
		}

		std::cout << "Bunny " << Name << " bite " << AdultBunny->Name << std::endl;
		AdultBunny->MakeMutant();
		AdultBunny->BitByMutantAtTurn = Ecosystem::GetEcosystem()->Turn;
		std::cout << AdultBunny->Name << " is created " << std::endl;
		return;
	}
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
}

Bunny::~Bunny()
{
	Ecosystem::GetEcosystem()->count--;
}