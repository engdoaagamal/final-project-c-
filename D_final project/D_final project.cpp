
#include <iostream>
#include <map>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;
class course {

    string course_code;
    string course_name;
    double grade;
    int course_hour;
  public :
      course() {
          course_code = "";
          course_name = "";
          grade = 0;
          course_hour = 0;
      }
      course(string code, string name, double g, int h) {
          course_code = code;
          course_name = name;
          course_hour = h;
          setgrad(g);
      }
    course(string code, double g, int h) {
        
        course_code = code;
        course_name = code;
        course_hour = h;
        setgrad(g);
    }
    void setname(string n) {
        this->course_name = n;
    }
    string getname()const {
      return  this->course_name;
    }
    void setcode(string code) {
        this->course_code = code;
    }
    string getcode()const {
        return  this->course_code;
    }
    void sethour(int  h) {
        if (h > 0&& h<=3)
            course_hour = h;
        else
            cout << "Invalid hours\n";
    }
    int gethour()const {
      return  this->course_hour;
    }
    bool setgrad(double d)
    {
        if (d >= 0 && d <= 100)
        {
           
           
                if (d >= 93) grade = 4.0;
                else if (d >= 90) grade =3.7;
                else if (d >= 87) grade =3.3;
                else if (d >= 83) grade =3.0;
                else if (d >= 80) grade =2.7;
                else if (d >= 77) grade =2.3;
                else if (d >= 73) grade =2.0;
                else if (d >= 70) grade =1.7;
                else if (d >= 67) grade =1.3;
                else if (d >= 65) grade =1.0;
                else grade =0.0;
           
            return true;
        }
        
            cout << "the grade must be between 0:100 \n";
            return false;
    }
    float getgrade()const {
        return  this->grade;
    }
    void print() {
        cout << "the course name : " << this->course_name << " code : " << course_code << " grad :" << this->grade <<" hour:"<<this->course_hour<< endl;
    }
    void show() {
        cout << " code : " << course_code << "  name : " << this->course_name << endl;
    }
};
class person {

    string name;
public:
    person(string n) {
        // cout << "welcome from person\n";
        name = n;
    }
    person() {
        cout << "welcome from person\n";
        name = "";
    }
};
class student :public  person {
public :
    int id;
    double Gpa = 0;
    map<string, course>courses;
    student(string n, int id) : person(n)
    {
        
        this->id = id;
    }
    void setcourse(string c_code,string n, double g,int h)
        {
        course c(c_code,n,g,h);
        courses[c_code] = c;
        }
    void setcoursebycode(string c_code, double g,int h)
    {
        course c(c_code,g,h);
        courses[c_code] = c;
    }
    void setcoursebyobj(course c)
    {
        
        courses[c.getcode()] = c;
    }
    double getGpa()
    {
        return Gpa;
    }
    void showcourses()
    {
        for (const auto& entry : courses) {
            cout << entry.first << "  " << entry.second.getname() << endl;
        }
    }
    void showcoursesdegree()
    {
        for (const auto& entry : courses) {
            cout << entry.first << "  " << entry.second.getname() << "  " << entry.second.getgrade() << endl;
        }
    }
    double calc_gpa()
    {
        double totalsum = 0;
        double totalhours = 0;

        for (const auto& entry : courses) {
            totalsum += entry.second.getgrade() * entry.second.gethour();
            totalhours += entry.second.gethour();
        }

        if (totalhours == 0) return 0;

        this->Gpa = totalsum / totalhours;
        return Gpa;
    }
};
int main()
{
    
    
        vector<student> students;
        int choice;

        do {
            cout << "\n===== MENU =====\n";
            cout << "1. Add Student\n";
            cout << "2. Remove Student\n";
            cout << "3. Search Student\n";
            cout << "4. Display All Students\n";
            cout << "5. Enroll Student in Course\n";
            cout << "6. Show Student Courses\n";
            cout << "7. Sort Students by GPA\n";
            cout << "8. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            if (choice == 1) {
                int id;
                string name;

                cout << "Enter ID: ";
                cin >> id;

                cout << "Enter Name: ";
                cin >> name;

                // check unique ID
                bool exists = false;
                for (auto& s : students) {
                    if (s.id == id) {
                        exists = true;
                        break;
                    }
                }

                if (exists) {
                    cout << "ID already exists!\n";
                }
                else {
                    student s(name, id);
                    students.push_back(s);
                    cout << "Student added successfully\n";
                }
            }

            else if (choice == 2) {
                int id;
                cout << "Enter ID to remove: ";
                cin >> id;

                bool found = false;

                for (int i = 0; i < students.size(); i++) {
                    if (students[i].id == id) {
                        students.erase(students.begin() + i);
                        cout << "Student removed\n";
                        found = true;
                        break; 
                    }
                }

                if (!found) {
                    cout << "Student not found\n";
                }
            }

            else if (choice == 3) {
                int id;
                cout << "Enter ID to search: ";
                cin >> id;

                bool found = false;
                for (auto& s : students) {
                    if (s.id == id) {
                        cout << "Found: " << s.name << " GPA: " << s.getGpa() << endl;
                        found = true;
                        break;
                    }
                }

                if (!found)
                    cout << "Student not found\n";
            }

            else if (choice == 4) {
                for (auto& s : students) {
                    cout << "ID: " << s.id
                        << " Name: " << s.name
                        << " GPA: " << s.calc_gpa() << endl;
                }
            }

            else if (choice == 5) {
                int id;
                cout << "Enter student ID: ";
                cin >> id;

                bool found = false;

                for (auto& s : students) {
                    if (s.id == id) {
                        string code, name;
                        double grade;
                        int hour;

                        cout << "Enter course code: ";
                        cin >> code;
                        cout << "Enter course name: ";
                        cin >> name;
                        cout << "Enter grade (0-100): ";
                        cin >> grade;
                        cout << "Enter hours:  ";
                        cin >> hour;

                        s.setcourse(code, name, grade, hour);
                        cout << "Course added\n";

                        found = true;
                        break;
                    }
                }

                if (!found)
                    cout << "Student not found\n";
            }

            else if (choice == 6) {
                int id;
                cout << "Enter student ID: ";
                cin >> id;

                bool found = false;

                for (auto& s : students) {
                    if (s.id == id) {
                        s.showcoursesdegree();
                        found = true;
                        break;
                    }
                }

                if (!found)
                    cout << "Student not found\n";
            }

            else if (choice == 7) {
                sort(students.begin(), students.end(),
                    [](student& a, student& b) {
                        return a.calc_gpa() > b.calc_gpa();
                    });

                cout << "Students sorted by GPA\n";
            }

        } while (choice != 8);

        return 0;
    }


