#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

// Employee structure
struct Employee
{
    int employee_id;
    char name[50];
    char department[30];
    char position[30];
    double salary;
};

// Class for Employee Management System
class EmployeeManagement
{
private:
    const char file_name[14] = "employees.dat";

public:
    void add_employee();
    void display_employee(int employee_id);
    void display_all_employees();
    void delete_employee(int employee_id);
    void main_menu();
    bool read_from_file(int employee_id, Employee &employee);
    void write_to_file(Employee &employee);
};

// Function to add an employee
void EmployeeManagement::add_employee()
{
    Employee employee;
    cout << "\nEnter employee ID: ";
    cin >> employee.employee_id;
    cin.ignore();

    cout << "Enter employee name: ";
    cin.getline(employee.name, 50);

    cout << "Enter department: ";
    cin.getline(employee.department, 30);

    cout << "Enter position: ";
    cin.getline(employee.position, 30);

    cout << "Enter salary: ";
    cin >> employee.salary;

    write_to_file(employee);
    cout << "Employee added successfully!\n";
}

// Function to write an employee to file
void EmployeeManagement::write_to_file(Employee &employee)
{
    ofstream fout(file_name, ios::binary | ios::app);
    fout.write((char *)&employee, sizeof(Employee));
    fout.close();
}

// Function to display employee details
void EmployeeManagement::display_employee(int employee_id)
{
    Employee employee;
    if (read_from_file(employee_id, employee))
    {
        cout << "\nEmployee Details:\n";
        cout << "ID: " << employee.employee_id << endl;
        cout << "Name: " << employee.name << endl;
        cout << "Department: " << employee.department << endl;
        cout << "Position: " << employee.position << endl;
        cout << "Salary: " << employee.salary << endl;
    }
    else
    {
        cout << "Employee not found!\n";
    }
}

// Function to read an employee from file based on employee ID
bool EmployeeManagement::read_from_file(int employee_id, Employee &employee)
{
    ifstream fin(file_name, ios::binary);
    if (!fin)
        return false;

    while (fin.read((char *)&employee, sizeof(Employee)))
    {
        if (employee.employee_id == employee_id)
        {
            fin.close();
            return true;
        }
    }

    fin.close();
    return false;
}

// Function to display all employees
void EmployeeManagement::display_all_employees()
{
    ifstream fin(file_name, ios::binary);
    Employee employee;

    cout << "\nAll Employee Details:\n";
    while (fin.read((char *)&employee, sizeof(Employee)))
    {
        cout << "ID: " << employee.employee_id << ", ";
        cout << "Name: " << employee.name << ", ";
        cout << "Department: " << employee.department << ", ";
        cout << "Position: " << employee.position << ", ";
        cout << "Salary: " << employee.salary << endl;
    }

    fin.close();
}

// Function to delete an employee
void EmployeeManagement::delete_employee(int employee_id)
{
    ifstream fin(file_name, ios::binary);
    ofstream fout("temp.dat", ios::binary);

    Employee employee;
    bool found = false;

    while (fin.read((char *)&employee, sizeof(Employee)))
    {
        if (employee.employee_id == employee_id)
        {
            found = true;
        }
        else
        {
            fout.write((char *)&employee, sizeof(Employee));
        }
    }

    fin.close();
    fout.close();

    remove(file_name);
    rename("temp.dat", file_name);

    if (found)
    {
        cout << "Employee deleted successfully!\n";
    }
    else
    {
        cout << "Employee not found!\n";
    }
}

// Function to show the main menu
void EmployeeManagement::main_menu()
{
    int choice;
    do
    {
        cout << "\n********** EMPLOYEE MANAGEMENT MENU **********\n";
        cout << "1. Add an Employee\n";
        cout << "2. Display Employee Details\n";
        cout << "3. Display All Employees\n";
        cout << "4. Delete an Employee\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            add_employee();
            break;
        case 2:
            int employee_id;
            cout << "Enter employee ID to display: ";
            cin >> employee_id;
            display_employee(employee_id);
            break;
        case 3:
            display_all_employees();
            break;
        case 4:
            cout << "Enter employee ID to delete: ";
            cin >> employee_id;
            delete_employee(employee_id);
            break;
        case 5:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);
}

int main()
{
    EmployeeManagement em;
    em.main_menu();
    return 0;
}

