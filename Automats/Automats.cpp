#include "KDA.h"
#include "KNA.h"
#include "EKNA.h"
#include <iostream>
#include <fstream>
#include <memory>

int main()
{
	EKNA automat;

	std::ifstream in("inputEKNA.txt");

	automat.Prepare(in);

	int numRecords;
	in >> numRecords;
	for (int i = 0; i < numRecords; ++i)
	{
		std::string stateKey, symbolKey, stateValue;
		in >> stateKey >> symbolKey >> stateValue;
		auto pairTable = std::make_pair(Key(stateKey, symbolKey), stateValue);
		std::shared_ptr<std::pair<Key, std::string>> arg(new std::pair<Key, std::string>(pairTable));
		automat.Insert(arg.get());
	}

	automat.HandleWord();
	automat.DisplayTable();

	KNA kna = automat.Eclose();
	kna.HandleWord();
	kna.DisplayTable();

	KDA kda = kna.AlgorithmTompson();
	kda.HandleWord();
	kda.DisplayTable();
}
