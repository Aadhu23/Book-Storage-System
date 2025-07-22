#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct Book {
    string name;
    string author;
    string language;
    int rating;
    string category;
};

void addBook() {
    Book b;
    cout << "\nEnter Book Name: ";
    cin.ignore();
    getline(cin, b.name);

    cout << "Enter Author Name: ";
    getline(cin, b.author);

    cout << "Enter Language: ";
    getline(cin, b.language);

    cout << "Enter Ratings (1 to 5): ";
    cin >> b.rating;

    cout << "Enter Category (e.g. Fiction, Self-help): ";
    cin.ignore();
    getline(cin, b.category);

    ofstream outFile("books.csv", ios::app);
    if (outFile.is_open()) {
        outFile << b.name << "," << b.author << "," << b.language << "," << b.rating << "," << b.category << "\n";
        outFile.close();
        cout << "Book added successfully.\n";
    } else {
        cout << "Error opening books.csv\n";
    }
}

void viewBooks() {
    ifstream inFile("book.csv");
    string line;
    cout << "\n=== Book Reading Journal ===\n";
    if (inFile.is_open()) {
        getline(inFile, line);
        if (line.find("Book Name") == string::npos) {
            inFile.clear();
            inFile.seekg(0, ios::beg);
        }

        while (getline(inFile, line)) {
            stringstream ss(line);
            string name, author, language, rating, category;

            getline(ss, name, ',');
            getline(ss, author, ',');
            getline(ss, language, ',');
            getline(ss, rating, ',');
            getline(ss, category, ',');

            cout << "Book Name: " << name
                 << "\nAuthor   : " << author
                 << "\nLanguage : " << language
                 << "\nRatings  : " << rating
                 << "\nCategory : " << category
                 << "\n--------------------------\n";
        }
        inFile.close();
    } else {
        cout << "Error reading books.csv\n";
    }
}

int main() {
    int choice;
    do {
        cout << "\n***Book Journal Menu***\n";
        cout << "1. Add New Book\n";
        cout << "2. View All Books\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: cout << "Goodbye!\n"; break;
            default: cout << "Invalid option.\n";
        }
    } while (choice != 3);

    return 0;
}
