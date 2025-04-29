#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <regex>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

class Project_cpp {
public:
    static void menu() {
        cout << "\t\t*******************************************" << endl;
        cout << "\t\t\t  EMPLOYEE MANAGEMENT SYSTEM" << endl;
        cout << "\t\t*******************************************" << endl;
        cout << "\nPress 1 : To Add an Employee Details" << endl;
        cout << "Press 2 : To See an Employee Details" << endl;
        cout << "Press 3 : To Remove an Employee" << endl;
        cout << "Press 4 : To Update Employee Details" << endl;
        cout << "Press 5 : To Search for an Employee" << endl;
        cout << "Press 6 : To Display All Employees" << endl;
        cout << "Press 7 : To Exit the EMS Portal" << endl;
    }
};

class EmployDetail {
public:
    string name, father_name, email, position, employ_id, employ_salary, employ_contact;

    void getInfo() {
        cout << "Enter Employee's name --------: ";
        getline(cin, name);
        validateInput(name);

        cout << "Enter Employee's Father name -: ";
        getline(cin, father_name);
        validateInput(father_name);

        cout << "Enter Employee's ID ----------: ";
        getline(cin, employ_id);
        validateNumericInput(employ_id);

        cout << "Enter Employee's Email ID ----: ";
        getline(cin, email);
        validateInput(email);

        cout << "Enter Employee's Position ----: ";
        getline(cin, position);
        validateInput(position);

        cout << "Enter Employee contact Info --: ";
        getline(cin, employ_contact);
        validateInput(employ_contact);

        cout << "Enter Employee's Salary ------: ";
        getline(cin, employ_salary);
        validateNumericInput(employ_salary);
    }

private:
    void validateInput(string& input) {
        while (input.empty()) {
            cout << "Invalid input. Please enter a non-empty value: ";
            getline(cin, input);
        }
    }

    void validateNumericInput(string& input) {
        while (!regex_match(input, regex("\\d+"))) {
            cout << "Invalid input. Please enter a numeric value: ";
            getline(cin, input);
        }
    }
};

class Employee_Add {
public:
    void createFile() {
        EmployDetail emp;
        emp.getInfo();
        string filename = "file" + emp.employ_id + ".txt";

        ifstream infile(filename);
        if (infile.good()) {
            cout << "\nEmployee already exists :(" << endl;
        } else {
            ofstream outfile(filename);
            outfile << "Employee ID:" << emp.employ_id << "\n"
                    << "Employee Name     :" << emp.name << "\n"
                    << "Father's Name     :" << emp.father_name << "\n"
                    << "Employee Contact  :" << emp.employ_contact << "\n"
                    << "Email Information :" << emp.email << "\n"
                    << "Employee position :" << emp.position << "\n"
                    << "Employee Salary   :" << emp.employ_salary << "\n";
            cout << "\nEmployee has been Added :)" << endl;
            displayCurrentDateTime();
        }
        cout << "\nPress Enter to Continue...";
        cin.ignore();
    }

private:
    void displayCurrentDateTime() {
        time_t now = time(0);
        char* dt = ctime(&now);
        cout << "Employee added on: " << dt;
    }
};

class Employee_Show {
public:
    void viewFile(const string& id) {
        ifstream infile("file" + id + ".txt");
        if (!infile) {
            cout << "Employee does not exist :(" << endl;
            return;
        }
        string line;
        while (getline(infile, line)) {
            cout << line << endl;
        }
    }
};

class Employee_Remove {
public:
    void removeFile(const string& id) {
        string filename = "file" + id + ".txt";
        if (!fs::exists(filename)) {
            cout << "\nEmployee does not exist :(" << endl;
            return;
        }

        cout << "Are you sure you want to remove this employee? (Y/N): ";
        string confirm;
        getline(cin, confirm);

        if (confirm == "Y" || confirm == "y") {
            if (remove(filename.c_str()) == 0)
                cout << "Employee has been removed successfully." << endl;
            else
                cout << "Error removing employee :(" << endl;
        } else {
            cout << "Employee removal canceled." << endl;
        }
    }
};

class Employee_Update {
public:
    void updateFile(const string& id, const string& oldData, const string& newData) {
        string filename = "file" + id + ".txt";
        ifstream infile(filename);
        if (!infile) {
            cout << "Employee file not found." << endl;
            return;
        }

        stringstream buffer;
        buffer << infile.rdbuf();
        string content = buffer.str();

        size_t pos = content.find(oldData);
        if (pos != string::npos)
            content.replace(pos, oldData.length(), newData);

        ofstream outfile(filename);
        outfile << content;
        cout << "Employee details updated successfully." << endl;
        displayCurrentDateTime();
    }

private:
    void displayCurrentDateTime() {
        time_t now = time(0);
        char* dt = ctime(&now);
        cout << "Employee details updated on: " << dt;
    }
};

class Employee_Search {
public:
    void searchEmployee(const string& name) {
        bool found = false;
        for (const auto& entry : fs::directory_iterator(".")) {
            if (entry.is_regular_file() && entry.path().string().find("file") != string::npos) {
                ifstream file(entry.path());
                string line;
                while (getline(file, line)) {
                    if (line.find("Employee Name") != string::npos && line.find(name) != string::npos) {
                        cout << "\nEmployee found:\n" << line << endl;
                        found = true;
                        break;
                    }
                }
            }
        }
        if (!found) {
            cout << "\nEmployee not found :(" << endl;
        }
    }
};

class Employee_DisplayAll {
public:
    void displayAllEmployees() {
        for (const auto& entry : fs::directory_iterator(".")) {
            if (entry.path().string().find("file") != string::npos) {
                ifstream infile(entry.path());
                string line;
                while (getline(infile, line)) {
                    cout << line << endl;
                }
                cout << "\n------------------------\n";
            }
        }
    }
};

class CodeExit {
public:
    void out() {
        cout << "\n$ Thank You !! Please Visit Again :)\n" << endl;
        exit(0);
    }
};

int main() {
    Project_cpp::menu();
    Employee_Show epv;
    int choice;

    while (true) {
        cout << "\nPlease Enter choice : ";
        cin >> choice;
        cin.ignore(); // To consume newline after integer input

        switch (choice) {
            case 1: {
                Employee_Add ep;
                ep.createFile();
                Project_cpp::menu();
                break;
            }
            case 2: {
                cout << "\nPlease Enter Employee's ID : ";
                string id;
                getline(cin, id);
                epv.viewFile(id);
                cout << "\nPress Enter to Continue...";
                cin.ignore();
                Project_cpp::menu();
                break;
            }
            case 3: {
                cout << "\nEnter Employee ID to Remove: ";
                string id;
                getline(cin, id);
                Employee_Remove er;
                er.removeFile(id);
                cout << "\nPress Enter to Continue...";
                cin.ignore();
                Project_cpp::menu();
                break;
            }
            case 4: {
                cout << "\nEnter Employee ID to Update: ";
                string id, oldData, newData;
                getline(cin, id);
                cout << "Enter Old Data to Replace: ";
                getline(cin, oldData);
                cout << "Enter New Data: ";
                getline(cin, newData);
                Employee_Update eu;
                eu.updateFile(id, oldData, newData);
                cout << "\nPress Enter to Continue...";
                cin.ignore();
                Project_cpp::menu();
                break;
            }
            case 5: {
                cout << "\nEnter Employee Name to Search: ";
                string name;
                getline(cin, name);
                Employee_Search es;
                es.searchEmployee(name);
                cout << "\nPress Enter to Continue...";
                cin.ignore();
                Project_cpp::menu();
                break;
            }
            case 6: {
                Employee_DisplayAll eda;
                eda.displayAllEmployees();
                cout << "\nPress Enter to Continue...";
                cin.ignore();
                Project_cpp::menu();
                break;
            }
            case 7: {
                CodeExit ce;
                ce.out();
            }
            default:
                cout << "Invalid choice!" << endl;
        }
    }
    return 0;
}
