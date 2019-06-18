#ifndef HELPERFUNCTIONS_HPP
#define HELPERFUNCTIONS_HPP
#include <iostream>
#include "customObjects.hpp"
//gets the shortest line in multiple register scenario
int getShortestLineIndex(std::vector<registerInfo>& registers);
//overloaded for register exiting, one of multiline, one for single line.
void isAnyRegisterExiting(std::vector<registerInfo>& registers, int t, int lengthOfSimulation, int numberOfEmptyRegisters, statistics& statsInformation);
void isAnyRegisterExiting(std::vector<registerInfo>& registers, int t, int lengthOfSimulation, statistics& statsInformation);
//overloaded for moving customers from line to register, one for multiline one for single line.
void moveCustomersToEmptyRegisters(std::vector<registerInfo>& registers, int t, int& numberOfEmptyRegisters, statistics& statsInformation);
void moveCustomersToEmptyRegisters(std::vector<registerInfo>& registers, int t, statistics& statsInformation);
//prnints statistics ... called at the end of the LOG
void printStatistics(std::vector<registerInfo>& registers, statistics& statsInformation);
#endif //HELPERFUNCTIONS_HPP