#pragma once

#include<vector>
#include<string>
#include<unordered_map>
#include"EcosystemData.h"

enum class EntityType;
class Entity;

class Ecosystem
{
private:

	int GrassAmount;
	static Ecosystem* EcosystemManager;

public:

	Ecosystem();
	~Ecosystem();

	static Ecosystem* GetEcosystem();

	// Used unordered map as it is faster and we dont have a requirement to have ordered keys.
	// Ordered map is slower as it uses red black tree. Access time is proportional to the number of keys.
	std::unordered_map<EntityType, std::vector<Entity*>> EntitiesMap;
	std::unordered_map<EntityType, std::vector<Entity*>> ReproducedEntitiesMap;
	
	int Turn = 0;
	inline int GetGrassAmount() const { return GrassAmount; }
	inline void ConsumeGrass(int& Amount) { GrassAmount -= Amount; }

	void Init();
	void AddEntity(EntityType Type, Entity* Entity);
	void AddReproducedEntity(EntityType Type, Entity* Entity);
	void ProcessLife(EntityType Type);
	bool SimulateEcosystem();
	std::string RandomName(int length);
	void Cleanup();
	void AddReproducedEntitiesInEcosystem();
};