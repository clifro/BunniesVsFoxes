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
	EntityType FoodType;
	int FoodAmount;
	int DeathAge;

public:
	Color ColorAssigned;
	std::string Name;
	int ReproduceAge;
	int RemainingTurns;
	int Age;
	int ReproducedAtTurn;
	bool Gender; // 0 M, 1 F
	virtual bool AgeUp(Ecosystem* system) = 0;
	virtual bool Feed(Ecosystem* system) = 0;
	virtual void Kill() = 0;
	virtual void Reproduce(Ecosystem* system) = 0;
};