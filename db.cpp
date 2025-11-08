#include "db.h"
#include <memory>
#include <stdexcept>

//Create a smart pointer so that it will be automatically deleted after the program is killed
//This is also the global variable so that the other classes can use the connection without being affected by the scope limitation
static std::unique_ptr<pqxx::connection> g_conn;

//This function uses the string argument (all the infos to connect to the db) to make a connection
void initDB(const std::string& connection_str) {
    //Make a connection
    g_conn = std::make_unique<pqxx::connection>(connection_str);
    if (!g_conn->is_open())
        throw std::runtime_error("Failed to open DB connection");
}

//Dereference the pointer and return the connection.
pqxx::connection& DB() {
    if (!g_conn || !g_conn->is_open())
        throw std::runtime_error("DB not initialized");
    return *g_conn;
}
