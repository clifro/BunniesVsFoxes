#include<iostream>
#include"Ecosystem.h"
#include"Entity.h"
#include <windows.h>

int main()
{
	std::cout << " Welcome to Bunnies Vs Foxes Ecosystem " << std::endl;
	Ecosystem* EcosystemManager = new Ecosystem();

	while (true)
	{
		if (!EcosystemManager->SimulateEcosystem())
		{
			std::cout << "Simulation Over!";
			break;
		}

		Sleep(10);
	}

	return 0;
}