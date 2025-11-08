#include "manageStudentControl.h"

void ManageStudentControl::getAllStudent() const {
    try {
        //Create a transaction from the connection given by db.h
        pqxx::read_transaction tx(DB());

        //Make a query
        auto rows = tx.exec(
            "SELECT student_id, first_name, last_name, email, enrollment_date "
            "FROM students ORDER BY student_id;"
        );

        if (rows.empty()) {
            cout << "No students found.\n";
            return;
        }

        //Display the data
        for (const auto& r : rows) {
            cout << "Student ID: "      << r["student_id"].as<int>() << "\n"
                      << "First Name: "      << r["first_name"].as<string>() << "\n"
                      << "Last Name: "       << r["last_name"].as<string>() << "\n"
                      << "Email: "           << r["email"].as<string>() << "\n"
                      << "Enrollment Date: " << r["enrollment_date"].as<string>() << "\n"
                      << "------------------------------------------\n";
        }

        //Catch error if the query is failed
    } catch (const pqxx::sql_error& e) {
        cerr << "SQL error: " << e.what() << "\nQuery: " << e.query() << "\n";

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
    }
}

void ManageStudentControl::addStudent(const string& first_name, const string& last_name, const string& email, const string& enrollment_date) {


    try {
        //Create a transaction
        pqxx::work tx(DB());

        //Execute the querry with the inputed values
        tx.exec_params(
            "INSERT INTO students (first_name, last_name, email, enrollment_date) "
            "VALUES ($1, $2, $3, $4::date);",
            first_name,last_name, email, enrollment_date
        );

        //Commit the transaction. If not, PostgreSQL automatically rolls back the transaction when it ends.
        tx.commit();
        std::cout << "Student added.\n";

        //Catch error
    } catch (const pqxx::sql_error& e) {
        std::cerr << "SQL error: " << e.what() << "\nQuery: " << e.query() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void ManageStudentControl::updateStudentEmail(int student_id, const string& new_email){


    try {
        pqxx::work tx(DB());

        //Update the student's email
        pqxx::result r = tx.exec_params(
           "UPDATE students "
           "SET email = $1 "
           "WHERE student_id = $2 "
           "RETURNING student_id;",   // To check if something was updated
           new_email, student_id
       );

        //Commit the transaction
        tx.commit();

        if (r.empty()) {
            std::cout << "No student found with ID " << student_id << ".\n";
        } else {
            std::cout << "Email updated successfully for student ID " << student_id << ".\n";
        }

        //Catch and print the errors
    } catch (const pqxx::sql_error& e) {
        std::cerr << "SQL Error: " << e.what() << "\nQuery: " << e.query() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

}

void ManageStudentControl::deleteStudent() {
    //Take input from user
    int student_id;
    cout << "Enter student ID you want to delete: ";
    cin >> student_id;

    try {
        //Create a transaction
        pqxx::work tx(DB());  // Start transaction

        // Delete the student
        pqxx::result r = tx.exec_params(
            "DELETE FROM students WHERE student_id = $1 RETURNING student_id;",
            student_id
        );

        //Commit the transaction
        tx.commit();

        if (r.empty()) {
            std::cout << "No student found with ID " << student_id << ".\n";
        } else {
            std::cout << "Student ID " << student_id << " deleted successfully.\n";
        }

        //Catch and print errors
    } catch (const pqxx::sql_error& e) {
        std::cerr << "SQL Error: " << e.what() << "\nQuery: " << e.query() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}