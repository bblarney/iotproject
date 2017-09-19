#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "util.h"
#include "t.h"

using namespace std;

class Item {
	string itemName, itemInstallerTask, itemRemoverTask, itemSequence, itemDescription;
public:
	string& name     () { return itemName; }
	string& installer() { return itemInstallerTask; }
	string& remover  () { return itemRemoverTask; }

	Item();

	Item(vector<string> &line);
	void print();

	void graph(fstream& gv);
};

class ItemManager {
	vector<Item> itemList;

public:
	ItemManager();
	ItemManager(vector<vector<string>> & csvDataItem);

	void print();

	void graph(string& f);

	bool validate(TaskManager& tm);

	Task* find(string& t);
};