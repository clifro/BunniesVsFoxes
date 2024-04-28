#pragma once

#include "Entity.h"
#include<memory>


class Bunny : public Entity
{
private:

public:

	std::weak_ptr<Entity> Parent; // Force bunny pointer, reason being fox cannot be the parent
	bool IsMutant;
	bool IsGhost;
	int BitByMutantAtTurn = 0;
	Bunny(std::shared_ptr<Entity> Mother = 0);
	~Bunny();
	void DisplayStatus();
	bool Feed() override;
	void Bite();
	void Kill() override;
	void Reproduce() override;
	bool AgeUp() override;
	void MakeMutant();
	bool CanReproduce() override;
};