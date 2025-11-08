#ifndef UNTITLED_DB_H
#define UNTITLED_DB_H
#include <pqxx/pqxx>
#include <string>

// Call once at startup
void initDB(const std::string& connection_str);

// Get the live connection (throws if not initialized)
pqxx::connection& DB();
#endif //UNTITLED_DB_H