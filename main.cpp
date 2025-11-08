#include <iostream>
#include "db.h"
#include "view.h"

int main() {
    try {
        //Connect to the local db
        initDB("host=localhost port=5432 dbname=COMP3005_A3_Q1 user=postgres password=HQVinh2803<3 sslmode=disable");
        std::cout << "Connected to: " << DB().dbname() << "\n";

        View view;
        view.displayView();

        //Catch error if the connection is failed
    } catch (const std::exception& e) {
        std::cerr << "DB error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
