#include"Ecosystem.h"
#include"Entity.h"
#include"Bunny.h"
#include"Fox.h"
#include<iostream>
#include<iterator>

Ecosystem* Ecosystem::EcosystemManager = NULL;

Ecosystem::Ecosystem() : GrassAmount(EcosystemData::MaxGrass)
{
	//Calling Init here calls new bunny creation constructor which calls the getecosytem recreating new memory allocation
}

Ecosystem::~Ecosystem()
{
	std::cout << "Destroying Ecosystem........ " << std::endl;
	std::cout << "Remaining leaked memory entities count " << Ecosystem::GetEcosystem()->count << std::endl;
}

Ecosystem* Ecosystem::GetEcosystem()
{
	if (!EcosystemManager)
	{
		std::cout << "Initializing Ecosystem........ " << std::endl;
		EcosystemManager = new Ecosystem();
		std::cout << "Initialized Ecosystem! " << std::endl;
		EcosystemManager->Init();
	}

	return EcosystemManager;
}

void Ecosystem::AddEntity(EntityType InType, Entity* InEntity)
{
	EntitiesMap[InType].emplace_back(InEntity);
}

void Ecosystem::AddReproducedEntity(EntityType InType, Entity* InEntity)
{
	ReproducedEntitiesMap[InType].emplace_back(InEntity);
}

void Ecosystem::AddEntity(EntityType InType, std::shared_ptr<Entity>& InEntity)
{
	EntitiesMap[InType].emplace_back(InEntity);
}

void Ecosystem::AddReproducedEntitiesInEcosystem()
{
	if (ReproducedEntitiesMap.size() > 0)
	{
		for (auto i = EntitiesMap.begin(); i != EntitiesMap.end(); i++)
		{
			std::vector<std::shared_ptr<Entity>>& Entities = EntitiesMap[i->first];
			std::vector<std::shared_ptr<Entity>>& ReproducedEntities = ReproducedEntitiesMap[i->first];
			Entities.insert(Entities.begin(), ReproducedEntities.begin(), ReproducedEntities.end());
		}

		ReproducedEntitiesMap.clear();
	}
}

bool Ecosystem::SimulateEcosystem()
{
	Turn++;
	GrassAmount += EcosystemData::GrassGrowthRate;

	if (GrassAmount > EcosystemData::MaxGrass) 
	{
		GrassAmount = EcosystemData::MaxGrass;
	}

	std::cout << "Turn : " << Turn << " Grass is " << GrassAmount << std::endl;
	bool Terminate = true;

	for (auto i = EntitiesMap.begin(); i != EntitiesMap.end(); i++)
	{
		ProcessLife(i->first);
		std::vector<std::shared_ptr<Entity>>& Entities = EntitiesMap[i->first];
		size_t numberOfEntities = Entities.size();

		if (i->first == EntityType::Bunny || i->first == EntityType::GhostBunny || i->first == EntityType::MutantBunny)
		{
			if ((i->first == EntityType::Bunny))
			{
				if (numberOfEntities >= EcosystemData::MaxBunnyCount)
				{
					std::cout << "Max Bunny population reached " << std::endl;
					size_t bunniesToKill = (numberOfEntities / 2);

					while (bunniesToKill > 0)
					{
						size_t randomIndex = rand() % Entities.size();
						std::cout << Entities[randomIndex]->Name << " Killed ";
						Entities.erase(Entities.begin() + randomIndex);
						bunniesToKill--;
					}
				}
			}

			if (numberOfEntities > 0)
			{
				std::cout << "------------------------------ Bunnies status ------------------------------" << std::endl;
				for (auto it = EntitiesMap[i->first].begin(); it != EntitiesMap[i->first].end(); ++it)
				{
					Bunny* BunnyEntity = static_cast<Bunny*>((*it).get());
					BunnyEntity->DisplayStatus();
				}
				std::cout << "------------------------------ xxxxxxxxxxxxx ------------------------------" << std::endl;

				Terminate = false;
			}
		}
	}

	if (Terminate)
	{
		std::cout << "All Bunnies are dead. Terminating " << std::endl;
	}

	return !Terminate;
}

void Ecosystem::ProcessLife(EntityType InType)
{
	for (auto it = EntitiesMap[InType].begin(); it != EntitiesMap[InType].end();)
	{
		Entity* EntityToProcess = (*it).get();

		if (EntityToProcess->AgeUp() && EntityToProcess->Feed())
		{
			it++;
		}
		else
		{
			EntityToProcess->Kill();
			it = EntitiesMap[InType].erase(it);
		}
	}

	for (auto it = EntitiesMap[InType].begin(); it != EntitiesMap[InType].end();)
	{
		Entity* EntityToProcess = (*it).get();
		EntityToProcess->Reproduce();
		it++;
	}

	AddReproducedEntitiesInEcosystem();
}

void Ecosystem::Init()
{
	for (int i = 0; i < EcosystemData::BunnyCount; i++)
	{
		AddEntity(EntityType::Bunny, new Bunny());
	}

	for (int i = 0; i < EcosystemData::FoxCount; i++)
	{
		AddEntity(EntityType::Fox, new Fox());
	}
}

std::string Ecosystem::RandomName(int length) {

	char consonents[] = { 'b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','z' };
	char vowels[] = { 'a','e','i','o','u','y' };

	std::string name = "";

	int random = rand() % 2;
	int count = 0;

	for (int i = 0; i < length; i++) {

		if (random < 1 && count < 1) {
			name = name + consonents[rand() % 19];
			count++;
		}
		else 
		{
			name = name + vowels[rand() % 5];
			count = 0;
		}

		random = rand() % 2;
	}

	return name;
}

void Ecosystem::Cleanup()
{
	for (auto i = EntitiesMap.begin(); i != EntitiesMap.end(); i++)
	{
		std::vector<std::shared_ptr<Entity>>& Entities = EntitiesMap[i->first];

		for (auto it = Entities.begin(); it != Entities.end();)
		{
			Entity* EntityToProcess = (*it).get();
			it = Entities.erase(it);
		}

		std::vector<std::shared_ptr<Entity>>& ReproducedEntities = ReproducedEntitiesMap[i->first];

		for (auto it = ReproducedEntities.begin(); it != ReproducedEntities.end();)
		{
			Entity* EntityToProcess = (*it).get();
			it = ReproducedEntities.erase(it);
		}
	}
}