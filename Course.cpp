
#include "Course.h"
#include "Student.h"

using namespace std;

namespace BrooklynPoly {
    Course::Course(const string& courseName) : name(courseName) {}

    const string& Course::getName() const {
        return name;
    }

    ostream& operator<<(ostream& os, const Course& rhs) {
        os << rhs.name << ":";
        if (rhs.students.size() > 0) {
            for (const Student* studentp : rhs.students) {
                os << " " << studentp->getName();
            }
        }
        else {
            os << " No Students";
        }
        os << endl;
        return os;
    }



    bool Course::addStudent(Student* pointer) {
        for (size_t i = 0; i < students.size(); ++i) {
            if (students[i] == pointer) {
                return false;
            }
        }
        students.push_back(pointer);
        return true;
        
    }


    void Course::removeStudentsFromCourse() {
        for (size_t ind = 0; ind <students.size(); ++ind){
            students[ind]->removedFromCourse(this);
        }
        students.clear();
    }
}


