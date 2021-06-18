#pragma once
#include "Database.h"
#include <algorithm>

class Selection {
	Database* database = new Database();
	string query;
	int solvent_clients_count_to_int;
public:
	string solvent_clients_count;
	string male_count;
	string female_count;
	vector<string> country_id;
	vector<string> people_in_country;
	vector<string> five_countrys;
	vector<string> solvent_clients_id;
	vector<string> male_clients_id;
	vector<string> female_clients_id;
	void topFiveCountrys();
	void solventClients();
	void countMaleAndFemale();
};