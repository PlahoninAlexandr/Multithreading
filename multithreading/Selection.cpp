#include "Selection.h"

void Selection::topFiveCountrys() {
	vector<int> vec;
	int* tmp = new int;

	for (int i = 0; i < people_in_country.size(); i++) {
		*tmp = stoi(people_in_country[i]);
		vec.push_back(*tmp);
	}

	cout << endl;

	for (int i = 0; i < 5; i++) {
		auto it = vec.begin();
		*tmp = distance(vec.begin(), max_element(vec.begin(), vec.end()));
		five_countrys.push_back(database->countrys[*tmp]);
		advance(it, *tmp);
		*it = 0;
	}

	for (int i = 0; i < five_countrys.size(); i++) {
		cout << five_countrys[i] << " ";
	}
	cout << endl;

	delete tmp;
}

void Selection::solventClients() {
	solvent_clients_count_to_int = stoi(solvent_clients_count);

	cout << solvent_clients_count_to_int << endl;

	for (int i = 0; i < solvent_clients_count_to_int; i++) {
		cout << solvent_clients_id[i] << " ";
	}
}