#pragma once

#include "Entity.h"



class Bunny : public Entity
{
private:

public:

	Bunny* Parent; // Force bunny pointer, reason being fox cannot be the parent
	bool IsMutant;
	bool IsGhost;
	Bunny(Bunny* Mother = 0);
	bool Feed() override;
	void Kill() override;
	void Reproduce() override;
	bool AgeUp() override;
	bool CanReproduce() override;
};