#include "Database.h"
#include "sqlite3.h"
#include "Selection.h"
#include "Timer.h"
#include <thread>
#include <mutex>
#include <fstream>

int callback(void* db, int argc, char** argv, char** azColName) {
	for (int i = 0; i < argc; ++i) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	return 0; // сделать проверку если база данных пустая то нужно заполнить, если база данных заполнена - переход к следующему шагу
}

int callback_v2(void* p, int size, char** column_text, char** column_name) {
	if (size == 0) return -1;
	auto& container = *static_cast<vector<string>*>(p);
	if (!column_text[0]) container.push_back("NULL");
	else container.push_back(column_text[0]);
	return 0;
}

int callback_v2_single(void* p, int size, char** column_text, char** column_name) {
	for (int i = 0; i < size; ++i) {
		auto& container = *static_cast<string*>(p);
		container = column_text[0];
		return 0;
	}
}

void getIdAndCount(Database* database, Selection* selection) {	// количество клиентов из каждой страны и их id
	string sql;
	for (int i = 0; i < database->countrys.size(); i++) {
		sql = "SELECT COUNT(*) FROM clients WHERE (country = '" + database->countrys[i] + "');";
		database->rc = sqlite3_exec(database->db, sql.c_str(), callback_v2, &selection->people_in_country, &database->err);
	}
	for (int i = 0; i < database->countrys.size(); i++) {
		sql = "SELECT id FROM clients WHERE (country = '" + database->countrys[i] + "');";
		database->rc = sqlite3_exec(database->db, sql.c_str(), callback_v2, &selection->country_id, &database->err);
	}
}

void getSolventPeopleIdAndCount(Database* database, Selection* selection) {	// количество платёжеспосообных клиентов и их id
	string sql = "SELECT COUNT(*) FROM clients WHERE age > 21 and age < 64";
	database->rc = sqlite3_exec(database->db, sql.c_str(), callback_v2_single, &selection->solvent_clients_count, &database->err);

	for (int i = 0; i < database->countrys.size(); i++) {
		sql = "SELECT id FROM clients WHERE age > 21 and age < 64";
		database->rc = sqlite3_exec(database->db, sql.c_str(), callback_v2, &selection->solvent_clients_id, &database->err);
	}
}

void getCountMaleAndFemale(Database* database, Selection* selection) {
	string sql = "SELECT COUNT(*) FROM clients WHERE sex = 'male'";
	database->rc = sqlite3_exec(database->db, sql.c_str(), callback_v2_single, &selection->male_count, &database->err);

	sql = "SELECT COUNT(*) FROM clients WHERE sex = 'female'";
	database->rc = sqlite3_exec(database->db, sql.c_str(), callback_v2_single, &selection->female_count, &database->err);

	for (int i = 0; i < database->countrys.size(); i++) {
		sql = "SELECT id FROM clients WHERE sex = 'male'";
		database->rc = sqlite3_exec(database->db, sql.c_str(), callback_v2, &selection->male_clients_id, &database->err);
	}

	for (int i = 0; i < database->countrys.size(); i++) {
		sql = "SELECT id FROM clients WHERE sex = 'female'";
		database->rc = sqlite3_exec(database->db, sql.c_str(), callback_v2, &selection->female_clients_id, &database->err);
	}
}

mutex mtx;

int main() {
	Timer timer;
	srand(time(NULL));
	
	Database* database = new Database();
	Selection* selection = new Selection();

	database->openDB();
	
	database->rc = sqlite3_exec(database->db, "SELECT COUNT(*) FROM clients", callback, &database->count, &database->err);

	if (database->rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", database->err);
		sqlite3_free(database->err);
	}

	if (database->rc == SQLITE_OK) {
		database->fillNumbers();
		database->fillDatabase();
		database->rc = sqlite3_exec(database->db, "SELECT COUNT(*) FROM clients", callback, &database->count, &database->err);
	}	

	thread th1(getIdAndCount, database, selection);
	thread th2(getSolventPeopleIdAndCount, database, selection);
	thread th3(getCountMaleAndFemale, database, selection);

	th1.join();
	thread th4([&]() {selection->topFiveCountrys(); });

	th2.join();
	th4.join();
	thread th5([&]() {selection->solventClients(); });
	

	th3.join();
	th5.join();
	thread th6([&]() {selection->countMaleAndFemale(); });
	th6.join();	
	

	ofstream* f_out = new ofstream;
	
	f_out->open("Statistics.txt", ofstream::app);

	if (!f_out->is_open()) {
		cout << endl << "file open error!!!" << endl;
	}

	f_out->close();
	database->closeDB();

	delete database;
	delete selection;
	delete f_out;

	return 0;
}

// 290.849 seconds

// 297.265 seconds

//  0.496443 seconds multi

// 0.596468 seconds single