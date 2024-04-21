#include"Entity.h"
 
Entity::Entity(EntityType InType, std::string Name, int InReproduceAge, int InDeathAge, int InFoodAmount, EntityType InFoodType, Gender InGender, Color InColor) :
	RemainingTurns(-1), ReproduceAge(InReproduceAge), Age(0), DeathAge(InDeathAge), Type(InType), FoodType(InFoodType), FoodAmount(InFoodAmount), Reproduced(false),
	ColorAssigned(InColor), EntityGender(InGender)
{

}

Entity::~Entity()
{

}