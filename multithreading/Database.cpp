#include "Database.h"

int Database::openDB() {
	rc = sqlite3_open("Clients.db", &db);

	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return(0);
	}
}

void Database::fillNumbers() {
	for (int i = 0, j = 16; i < num_size; ++i, ++j) {
		numbers[i] = j;
	}
}

void Database::randAge(int& age, const int arr[], const int& size) {
	age = arr[rand() % size];
}

void Database::randCountry(string& country, vector<string>& vec, const int& size) {
	country = vec[rand() % size];
}

void Database::randName(string& first_name, string& second_name, const int& size) {
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

void Database::fillDatabase() {
	cout << "fill db" << endl;
	for (int i = 0, j = 999999999; i < size_db; ++i, ----j) {
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

void Database::closeDB() {
	sqlite3_close(db);
}

int Database::getSizeDB() {
	return size_db;
}