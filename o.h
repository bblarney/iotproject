#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "util.h"
#include "i.h"

using namespace std;

class Order {
	string orderCustomer, orderProduct;
	vector<string> orderItemList;
public:
	Order();
	Order(vector<string> &line);
	void print();

	void graph(fstream& gv);
};

class OrderManager {
	vector<Order> orderList;

public:
	OrderManager();
	OrderManager(vector<vector<string>> & csvDataOrder);

	void print();

	void graph(string& f);

	bool validate(ItemManager& tm);
};