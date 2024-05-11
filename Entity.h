#pragma once

#include<string>
class Ecosystem;

enum Color
{
	Yellow,
	Green,
	Blue,
	White,
	Red,
	Pink,
	Orange,
	Indigo
};

enum class EntityType
{
	Grass,
	Bunny,
	MutantBunny,
	GhostBunny,
	Fox
};

enum class Gender
{
	Male,
	Female,
	Count // max count for randomization
};

class Entity
{
protected:

	EntityType Type;
	EntityType FoodType;
	int FoodAmount;
	int DeathAge;

public:

	typedef Entity Super;
	Entity();
	Entity(EntityType InType, const std::string& InName, int InReproduceAge, int InDeathAge, int InFoodAmount, EntityType InFoodType, Gender InGender, Color InColor);
	virtual ~Entity();
	Color ColorAssigned;
	std::string Name;
	int ReproduceAge;
	int RemainingTurns;
	int Age;
	bool Reproduced;
	Gender EntityGender;
	virtual bool AgeUp() = 0;
	virtual bool Feed() = 0;
	virtual void Kill() = 0;
	virtual void Reproduce() = 0;
	virtual bool CanReproduce() = 0;
};