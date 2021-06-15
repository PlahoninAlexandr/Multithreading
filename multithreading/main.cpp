#include "Database.h"
#include "sqlite3.h"

using namespace std;

int callback(void* db, int argc, char** argv, char** azColName) {
	int i = 0;
	for (i = 0; i < argc; ++i) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	return 0; // сделать проверку если база данных пустая то нужно заполнить, если база данных заполнена - переход к следующему шагу
}

int main() {
	srand(time(NULL));

	Database* database = new Database();
	

	database->openDB();


	database->rc = sqlite3_exec(database->db, "SELECT COUNT(*) FROM clients", callback, &database->count, &database->err);

	if (database->rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", database->err);
		sqlite3_free(database->err);
	}

	if (database->rc == 0) {
		database->fillNumbers();
		database->fillDatabase();
		database->rc = sqlite3_exec(database->db, "SELECT COUNT(*) FROM clients", callback, &database->count, &database->err);
	}


	database->closeDB();

	delete database;

	return 0;
}