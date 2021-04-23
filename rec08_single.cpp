//
//  main.cpp
//  Rec 8
//



#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    // Course methods needed by Registrar
    Course(const string& courseName);
    const string& getName() const;
    bool addStudent(Student*);
    void removeStudentsFromCourse();

private:
    string name;
    vector<Student*> students;
};

class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const string& name);
    const string& getName() const;
    bool addCourse(Course*);

    // Student method needed by Course
    void removedFromCourse(Course*);

private:
    string name;
    vector<Course*> courses;
};

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar();
    bool addCourse(const string&);
    bool addStudent(const string&);
    bool enrollStudentInCourse(const string& studentName,
                               const string& courseName);
    bool cancelCourse(const string& courseName);
    void purge();

private:
    size_t findStudent(const string&) const;
    size_t findCourse(const string&) const;

    vector<Course*> courses;
    vector<Student*> students;
};





int main() {

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;
     
    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;
   
    /*
    // [OPTIONAL - do later if time]
    cout << "ChangeStudentName FritzTheCat MightyMouse\n";
    registrar.changeStudentName("FritzTheCat", "MightyMouse");
    cout << registrar << endl;

    cout << "DropStudentFromCourse MightyMouse CS101.001\n";
    registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
    cout << registrar << endl;

    cout << "RemoveStudent FritzTheCat\n";
    registrar.removeStudent("FritzTheCat");
    cout << registrar << endl;
    */

    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
}



//course
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



//student
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



//registrar
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
