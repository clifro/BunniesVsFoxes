#pragma once

#include "Entity.h"

class Bunny : public Entity
{
private:

public:
	Entity* Parent; // Force bunny pointer, reason being fox cannot be the parent
	bool Mutant;
	bool Ghost;
	Bunny(Ecosystem* system, Entity* Mother = 0); // TODO GetEcosystem() 
	bool Feed(Ecosystem* system) override;
	void Kill() override;
	void Reproduce(Ecosystem* system) override;
	void SetName(std::string& Name);
	bool AgeUp(Ecosystem* system) override; // TODO pass ref
};