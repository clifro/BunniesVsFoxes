#pragma once

#include "Entity.h"

class Bunny : public Entity
{
public:
	Bunny(Ecosystem* system);
	bool Feed(Ecosystem* system) override;
	void Kill() override;
	void Reproduce(Ecosystem* system) override;
	void SetName(std::string& Name);
	bool AgeUp() override;
};