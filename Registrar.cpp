//
//  Registrar.cpp
//  Rec 8 multiple
//

#include "Course.h"
#include "Student.h"
#include "Registrar.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace BrooklynPoly{

    Registrar::Registrar() {}

    ostream& operator<<(ostream& os, const Registrar& rhs) {
        os << "Registrar's Report" << endl;
        os << "Courses:" << endl;
        
        for (const Course* coursep : rhs.courses) {
            os << *coursep;
        }
        os << "Students:" << endl;
        
        for (const Student* studentp : rhs.students) {
            os << *studentp;
        }
        return os;
    }


    bool Registrar::addCourse(const string& courseName) {
        if (findCourse(courseName) == courses.size()) {
            Course* new_course = new Course(courseName);
            courses.push_back(new_course);
            return true;
        }
        return false;
    }


    bool Registrar::addStudent(const string& studentName) {
        if (findStudent(studentName) == students.size()) {
            Student* new_stud = new Student(studentName);
            students.push_back(new_stud);
            return true;
        }
        return false;
    }


    bool Registrar::enrollStudentInCourse(const string& studentName,const string& courseName) {
        size_t courseindex = findCourse(courseName);
        size_t studentindex = findStudent(studentName);
        if (courseindex < courses.size() && studentindex < students.size()) {
            courses[courseindex]->addStudent(students[studentindex]);
            students[studentindex]->addCourse(courses[courseindex]);
            return true;
        }
        return false;
    }


    bool Registrar::cancelCourse(const string& courseName) {
        size_t courseindex = findCourse(courseName);
        if (courseindex != courses.size()) {
            courses[courseindex]->removeStudentsFromCourse();
            delete courses[courseindex];
            
            bool shift_vector = false;
            for(size_t i = 0; i <courses.size(); ++i){
                if (courses[i] == courses[courseindex]){
                    shift_vector = true;
                }
                
                if (i == courses.size()-1){
                    courses.pop_back();
                    break;
                }
                
                if (shift_vector == true){
                    courses[i] = courses[i+1];
                }
            }
            return true;
        }
        return false;
    }



    void Registrar::purge() {
        for (Course* course : courses) {
            delete(course);
        }
        courses.clear();
        for (Student* student : students) {
            delete(student);
        }
        students.clear();
    }


    size_t Registrar::findStudent(const string& studentName) const {
        for (size_t ind = 0; ind < students.size(); ++ind) {
            if (students[ind]->getName() == studentName) {
                return ind;
            }
        }
        return students.size();
        
    }

    size_t Registrar::findCourse(const string& courseName) const {
        for (size_t ind = 0; ind < courses.size(); ++ind) {
            if (courses[ind]->getName() == courseName) {
                return ind;
            }
        }
        return courses.size();
    }
}
