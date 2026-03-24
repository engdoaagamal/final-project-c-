
#include <iostream>
#include <map>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>

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
private:
    string name;
public:
    person(string n) {
      //  cout << "welcome from person\n";
        name = n;
    }
    person() {
        cout << "welcome from person\n";
        name = "";
    }
    string getname()const {
        return name;
    }
};
class student :public  person {
private:
    int id;
    double Gpa = 0;
    map<string, course>courses;
public :
    student() { id = 0; Gpa = 0.0; }
    student(string n, int id) : person(n)
    {
        
        this->id = id;
    }
    int getId()const { return id; }
    //map<string, course>getcourses()const { return courses; }
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
        Gpa= calc_gpa();
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
    void printstd() {
        cout << "ID: " << this->id
            << " Name: " <<this->getname()
            << " GPA: " << this->calc_gpa() << endl;
    }
};
bool checkexiststd(int newid, const vector<student> & students) {
    bool exists = false;
    for (auto& s : students) {
        if (s.getId() == newid) {
            exists = true;
            break;
        }
    }
    return exists;
}
void inputstddetails(int &id,string &name) {
    cout << "Enter ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);
}
bool removestd(int stdid, vector<student>& students) {
    bool found = false;
    for (int i = 0; i < students.size(); i++) {
        if (students[i].getId() == stdid) {
            students.erase(students.begin() + i);
            cout << "Student removed\n";
            found = true;
            break;
        }
    }
    return found;
}

bool searchstd(int stdid, vector<student>& students) {
    bool found = false;
    for ( auto& s : students) {
        if (s.getId() == stdid) {
            cout << "Found: "<< endl;
            s.printstd();
            found = true;
            break;
        }
    }
    return found;
}
int findStudentIndex(int stdid,const  vector<student>& students) {
    for (int i = 0; i < students.size(); i++) {
        if (students[i].getId() == stdid) {
            return i;
        }
    }
    return -1;
}
void inputcourse(string &code, string &name,double &grade,int &hour) {
    cout << "Enter course code: ";
    cin >> code;
    cin.ignore();
    cout << "Enter course name: ";
    getline(cin, name);
    cout << "Enter grade (0-100): ";
    cin >> grade;
    cout << "Enter hours:  ";
    cin >> hour;
}

void printAll(vector<student>& students) {
    for (auto& s : students) {
        s.printstd();
    }
}


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
                inputstddetails(id,name);
               bool exists= checkexiststd(id,students);
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

                bool found= removestd(id, students);
                if (!found) {
                    cout << "Student not found\n";
                }
            }

            else if (choice == 3) {
                int id;
                cout << "Enter ID to search: ";
                cin >> id;

                bool found = searchstd( id, students);
                if (!found)
                    cout << "Student not found\n";
            }

            else if (choice == 4) {
                printAll(students);
            }

            else if (choice == 5) {
                int id;
                cout << "Enter student ID: ";
                cin >> id;

                int found = findStudentIndex(id,students);
                
                    if (found>=0) {
                        string code, name;
                        double grade;
                        int hour;
                        inputcourse(code, name, grade, hour);
                      students[found].setcourse(code, name, grade, hour);
                        cout << "Course added\n";
                    }
                    else 
                    {
                        cout << "Student not found\n";
                    }
            }

            else if (choice == 6) {
                int id;
                cout << "Enter student ID: ";
                cin >> id;

                int found = findStudentIndex(id, students);

                
                if (found>= 0) {
                    students[found].showcoursesdegree();
                        
                    }
                else
                {
                    cout << "Student not found\n";
                }
                    
            }

            else if (choice == 7) {
                sort(students.begin(), students.end(),
                    []( student& a,  student& b) {
                        return a.getGpa() > b.getGpa();
                    });

                cout << "Students sorted by GPA\n";
            }

        } while (choice != 8);

        return 0;
    }


