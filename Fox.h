#pragma once

#include "Entity.h"

class Fox : public Entity
{
public:
	Fox(Ecosystem* system);
	bool AgeUp() override;
	bool Feed(Ecosystem* system) override;
	void Kill() override;
	void Reproduce(Ecosystem* system) override;
};