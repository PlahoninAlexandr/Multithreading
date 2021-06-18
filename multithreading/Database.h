#pragma once
#include <iostream>
#include "sqlite3.h"
#include <string>
#include <ctime>
#include <vector>

using namespace std;

class Database {
private:
	string query;
	static const int num_size = 84;
	const int let_size = 8;
	const int size_db = 1000;
	int numbers[num_size];
public:
	vector<string> countrys = { "AUG", "AUT", "ARG", "BLR", "GTM", "DEU", "EGY", "RUS", "UKR", "USA", "JPN" };
	sqlite3* db;
	sqlite3_stmt* stmt;
	char* err;
	int rc;
	int count = 0;
	void closeDB();
	int openDB();
	void fillNumbers();
	void fillDatabase();
	int getSizeDB();
private:
	void randAge(int& age, const int arr[], const int& size);
	void randCountry(string& country, vector<string>& vec, const int& size);
	void randName(string& first_name, string& second_name, const int& size);
};