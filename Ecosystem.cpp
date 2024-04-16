#include"Ecosystem.h"
#include"Entity.h"
#include"Bunny.h"
#include"Fox.h"
#include<iostream>
#include<iterator>

Ecosystem::Ecosystem()
{
	Init();
}

void Ecosystem::AddEntity(EntityType Type, Entity* EntityData, bool Reproduced)
{
	if (Reproduced)
	{
		ReproducedEntitiesMap[Type].push_back(EntityData);
	}
	else
	{
		EntitiesMap[Type].push_back(EntityData);
	}
}

void Ecosystem::AddReproducedEntitiesInEcosystem()
{
	if (ReproducedEntitiesMap.size() > 0)
	{
		for (auto i = EntitiesMap.begin(); i != EntitiesMap.end(); i++)
		{
			EntitiesMap[i->first].insert(EntitiesMap[i->first].end(), ReproducedEntitiesMap[i->first].begin(), ReproducedEntitiesMap[i->first].end());
		}

		ReproducedEntitiesMap.clear();
	}
}

bool Ecosystem::SimulateEcosystem()
{
	bool endSimulation = true;
	Turn++;

	GrassAmount += GrassGrowRate;
	std::cout << "Turn : " << Turn << " Grass is " << GrassAmount << std::endl;

	for (auto i = EntitiesMap.begin(); i != EntitiesMap.end(); i++)
	{
		ProcessLife(i->first);

		if (EntitiesMap[i->first].size() != 0)
		{
			endSimulation = false;
		}
	}

	return !endSimulation;
}

void Ecosystem::ProcessLife(EntityType Type)
{
	for (auto it = EntitiesMap[Type].begin(); it != EntitiesMap[Type].end();)
	{
		if ((*it)->AgeUp(this) && (*it)->Feed(this))
		{
			(*it)->Reproduce(this);
			it++;
		}
		else
		{
			(*it)->Kill();
			(*it) = 0;
			delete* it;
			it = EntitiesMap[Type].erase(it);
		}
	}

	AddReproducedEntitiesInEcosystem();
}

void Ecosystem::Init()
{
	for (int i = 0; i < BunnyCount; i++)
	{
		AddEntity(EntityType::Bunny, new Bunny(this));
	}

	for (int i = 0; i < FoxCount; i++)
	{
		AddEntity(EntityType::Fox, new Fox(this));
	}
}

std::string Ecosystem::RandomName(int length) {

	char consonents[] = { 'b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','z' };
	char vowels[] = { 'a','e','i','o','u','y' };

	std::string name = "";

	int random = rand() % 2;
	int count = 0;

	for (int i = 0; i < length; i++) {

		if (random < 2 && count < 2) {
			name = name + consonents[rand() % 19];
			count++;
		}
		else {
			name = name + vowels[rand() % 5];
			count = 0;
		}

		random = rand() % 2;

	}

	return name;
}