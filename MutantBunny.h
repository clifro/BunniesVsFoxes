#pragma once

#include "Entity.h"

class MutantBunny : public Entity
{
	bool Feed(Ecosystem* system) override;
	void Kill() override;
	void Reproduce(Ecosystem* system) override;
};