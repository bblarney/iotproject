#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "util.h"

using namespace std;

class Task {
	string taskName, taskSlots = "1", taskPass, taskFail;
public:
	string& pass() { return taskPass; }
	string& fail () { return taskFail; }
	string& name() { return taskName; }

	Task();
	Task(vector<string> &line);
	void print();

	void graph(fstream& gv);
};

class TaskManager {
	vector<Task> taskList;

public:
	TaskManager();
	TaskManager(vector<vector<string>> & csvDataTask);

	void print();

	void graph(string& f);

	bool validate();

	Task* find(string& t);
};