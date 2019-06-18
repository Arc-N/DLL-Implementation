#ifndef CUSTOMOBJECTS_HPP
#define CUSTOMOBJECTS_HPP
#include <vector>
#include "Queue.hpp"
#include "DoublyLinkedList.hpp"
//Holds the stats information. 
struct statistics
{
	int enteredLine;
	int exitedLine;
	int exitedRegister;
	std::vector<int> avgWaitTime;
	int leftInLine;
	int leftInRegister;
	int lost;
};
//Register info holds information about lines and wait times
struct registerInfo
{
	Queue<int> line;
	DoublyLinkedList<int> waitTime;
	int queueSize;
	int time;
	int ptime;
	bool empty;
};
//Customer info is used to read the second part of input.
struct customerInfo
{
	int numberOfCustomersEntered;
	int timeOfCustomersEntered;
};
#endif //CUSTOMOBJECTS_HPP