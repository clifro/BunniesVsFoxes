#include"Entity.h"
 
Entity::Entity()
{

}

Entity::Entity(EntityType InType, const std::string& InName, 
	int InReproduceAge, int InDeathAge, 
	int InFoodAmount, EntityType InFoodType, 
	Gender InGender, Color InColor) :
	RemainingTurns(-1), ReproduceAge(InReproduceAge), Age(0), DeathAge(InDeathAge), Name(InName), 
	Type(InType), FoodType(InFoodType), FoodAmount(InFoodAmount), Reproduced(false),
	ColorAssigned(InColor), EntityGender(InGender)
{

}

Entity::~Entity()
{

}