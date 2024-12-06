#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

// Book structure
struct Book
{
    int book_id;
    char title[100];
    char author[50];
    float price;
};

// Library Management Class
class LibraryManagement
{
private:
    const char file_name[20] = "library.dat";

public:
    void add_book();
    void display_book(int book_id);
    void display_all_books();
    void delete_book(int book_id);
    bool read_from_file(int book_id, Book &book);
    void write_to_file(Book &book);
    void main_menu();
};

// Add a new book
void LibraryManagement::add_book()
{
    Book book;
    cout << "\nEnter Book ID: ";
    cin >> book.book_id;

    cout << "Enter Title: ";
    cin.ignore();
    cin.getline(book.title, 100);

    cout << "Enter Author: ";
    cin.getline(book.author, 50);

    cout << "Enter Price: ";
    cin >> book.price;

    write_to_file(book);
    cout << "Book added successfully!\n";
}

// Write a book to the file
void LibraryManagement::write_to_file(Book &book)
{
    ofstream fout(file_name, ios::binary | ios::app);
    fout.write((char *)&book, sizeof(Book));
    fout.close();
}

// Display details of a single book
void LibraryManagement::display_book(int book_id)
{
    Book book;
    if (read_from_file(book_id, book))
    {
        cout << "\nBook Details:\n";
        cout << "Book ID: " << book.book_id << endl;
        cout << "Title: " << book.title << endl;
        cout << "Author: " << book.author << endl;
        cout << "Price: " << book.price << endl;
    }
    else
    {
        cout << "Book not found!\n";
    }
}

// Read a book from the file
bool LibraryManagement::read_from_file(int book_id, Book &book)
{
    ifstream fin(file_name, ios::binary);
    if (!fin)
        return false;

    while (fin.read((char *)&book, sizeof(Book)))
    {
        if (book.book_id == book_id)
        {
            fin.close();
            return true;
        }
    }

    fin.close();
    return false;
}

// Display all books
void LibraryManagement::display_all_books()
{
    ifstream fin(file_name, ios::binary);
    Book book;

    cout << "\nAll Books in the Library:\n";
    while (fin.read((char *)&book, sizeof(Book)))
    {
        cout << "Book ID: " << book.book_id << ", ";
        cout << "Title: " << book.title << ", ";
        cout << "Author: " << book.author << ", ";
        cout << "Price: " << book.price << ", ";
    }

    fin.close();
}

// Delete a book
void LibraryManagement::delete_book(int book_id)
{
    ifstream fin(file_name, ios::binary);
    ofstream fout("temp.dat", ios::binary);

    Book book;
    bool found = false;

    while (fin.read((char *)&book, sizeof(Book)))
    {
        if (book.book_id == book_id)
        {
            found = true;
        }
        else
        {
            fout.write((char *)&book, sizeof(Book));
        }
    }

    fin.close();
    fout.close();

    remove(file_name);
    rename("temp.dat", file_name);

    if (found)
    {
        cout << "Book deleted successfully!\n";
    }
    else
    {
        cout << "Book not found!\n";
    }
}

// Main menu
void LibraryManagement::main_menu()
{
    int choice;
    do
    {
        cout << "\n********** LIBRARY MANAGEMENT MENU **********\n";
        cout << "1. Add a Book\n";
        cout << "2. Display Book Details\n";
        cout << "3. Display All Books\n";
        cout << "4. Delete a Book\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            add_book();
            break;
        case 2:
        {
            int book_id;
            cout << "Enter Book ID: ";
            cin >> book_id;
            display_book(book_id);
            break;
        }
        case 3:
            display_all_books();
            break;
        case 4:
        {
            int book_id;
            cout << "Enter Book ID to delete: ";
            cin >> book_id;
            delete_book(book_id);
            break;
        }
        case 5:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);
}

// Main function
int main()
{
    LibraryManagement lm;
    lm.main_menu();
    return 0;
}
