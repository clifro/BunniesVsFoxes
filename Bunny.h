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
	Bunny(std::shared_ptr<Entity> Mother = 0);
	~Bunny();
	bool Feed() override;
	void Kill() override;
	void Reproduce() override;
	bool AgeUp() override;
	bool CanReproduce() override;
};