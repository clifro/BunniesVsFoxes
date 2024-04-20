#include<iostream>
#include"Ecosystem.h"
#include"Entity.h"
#include<windows.h>
#include<time.h>

int main()
{
	srand(time(NULL));
	std::cout << " Welcome to Bunnies Vs Foxes Ecosystem " << std::endl;
	Ecosystem* EcosystemManager = Ecosystem::GetEcosystem();

	while (true)
	{
		if (!EcosystemManager->SimulateEcosystem())
		{
			std::cout << "Simulation Over At Turn " << EcosystemManager->Turn << std::endl;
			break;
		}

		Sleep(10);
	}

	delete EcosystemManager;
	return 0;
}