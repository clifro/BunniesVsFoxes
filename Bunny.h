#pragma once

#include "Entity.h"

class Bunny : public Entity
{
public:
	Entity* Parent;
	Bunny(Ecosystem* system, Entity* Mother = 0);
	bool Feed(Ecosystem* system) override;
	void Kill() override;
	void Reproduce(Ecosystem* system) override;
	void SetName(std::string& Name);
	bool AgeUp(Ecosystem* system) override;
};