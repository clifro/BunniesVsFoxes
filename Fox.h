#pragma once

#include "Entity.h"

class Fox : public Entity
{
public:
	int HuntingAge;
	int FeedingAgainCounter;
	Fox();
	~Fox();
	bool AgeUp() override;
	bool Feed() override;
	void Kill() override;
	void Reproduce() override;
	bool CanReproduce() override;
};