//Arman Arakelyan
#include "helperFunctions.hpp"
int main()
{
	int lengthOfSimulation = 0, numberOfRegisters = 0, maximumLineLength = 0;
	char arrangmentSelector = '\0';
	std::cin >> lengthOfSimulation >> numberOfRegisters >> maximumLineLength;
	std::cin >> arrangmentSelector;
	//==================================================Single Line==============================================
	if (arrangmentSelector == 'S')
	{
		statistics statsInformation{0};
		DoublyLinkedList<customerInfo> cInfo;
		std::vector<registerInfo> registers(numberOfRegisters);
		//fill in registers with their service time
		for (int i = 0; i < numberOfRegisters; ++i)
		{
			std::cin >> registers[i].time;
			registers[i].empty = true;
			registers[i].ptime = lengthOfSimulation * 60;
		}
		//fill in customer information into corresponding linked list.
		customerInfo temp;
		std::cin >> temp.numberOfCustomersEntered >> temp.timeOfCustomersEntered;
		cInfo.addToEnd(temp);
		//read customer input untill END
		while (!std::cin.fail())
		{
			std::cin >> temp.numberOfCustomersEntered >> temp.timeOfCustomersEntered;
			cInfo.addToEnd(temp);
		}
		//Start log
		std::cout << "\nLOG" << std::endl;
		std::cout << "0 start" << std::endl;
		for (int t = 0; t < lengthOfSimulation * 60; ++t)
		{
			if (t == cInfo.first().timeOfCustomersEntered)
			{
				for (int j = 0; j < cInfo.first().numberOfCustomersEntered; ++j)
				{
					if (registers[0].queueSize != maximumLineLength)
					{
						registers[0].line.enqueue(registers[0].queueSize);
						registers[0].queueSize++;
						registers[0].waitTime.addToEnd(t);
						std::cout << t << " entered line 1 length " << registers[0].queueSize << std::endl;
						statsInformation.enteredLine++;
					}
					else if (registers[0].queueSize == maximumLineLength)
					{
						std::cout << t << " lost" <<std::endl;
						statsInformation.lost++;
					}
				}
				cInfo.removeFromStart();
			}
			if (registers[0].queueSize != 0)
			{
				moveCustomersToEmptyRegisters(registers, t, statsInformation);
			}
			isAnyRegisterExiting(registers, t, lengthOfSimulation, statsInformation);
		}
		std::cout << lengthOfSimulation*60 << " end" << std::endl;
		printStatistics(registers, statsInformation);
	}
	//==================================================Multi Line==============================================
	else
	{
		statistics statsInformation{0};
		int numberOfEmptyRegisters = numberOfRegisters;
		DoublyLinkedList<customerInfo> cInfo;
		std::vector<registerInfo> registers(numberOfRegisters);
		//fill in registers with their service time
		for (int i = 0; i < numberOfRegisters; ++i)
		{
			std::cin >> registers[i].time;
			registers[i].empty = true;
			registers[i].ptime = lengthOfSimulation * 60;
		}
		//push customer info into linked list cInfo
		customerInfo temp;
		std::cin >> temp.numberOfCustomersEntered >> temp.timeOfCustomersEntered;
		cInfo.addToEnd(temp);
		//read input untill END
		while (!std::cin.fail())
		{
			std::cin >> temp.numberOfCustomersEntered >> temp.timeOfCustomersEntered;
			cInfo.addToEnd(temp);
		}
		//start LOG
		std::cout << "\nLOG" << std::endl;
		std::cout << "0 start" << std::endl;
		for (int t = 0; t < lengthOfSimulation * 60; ++t)
		{
			if (t == cInfo.first().timeOfCustomersEntered)
			{
				for (int j = 0; j < cInfo.first().numberOfCustomersEntered; ++j)
				{
					int shortestLineIndex = getShortestLineIndex(registers);
					if (registers[shortestLineIndex].queueSize != maximumLineLength)
					{
						registers[shortestLineIndex].line.enqueue(registers[shortestLineIndex].queueSize);
						registers[shortestLineIndex].queueSize++;
						registers[shortestLineIndex].waitTime.addToEnd(t);
						std::cout << t << " entered line " << shortestLineIndex+1 << " length " << registers[shortestLineIndex].queueSize << std::endl;
						statsInformation.enteredLine++;
					}
					else if (registers[shortestLineIndex].queueSize == maximumLineLength)
					{
						std::cout << t << " lost" << std::endl;
						statsInformation.lost++;
					}
				}
				cInfo.removeFromStart();
			}
			if(numberOfEmptyRegisters) //if there are not empty registers don't bother trying to move customers into empty registers.
			{
				moveCustomersToEmptyRegisters(registers, t, numberOfEmptyRegisters, statsInformation);
			}
			isAnyRegisterExiting(registers, t, lengthOfSimulation, numberOfEmptyRegisters, statsInformation); //Check if any registers are going to finish at t
		}
		std::cout << lengthOfSimulation*60 << " end" << std::endl;
		printStatistics(registers, statsInformation);
	}
	return 0;
}
