#include "o.h"

using namespace std;

	Order::Order() {

	}
	Order::Order(vector<string> &line) {
		/*for (auto & field : line) {
		cout << "%" << field << "%";
		}
		cout << "\n";*/

		if (line.size() < 3) {
			throw string("Expected at least 3 fields, found: ") + to_string(line.size());
		}

		orderCustomer = line[0];
		orderProduct = line[1];

		for (size_t item = 2; item < line.size(); item++) {
			if (validItemName(line[item])) {
				orderItemList.push_back(line[item]);
			}
		}
	}
	void Order::print() {
		cout << "customer = " << orderCustomer << ", ";
		cout << "product = " << orderProduct;

		for (size_t i = 0; i < orderItemList.size(); i++)
			cout << ", " << orderItemList[i];

		cout << "\n";
	}

	void Order::graph(fstream& gv) {

		for (auto& item : orderItemList) {
			gv << '"' << orderCustomer << "\n" << orderProduct << '"';
			gv << "->";
			gv << '"' << "Item\n" << item << '"';
			gv << "[color=blue];\n";
		}
	}

	OrderManager::OrderManager() {

	}
	OrderManager::OrderManager(vector<vector<string>> & csvDataOrder) {
		for (auto & line : csvDataOrder) {
			try {
				orderList.push_back(Order(line));
			}
			catch (string& e) {
				cerr << e << "\n";
			}
		}
	}

	void OrderManager::print() {
		for (auto& t : orderList) {
			t.print();
		}
	}

	void OrderManager::graph(string& f) {
		fstream gv(f + ".gv", ios::out | ios::trunc);

		if (gv.is_open()) {

			gv << "digraph ordergraph {\n";

			for (auto& t : orderList) {
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

	bool OrderManager::validate(ItemManager& im) {
		int errors = 0;

		for (auto& o : orderList) {

			for (size_t i = 0; i < o.count(); i++) {
				if (im.find(o.item(i)) == nullptr) {
					errors++;
					cerr << "Someone ordered '" << o.item[i] << "\n" << "' but cannot find item.\n";
				}
			}
		}

		return errors == 0;
	}
