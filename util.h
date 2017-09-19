#pragma once

//turn all csvread functions into prototypes

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void TrimSpaces(std::string& s);

void csvPrint(std::vector<std::vector<std::string>> &csvData);

void csvRead(std::string& filename, char delimiter, std::vector<std::vector<std::string>> &csvData);

bool validTaskName(std::string& s);
bool validSlots(std::string& s);

bool validSequence(std::string& s);
bool validItemName(std::string& s);