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
	const int BunnyCount = 10;
	const int FoxCount = 10;
	const int MaxBunnyCount = 1000;
	const int MaxBunnyRedcutionPercent = 50;

public:
	std::map<EntityType, std::vector<Entity*>> EntitiesMap;
	std::map<EntityType, std::vector<Entity*>> ReproducedEntitiesMap;
	int Turn = 0;
	Ecosystem();
	inline int GetGrassAmount() { return GrassAmount; }
	inline void ConsumeGrass(int& Amount) { GrassAmount -= Amount; }

	void Init();
	void AddEntity(EntityType Type, Entity* Entity, bool Reproduced = false);
	void ProcessLife(EntityType Type);
	bool SimulateEcosystem();
	std::string RandomName(int length);
	void AddReproducedEntitiesInEcosystem();
};