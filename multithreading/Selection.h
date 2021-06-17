#pragma once
#include "Database.h"
#include <algorithm>

class Selection {
	Database* database = new Database();
	string query;
public:
	string solvent_clients_count;
	int solvent_clients_count_to_int;
	vector<string> country_id;
	vector<string> people_in_country;
	vector<string> five_countrys;
	vector<string> solvent_clients_id;
	void topFiveCountrys();
	void solventClients();
};