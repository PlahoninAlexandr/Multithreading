#include "Selection.h"

void Selection::topFiveCountrys() {
	cout << endl << "Top 5 countries with the largest number of solvent clients:" << endl;

	vector<int> vec;
	int* tmp = new int;

	for (int i = 0; i < people_in_country.size(); i++) {
		*tmp = stoi(people_in_country[i]);
		vec.push_back(*tmp);
	}

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

	cout << endl << endl;

	delete tmp;
}

void Selection::solventClients() {
	cout << "The number of all solvent clients and their id:" << endl;

	solvent_clients_count_to_int = stoi(solvent_clients_count);

	cout << solvent_clients_count_to_int << endl;

	for (int i = 0; i < solvent_clients_count_to_int; i++) {
		cout << solvent_clients_id[i] << " ";
	}

	cout << endl << endl;
}

void Selection::countMaleAndFemale() {
	cout << "Number of male clients and their id:" << endl;

	stoi(male_count);
	cout << male_count << endl;

	for (int i = 0; i < stoi(male_count); i++) {
		cout << male_clients_id[i] << " ";
	}

	cout << endl << endl;

	cout << "Number of male clients and their id:" << endl;

	stoi(female_count);
	cout << female_count << endl;

	for (int i = 0; i < stoi(female_count); i++) {
		cout << female_clients_id[i] << " ";
	}

	cout << endl << endl;
}