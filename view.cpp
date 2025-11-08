#include "view.h"
#include "manageStudentControl.h"

void View::displayView() const {
    int choice = -1;

    while (choice != 0) {
        cout << R"(
    ==============================
     STUDENT MANAGEMENT MAIN MENU
    ==============================
    1. Display all current students
    2. Add a student to the database
    3. Update the email address for a student with the specified student_id.
    4. Delete a student
    0. Exit
    ==============================
    Choose an option: )";

        cin >> choice;

        //Create a control object
        ManageStudentControl studentManage;

        switch (choice) {
            case 1:
                cout << "Displaying all students...\n";
                studentManage.getAllStudent();
                break;

            case 2: {
                cout << "Adding a new student...\n";
                string first, last, student_email, date;

                // --- 1. Ask user input ---
                cout << "Enter first name: ";
                getline(std::cin >> std::ws, first);

                cout << "Enter last name: ";
                getline(cin >> ws, last);

                cout << "Enter email: ";
                getline(cin >> ws, student_email);

                cout << "Enter enrollment date (MM-DD-YYYY): ";
                getline(cin >> ws, date);

                studentManage.addStudent(first, last, student_email, date);
                break;
            }

            case 3: {
                cout << "Updating student email...\n";
                //Take input from user
                int student_id;
                cout << "Enter student ID you want to update: ";
                cin >> student_id;

                string new_email;
                cout << "Enter new email: ";
                getline(cin >> ws, new_email);

                studentManage.updateStudentEmail(student_id, new_email);
                break;
            }

            case 4:
                cout << "Deleting a student...\n";
                studentManage.deleteStudent();
                break;

            case 0:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid option. Please try again.\n";
                break;
        }
    }
}
