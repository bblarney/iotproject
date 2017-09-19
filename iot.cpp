#include "util.h"
#include "i.h"
#include "o.h"
#include "t.h"

using namespace std;

int main(int argc, char* argv[]) {
	//0 - program name, 1 - file name, 2 - seperator

	if (argc != 5) {
		cerr << "Usage: " << argv[0] << " item-file-name order-file-name task-file-name delimiter-character\n";
		return 1;
	}

	string filenameTask = argv[1];
	string filenameItem = argv[2];
	string filenameOrder = argv[3];

	char delimiter = argv[4][0];

	try {
		vector < vector<string>> csvDataItem;
		vector < vector<string>> csvDataOrder;
		vector < vector<string>> csvDataTask;
		
		//csvPrint(csvDataTask);
		csvRead(filenameItem, delimiter, csvDataItem);
		//csvPrint(csvDataItem);
		csvRead(filenameOrder, delimiter, csvDataOrder);
		//csvPrint(csvDataOrder);
		csvRead(filenameTask, delimiter, csvDataTask);

		ItemManager im(csvDataItem);
		im.print();
		im.graph(filenameItem);

		OrderManager om(csvDataOrder);
		om.print();
		om.graph(filenameOrder);

		TaskManager tm(csvDataTask);	
		tm.print();
		tm.graph(filenameTask);

		im.validate(tm);
		om.validate(im);
		tm.validate();
	}
	catch (const string& e) {
		cerr << "It threw: '" + e + "'\n";
	}

}