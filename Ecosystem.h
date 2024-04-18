#pragma once

#include<map>
#include<vector>
#include<string>;
enum class EntityType;
class Entity;

class Ecosystem
{
private:
	int MaxGrassAmount = 500;
	int GrassAmount = MaxGrassAmount;
	int GrassGrowRate = 10;
	const int BunnyCount = 5;
	const int FoxCount = 5;
	const int MaxBunnyCount = 1000;
	const int MaxBunnyRedcutionPercent = 50;

public:
	std::map<EntityType, std::vector<Entity*>> EntitiesMap;
	std::map<EntityType, std::vector<Entity*>> ReproducedEntitiesMap;
	int Turn = 0;
	Ecosystem();
	inline int GetGrassAmount() { return GrassAmount; }
	inline int GetMaxGrassAmount() { return MaxGrassAmount; }
	inline void ConsumeGrass(int& Amount) { GrassAmount -= Amount; }

	void Init();
	void AddEntity(EntityType Type, Entity* Entity, bool Reproduced = false);
	void ProcessLife(EntityType Type);
	bool SimulateEcosystem();
	std::string RandomName(int length);
	void AddReproducedEntitiesInEcosystem();
};