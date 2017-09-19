#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "util.h"

#include "i.h"

using namespace std;

	Item::Item() {

	}
	Item::Item(vector<string> &line) {
		/*for (auto & field : line) {
		cout << "%" << field << "%";
		}
		cout << "\n";*/

		switch (line.size()) {
		case 5:
			itemDescription = line[4];
		case 4:
			if (validSequence(line[3]))
				itemSequence = line[3];
			else
				throw string("Expected sequence number, found: ") + line[3];

			if (validTaskName(line[2]))
				itemRemoverTask = line[2];
			else
				throw string("Expected remover task name, found: ") + line[2];

			if (validTaskName(line[1]))
				itemInstallerTask = line[1];
			else
				throw string("Expected installer task name, found: ") + line[1];

			if (validItemName(line[0]))
				itemName = line[0];
			else
				throw string("Expected item name, found: ") + line[0];

			break;
		default:
			throw string("Expected 1, 2, 3, or 4 fields, found ") + to_string(line.size());
			break;
		}
	}
	void Item::print() {
		cout << "name = " << itemName << ", ";
		cout << "installer = " << itemInstallerTask << ", ";
		cout << "remover = " << itemRemoverTask << ", ";
		cout << "sequence = " << itemSequence << ", ";
		cout << "description = " << itemDescription;

		cout << "\n";
	}

	void Item::graph(fstream& gv) {

		gv << '"' << "Item\n" << itemName << '"';
		gv << "->";
		gv << '"' << "Installer\n" << itemInstallerTask << '"';
		gv << "[color=green];\n";


		gv << '"' << "Item\n" << itemName << '"';
		gv << "->";
		gv << '"' << "Remover\n" << itemRemoverTask << '"';
		gv << "[color=red];\n";
	}


	ItemManager::ItemManager() {

	}
	ItemManager::ItemManager(vector<vector<string>> & csvDataItem) {
		for (auto & line : csvDataItem) {
			try {
				itemList.push_back(Item(line));
			}
			catch (string& e) {
				cerr << e << "\n";
			}
		}
	}

	void ItemManager::print() {
		for (auto& t : itemList) {
			t.print();
		}
	}

	void ItemManager::graph(string& f) {
		fstream gv(f + ".gv", ios::out | ios::trunc);

		if (gv.is_open()) {

			gv << "digraph itemgraph {\n";

			for (auto& t : itemList) {
				t.graph(gv);
			}
			gv << "}\n";
			gv.close();

			//auto running the graph command
			string cmd = "dot";
			cmd += " -Tpng " + f + ".gv" + " > " + f + ".gv.png";
			cout << cmd << "\n";

			system(cmd.c_str());
		}
	}

	bool ItemManager::validate(TaskManager& tm) {
		int errors = 0;

		for (auto& item : itemList) {
			string installer = item.installer();
			if (find(installer) == nullptr) {
				errors++;
				cerr << "Cannot find installer task " << installer << "\n";
			}
			string remover = item.remover();
			if (tm.find(remover) == nullptr) {
				errors++;
				cerr << "Cannot find remover task " << remover << "\n";
			}
		}

		return errors == 0;
	}

	Task* ItemManager::find(string& i) {
		for (size_t item = 0; item < itemList.size(); item++) {
			if (itemList[item].name() == i)
				return &itemList[item];
			return nullptr;
		}
	}

