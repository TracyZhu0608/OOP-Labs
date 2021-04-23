//
//  Student.cpp
//  Rec 8 multiple
//


#include "Student.h"
#include "Course.h"

using namespace std;

namespace BrooklynPoly {
    Student::Student(const string& name) : name(name) {}

    const string& Student::getName() const {
        return name;
        }

    ostream& operator<<(ostream& os, const Student& rhs) {
        os << rhs.name << ":";
        if (rhs.courses.size() > 0) {
            for (const Course* coursep : rhs.courses) {
                os << " " << coursep->getName();
            }
        }
        
        else {
            os << " No Courses";
        }
        os << endl;
        return os;
        }

    bool Student::addCourse(Course* mypointer) {
        for (const Course* coursep : courses) {
            if (coursep == mypointer) {
                return false;
            }
        }
        courses.push_back(mypointer);
        return true;
    }

    void Student::removedFromCourse(Course* pointer) {

        bool shift_vector = false;
        for(size_t i = 0; i <courses.size(); ++i){
            if (courses[i] == pointer){
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
    //Loop through courses
    
    }

}
