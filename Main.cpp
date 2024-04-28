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
	EcosystemManager->Init();

	while (true)
	{
		if (!EcosystemManager->SimulateEcosystem())
		{
			std::cout << "Simulation Over At Turn " << EcosystemManager->Turn << std::endl;
			break;
		}

		Sleep(10);
	}

	std::cout << "Entities remaing to garbage collect " << Ecosystem::GetEcosystem()->count << std::endl;
	delete EcosystemManager;
	return 0;
}