#include "helperFunctions.hpp"
#include <iomanip>
//takes in registers information and returns the line which is the shortest.
int getShortestLineIndex(std::vector<registerInfo>& registers)
{
	int shortest = 0;
	for (int i = 1; i < registers.size(); i++)
	{
		if (registers[i].queueSize < registers[shortest].queueSize)
		{
			shortest = i;
		}
	}
	return shortest;
}
//if any register is going to exit at the given time t, this performs necessary actions. for multiline
void isAnyRegisterExiting(std::vector<registerInfo>& registers, int t, int lengthOfSimulation, int numberOfEmptyRegisters, statistics& statsInformation)
{
	for (int k = 0; k < registers.size(); ++k)
	{
		if (t - registers[k].ptime == registers[k].time)
		{
			registers[k].empty = true;
			registers[k].ptime = lengthOfSimulation * 60;
			std::cout << t << " exited register " << k+1 << std::endl;
			statsInformation.exitedRegister++;
			moveCustomersToEmptyRegisters(registers, t, numberOfEmptyRegisters, statsInformation);
		}
	}
}
//if any register is going to exit at the given time t, this performs necessary actions. for single line
void isAnyRegisterExiting(std::vector<registerInfo>& registers, int t, int lengthOfSimulation, statistics& statsInformation)
{
	for (int k = 0; k < registers.size(); ++k)
	{
		if (t - registers[k].ptime == registers[k].time)
		{
			registers[k].empty = true;
			registers[k].ptime = lengthOfSimulation * 60;
			std::cout << t << " exited register " << k+1 << std::endl;
			statsInformation.exitedRegister++;
			moveCustomersToEmptyRegisters(registers, t, statsInformation);
		}
	}
}
//moves customers to empty registers if there are empty registers for multiline
void moveCustomersToEmptyRegisters(std::vector<registerInfo>& registers, int t, int& numberOfEmptyRegisters, statistics& statsInformation)
{
	for (int i = 0; i < registers.size(); i++)
	{
		if (registers[i].empty && registers[i].queueSize != 0)
		{
			registers[i].line.dequeue();
			registers[i].queueSize--;
			std::cout << t << " exited line "<< i+1 <<" length " << registers[i].queueSize << " wait time " << t - registers[i].waitTime.first() << std::endl;
			statsInformation.avgWaitTime.push_back(t - registers[i].waitTime.first());
			statsInformation.exitedLine++;
			registers[i].waitTime.removeFromStart();
			std::cout << t << " entered register " << i+1 << std::endl;
			registers[i].empty = false;
			registers[i].ptime = t;
			numberOfEmptyRegisters--;
			if(registers[i].time == 0)
			isAnyRegisterExiting(registers, t, 1000, numberOfEmptyRegisters, statsInformation);
		}
	}
}
//moves customers to empty registers if there are empty registers for single line
void moveCustomersToEmptyRegisters(std::vector<registerInfo>& registers, int t, statistics& statsInformation)
{
	for (int k = 0; k < registers.size(); ++k)
	{
		if (registers[k].empty && registers[0].queueSize != 0)
		{
			registers[0].line.dequeue();
			registers[0].queueSize--;
			std::cout << t << " exited line 1 length " << registers[0].queueSize << " wait time " << t - registers[0].waitTime.first() << std::endl;
			statsInformation.avgWaitTime.push_back(t-registers[0].waitTime.first());
			statsInformation.exitedLine++;
			registers[0].waitTime.removeFromStart();
			std::cout << t << " entered register " << k+1 << std::endl;
			registers[k].empty = false;
			registers[k].ptime = t;
			if(registers[k].time == 0)
			isAnyRegisterExiting(registers, t, 1000, statsInformation);
		}
	}
}
void printStatistics(std::vector<registerInfo>& registers, statistics& statsInformation)
{
	//LOG ENDED calculate statistics.
	for (int i = 0; i < registers.size(); ++i)
	{
		statsInformation.leftInLine += registers[i].queueSize;
		if(!registers[i].empty)
		{
			statsInformation.leftInRegister++;
		}
	}
	double avgWaitTime = 0;
	for (int i = 0; i < statsInformation.avgWaitTime.size(); ++i)
	{
		avgWaitTime += statsInformation.avgWaitTime[i];
	}
	avgWaitTime /= statsInformation.avgWaitTime.size();
	std::cout << "\nSTATS" << std::endl;
	std::cout << "Entered Line    : " << statsInformation.enteredLine << std::endl;
	std::cout << "Exited Line     : " << statsInformation.exitedLine << std::endl;
	std::cout << "Exited Register : " << statsInformation.exitedRegister << std::endl;
	std::cout << "Avg Wait Time   : " << std::setprecision(4) << avgWaitTime << std::endl;
	std::cout << "Left In Line    : " << statsInformation.leftInLine << std::endl;
	std::cout << "Left In Register: " << statsInformation.leftInRegister << std::endl;
	std::cout << "Lost            : " << statsInformation.lost << std::endl;
}