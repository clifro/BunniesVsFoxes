#pragma once

#include "Entity.h"

class Fox : public Entity
{
public:
	int HuntingAge;
	bool FeedingAgain;
	Fox(Ecosystem* system);
	bool AgeUp(Ecosystem* system) override;
	bool Feed(Ecosystem* system) override;
	void Kill() override;
	void Reproduce(Ecosystem* system) override;
};