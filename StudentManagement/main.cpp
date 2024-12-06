#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

// Student structure
struct Student
{
    int student_id; // Unique identifier for the student
    char name[50];
    char class_name[20];
    int roll_number;
    int admission_year;
};

// Class for Student Management System
class StudentManagement
{
private:
    const char *file_name = "students.dat";

public:
    void add_student();
    void display_student(int student_id);
    void display_all_students();
    void delete_student(int student_id);
    void main_menu();
    bool read_from_file(int student_id, Student &student);
    void write_to_file(Student &student);
};

// Function to add a student
void StudentManagement::add_student()
{
    Student student;
    cout << "\nEnter student ID: ";
    cin >> student.student_id;

    cout << "Enter student name: ";
    cin.ignore();
    cin.getline(student.name, 50);

    cout << "Enter student class: ";
    cin.getline(student.class_name, 20);

    cout << "Enter student admission year: ";
    cin >> student.admission_year;

    cout << "Enter student roll number: ";
    cin >> student.roll_number;

    write_to_file(student);
    cout << "Student added successfully!\n";
}

// Function to write a student to file
void StudentManagement::write_to_file(Student &student)
{
    ofstream fout(file_name, ios::binary | ios::app);
    fout.write((char *)&student, sizeof(Student));
    fout.close();
}

// Function to display student details
void StudentManagement::display_student(int student_id)
{
    Student student;
    if (read_from_file(student_id, student))
    {
        cout << "\nStudent Details:\n";
        cout << "Student ID: " << student.student_id << endl;
        cout << "Name: " << student.name << endl;
        cout << "Class: " << student.class_name << endl;
        cout << "Admission Year: " << student.admission_year << endl;
        cout << "Roll Number: " << student.roll_number << endl;
    }
    else
    {
        cout << "Student not found!\n";
    }
}

// Function to read a student from file based on student ID
bool StudentManagement::read_from_file(int student_id, Student &student)
{
    ifstream fin(file_name, ios::binary);
    if (!fin)
        return false;

    while (fin.read((char *)&student, sizeof(Student)))
    {
        if (student.student_id == student_id)
        {
            fin.close();
            return true;
        }
    }

    fin.close();
    return false;
}

// Function to display all students
void StudentManagement::display_all_students()
{
    ifstream fin(file_name, ios::binary);
    Student student;

    cout << "\nAll Students Details:\n";
    while (fin.read((char *)&student, sizeof(Student)))
    {
        cout << "Student ID: " << student.student_id << ", ";
        cout << "Name: " << student.name << ", ";
        cout << "Class: " << student.class_name << ", ";
        cout << "Admission Year: " << student.admission_year << ", ";
        cout << "Roll Number: " << student.roll_number << endl;
    }

    fin.close();
}

// Function to delete a student
void StudentManagement::delete_student(int student_id)
{
    ifstream fin(file_name, ios::binary);
    ofstream fout("temp.dat", ios::binary); // Temporary file to store the data

    Student student;
    bool found = false;
    while (fin.read((char *)&student, sizeof(Student)))
    {
        if (student.student_id == student_id)
        {
            found = true;
        }
        else
        {
            fout.write((char *)&student, sizeof(Student));
        }
    }

    fin.close();
    fout.close();

    remove(file_name);             // Delete original file
    rename("temp.dat", file_name); // Rename temp file to original file name

    if (found)
    {
        cout << "Student deleted successfully!\n";
    }
    else
    {
        cout << "Student not found!\n";
    }
}

// Function to show the main menu
void StudentManagement::main_menu()
{
    int choice;
    do
    {
        cout << "\n********** STUDENT MANAGEMENT MENU **********\n";
        cout << "1. Add a Student\n";
        cout << "2. Display Student Details\n";
        cout << "3. Display All Students\n";
        cout << "4. Delete a Student\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            add_student();
            break;
        case 2:
            int student_id;
            cout << "Enter student ID to display: ";
            cin >> student_id;
            display_student(student_id);
            break;
        case 3:
            display_all_students();
            break;
        case 4:
            cout << "Enter student ID to delete: ";
            cin >> student_id;
            delete_student(student_id);
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
    StudentManagement sm;
    sm.main_menu();
    return 0;
}
