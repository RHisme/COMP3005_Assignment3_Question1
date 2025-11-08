#ifndef UNTITLED_MANAGESTUDENTCONTROL_H
#define UNTITLED_MANAGESTUDENTCONTROL_H
#include <iostream>
#include "db.h"
#include <string>
#include <pqxx/pqxx>
using namespace std;


class ManageStudentControl {

    public:
        void getAllStudent() const;
        void addStudent(const string& first_name, const string& last_name, const string& email, const string& enrollment_date);
        void updateStudentEmail(int student_id, const string& new_email);
        void deleteStudent();


};

#endif //UNTITLED_MANAGESTUDENTCONTROL_H