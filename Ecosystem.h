#pragma once

#include<vector>
#include<string>
#include<unordered_map>
#include<memory>
#include"EcosystemData.h"

enum class EntityType;
class Entity;

class Ecosystem
{
private:

	int GrassAmount;
	static Ecosystem* EcosystemManager;

public:

	int count = 0;
	Ecosystem();
	~Ecosystem();

	static Ecosystem* GetEcosystem();

	// Used unordered map as it is faster and we dont have a requirement to have ordered keys.
	// Ordered map is slower as it uses red black tree. Access time is proportional to the number of keys.
	std::unordered_map<EntityType, std::vector<std::shared_ptr<Entity>>> EntitiesMap;
	std::unordered_map<EntityType, std::vector<std::shared_ptr<Entity>>> ReproducedEntitiesMap;
	
	int Turn = 0;
	inline int GetGrassAmount() const { return GrassAmount; }
	inline void ConsumeGrass(int& Amount) { GrassAmount -= Amount; }

	void Init();
	void AddEntity(EntityType InType, Entity* InEntity);
	void AddReproducedEntity(EntityType InType, Entity* InEntity);
	void AddEntity(EntityType InType, std::shared_ptr<Entity>& InEntity);
	void ProcessLife(EntityType InType);
	bool SimulateEcosystem();
	std::string RandomName(int length);
	void Cleanup();
	void AddReproducedEntitiesInEcosystem();
};