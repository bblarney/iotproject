#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "util.h"
#include "t.h"

using namespace std;

	Task::Task() {

	}
	Task::Task(vector<string> &line) {
		/*for (auto & field : line) {
			cout << "%" << field << "%";
		}
		cout << "\n";*/

		switch (line.size()) {
		case 4:
			if (validTaskName(line[3]))
				taskFail = line[3];
			else
				throw string("Expected fail task name, found: ") + line[3];
		case 3:
			if (validTaskName(line[2]))
				taskPass = line[2];
			else
				throw string("Expected pass task name, found: ") + line[2];
		case 2:
			if (validSlots(line[1]))
				taskSlots = line[1];
			else
				throw string("Expected slots field, found: ") + line[1];
		case 1:
			if (validTaskName(line[0]))
				taskName = line[0];
			else
				throw string("Expected task name, found: ") + line[0];
		default:
			throw string("Expected 1, 2, 3, or 4 fields, found ") + to_string(line.size());
			break;
		}
	}
	void Task::print() {
		cout << "name = " << taskName << ", ";
		cout << "slots = " << taskSlots << ", ";
		cout << "pass = " << taskPass << ", ";
		cout << "fail = " << taskFail;
		cout << "\n";
	}

	void Task::graph(fstream& gv) {

		if (!taskPass.empty()) {
			gv << '"' << taskName << '"';
			gv << "->";
			gv << '"' << taskPass << '"';
			gv << "[color=green];\n";
		}

		if (!taskFail.empty()) {
			gv << '"' << taskName << '"';
			gv << "->";
			gv << '"' << taskFail << '"';
			gv << "[color=red];\n";
		}

		if (taskPass.empty() && taskFail.empty()) {
			gv << '"' << taskName << '"';
			gv << ";\n";
		}
	}

	TaskManager::TaskManager() {

	}
	TaskManager::TaskManager(vector<vector<string>> & csvDataTask) {
		for (auto & line : csvDataTask) {
			try {
				taskList.push_back(Task(line));
			}
			catch (string& e) {
				cerr << e << "\n";
			}
		}
	}

	void TaskManager::print() {
		for (auto& t : taskList) {
			t.print();
		}
	}

	void TaskManager::graph(string& f) {
		fstream gv(f + ".gv", ios::out | ios::trunc);

		if (gv.is_open()) {

			gv << "digraph taskgraph {\n";

			for (auto& t : taskList) {
				t.graph(gv);
			}
			gv << "}\n";
			gv.close();

			/*auto running the graph command
			string cmd = "dot";
			cmd += " -Tpng " + f + ".gv" + " > " + f + ".gv.png";
			cout << cmd << "\n";

			system(cmd.c_str());*/
		}
	}

	bool TaskManager::validate() {
		int errors = 0;

		for (auto& task : taskList) {
			string pass = task.pass();
			if (!pass.empty() && find(pass) == nullptr) {
				errors++;
				cerr << "Cannot find pass task " << pass << "\n";
			}
			string fail = task.fail();
			if (!fail.empty() && find(fail) == nullptr) {
				errors++;
				cerr << "Cannot find pass task " << fail << "\n";
			}
		}

		return errors == 0;
	}

	Task* TaskManager::find(string& t) {
		for (size_t i = 0; i < taskList.size(); i++) {
			if (taskList[i].name() == t)
				return &taskList[i];
			return nullptr;
		}
	}
