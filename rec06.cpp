//
//  main.cpp
//  Rec 6
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Section {
    friend ostream& operator<<(ostream& os, const Section& section) {
        os << "Section: " << section.section << ", Time Slot: " << section.time << ", Students: ";
             
        if (section.students.size()==0) {
            os << "None";
        }
        else {
            os << endl;
            for (StudentRecord* student : section.students) {
                os << *student;
            }
        }
        return os;
     }

private:
    
    class TimeSlot {
        friend ostream& operator<<(ostream& os, const TimeSlot& timeSlot) {
            os << "[Day: " << timeSlot.day << ", Start Time: ";
            
            if (timeSlot.hour > 12) {
                os << timeSlot.hour % 12 << "pm";
            }
            else {
                os << timeSlot.hour << "am";
            }
            os << "]";
            return os;
        }
        
        
    private:
        string day;
        int hour;
    
    public:
        TimeSlot (const string& day, const int hour)
           : day(day), hour(hour){}};


    class StudentRecord {
        friend ostream& operator<<(ostream& os, const StudentRecord& student) {
            os << "Name: " << student.name << ", Grades: ";
            for (int grade : student.grades) {
                os << grade << " ";
            }
            os << endl;
            return os;
        }
        
    private:
        string name;
        vector<int> grades;

    public:
        StudentRecord (const string& name): name(name), grades(14, -1){};

        const string& getName() const { return name; }

        void changeGrade(int newGrade, int week) {
            grades[week - 1] = newGrade;
        }
    };

     
    string section;
    TimeSlot time;
    vector<StudentRecord*> students;

public:
    Section (const string& code, const string& day, int hour): section(code), time(day, hour){};

    Section (const Section& rhs) : section(rhs.section), time(rhs.time) {
        for (StudentRecord* student : rhs.students) {
            StudentRecord* newStudent = new StudentRecord(*student);
            students.push_back(newStudent);
        }
    }

    ~Section() {
        cout << "Section " << section << " is being deleted\n";
        for (StudentRecord* student : students) {
            cout << "Deleting " << student->getName() << endl;
            delete student;
        }
        students.clear();
    }

    void addStudent (const string& newStudent) {
        students.push_back(new StudentRecord(newStudent));
    }

    void grading(const string& studentName, int newGrade, int week) {
        for (StudentRecord* student : students) {
            if (student->getName() == studentName) {
                student->changeGrade(newGrade, week);
            }
        }
    }
};







class LabWorker {
    friend ostream& operator<<(ostream& os, const LabWorker& professor) {
        if (!professor.section) {
           os << professor.name << " has no section" << endl;
        }
        else {
           os << professor.name << " has " << *professor.section;
        }
        return os;
    }

private:
    string name;
    Section* section;
    
public:
    LabWorker (const string& name): name(name), section(nullptr){};

    void addSection(Section& newSection) {
        section = &newSection;
    }

    void addGrade(const string& studentName, int grade, int week) {
        section->grading(studentName, grade, week);
    }
};



// Test code
void doNothing(Section sec) {
    cout << sec << endl;;
}

int main() {

    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe("Moe");
    cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection(secA2);
    cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection(secB3);
    cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);
    moe.addGrade("Paul", 19, 1);
    moe.addGrade("George", 16, 1);
    moe.addGrade("Ringo", 7, 1);
    cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);
    moe.addGrade("Paul", 20, 3);
    moe.addGrade("Ringo", 0, 3);
    moe.addGrade("George", 16, 3);
    cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
         << "then make sure the following call works properly, i.e. no memory leaks\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n";

} // main
