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
	Fox
};

class Entity
{
protected:

	EntityType Type;
	std::string Name;
	EntityType FoodType;
	int FoodAmount;
	int DeathAge;
	int ReproduceAge;
	int Age;

public:
	virtual bool AgeUp() = 0;
	virtual bool Feed(Ecosystem* system) = 0;
	virtual void Kill() = 0;
	virtual void Reproduce(Ecosystem* system) = 0;
};