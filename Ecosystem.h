#pragma once

#include<map>
#include<vector>
#include<string>;
enum class EntityType;
class Entity;

class Ecosystem
{
private:
	int GrassAmount = 500;
	int GrassGrowRate = 10;
	int Turn = 0;
	const int BunnyCount = 5;
	const int FoxCount = 5;
	const int MaxBunnyCount = 1000;
	const int MaxBunnyRedcutionPercent = 50;
	std::map<EntityType, std::vector<Entity*>> EntitiesMap;

public:
	Ecosystem();
	inline int GetGrassAmount() { return GrassAmount; }
	inline void ConsumeGrass(int& Amount) { GrassAmount -= Amount; }

	void Init();
	void AddEntity(EntityType Type, Entity* Entity);
	void ProcessLife(EntityType Type);
	bool SimulateEcosystem();
	std::string RandomName(int length);
};