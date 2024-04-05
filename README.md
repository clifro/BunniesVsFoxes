# BunniesVsFoxes
---

## Intro

* Our world consists of foxes, rabbits and grass
* Rabbits eat grass, foxes eat rabbits
* The interactions between these 3 elements aren't linear, read the rules below carefully

## Evolution rules

* At program initialization 5 bunnies must be created and given random colors.
* Each turn afterwards the bunnies age 1 year.
* So long as there is at least one male age 2 or older,
  * for each female bunny in the list age 2 or older;
    * a new bunny is created each turn. (i.e. if there was 1 adult male and 3 adult female bunnies, three new bunnies would be born each turn)
* More male adults do not increase the number of rabbits born.
* New bunnies born should be the same color as their mother.
* If a bunny becomes older than 10 years old, it dies.
* There's a 2% chance that a radioactive mutant vampire bunny is born
* Radioactive rabbits will bite and change exactly one non radioactive bunny into a radioactive vampire bunny every year.
  * (if there are two radioactive mutant vampire bunnies two bunnies will be changed each turn and so on...)
* Radioactive vampire bunnies are excluded from regular breeding and do not count as adult bunnies.
* Radioactive vampire bunnies do not die until they reach age 50.
* The program should print a list of all the bunnies in the colony each turn along w/ all the bunnies details, sorted by age.
* The program should also output each turns events such as `Bunny Thumper was born!`, `Bunny Fufu was born!`, `Radioactive Mutant Vampire Bunny Darth Maul was born!`, `Bunny Julius Caesar died!`
* When all the bunnies have died the program terminates.
  * If the bunny population exceeds 1000 a food shortage must occur killing exactly half of the bunnies (randomly chosen)


## Foxes & grass

* The forest has a maximum of 500 grass units
* Every rabbit eats 2 units of grass every turn
  * Vampire rabbits eat 4 units of grass every turn
* If there isn't enough grass for all rabbits, all rabbits that don't have enough food, die
* Every turn 10 unit of grass grows back

* Every fox eats 1 unit rabbit every turn, at random
  * If there aren't enough rabbits for all foxes, all foxes that don't have enough food, die
  * If grass is less than 20% of max, every fox has a 50% chance to eat an additional rabbit
* For every **pair of male & female fox**, a new baby fox is born
* Foxes live up to 20 years old and they can't be vampires
* If a fox eats a vampire rabbit, it has 30% chance of death
* When a rabbit is eaten by a fox, it becomes a ghost and haunts its murderer
  * Haunted foxes cannot give birth for 5 turns
  * When the 5 turns expire, "Ghost rabbit X goes to the afterlife!" - needs to be printed on screen.
* The mother of a ghost, if she is still alive, after the ghost goes to the afterlife print the message "Mother X finally accepts the death of Y"

! Fox can hunt at age of 2
! Vampire rabbit when eaten don't became ghost
