#include <iostream>
#include "sqlite3.h"
#include <string>
#include <ctime>
#include <vector>

using namespace std;

int callback(void* db, int argc, char** argv, char** azColName) {
	int i = 0;
	for (i = 0; i < argc; ++i) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	if (argv[i] == "NULL") return 0;
	else { return 1 ; };
}

void randAge(int &age, const int arr[], const int &size) {
	age = arr[rand() % size];
}

void randCountry(string& country, vector<string>& vec, const int &size) {
	country = vec[rand() % size];
}

void randName(string& first_name, string& second_name, const int &size) {
	for (int i = 0, j = 0; i < size; i++) {
		j = rand() % 10 + 1;

		if (j > size - i) j = size - i;
		i += j;

		for (int k = 0; k < j; k++) {
			first_name += (char)(rand() % 26 + 97);
			second_name += (char)(rand() % 26 + 97);
		}
	}
}

int main() {
	srand(time(NULL));
	sqlite3* db;
	sqlite3_stmt* stmt;

	string query;
	char* err;
	int rc;
	int count = 0;
	const int num_size = 84;
	const int let_size = 8;
	int numbers[num_size];

	vector<string> countrys = {"AUG", "AUT", "ARG", "BLR", "GTM", "DEU", "EGY", "RUS", "UKR", "USA", "JPN"};

	for (int i = 0, j = 16; i < num_size; ++i, ++j) {
		numbers[i] = j;
	}

	rc = sqlite3_open("Clients.db", &db);

	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return(1);
	}

	rc = sqlite3_exec(db, "SELECT COUNT(*) FROM clients", callback, &count, &err);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", err);
		sqlite3_free(err);
	}



	if (rc == 0) {
		cout << "fill db" << endl;
		for (int i = 0, j = 999999999; i < 10; ++i, ----j) {
			int age = 0;
			randAge(age, numbers, num_size);

			string sex;
			i % 3 == 0 ? sex = "female" : sex = "male";

			string first_name;
			string second_name;
			randName(first_name, second_name, let_size);

			string country;
			randCountry(country, countrys, countrys.size());

			query = "INSERT INTO clients (firstName, secondName, mail, phoneNumber, age, sex, country) VALUES ('" + first_name + "', '" + second_name + "', '" + second_name + "@mail.com', " + to_string(i + j) + ",  " + to_string(age) + ", '" + sex + "', '" + country + "');";
			rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &err);
		}
		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", err);
			sqlite3_free(err);
		}
	}
	
	rc = sqlite3_exec(db, "SELECT COUNT(*) FROM clients", callback, &count, &err);

	sqlite3_close(db);
	return 0;
}