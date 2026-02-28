#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

struct Book {
    string name;
    string author;
    string language;
    float rating;
    string category;
};

struct Node {
    Book data;
    Node* next;
};

Node* head = NULL;

void insertBook(Book b) {
    Node* newNode = new Node;
    newNode->data = b;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        return;
    }

    Node* temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
}

void displayBooks() {
    if (head == NULL) {
        cout << "No books available.\n";
        return;
    }

    Node* temp = head;
    while (temp != NULL) {
        cout << "\nBook Name: " << temp->data.name
             << "\nAuthor   : " << temp->data.author
             << "\nLanguage : " << temp->data.language
             << "\nRating   : " << temp->data.rating
             << "\nCategory : " << temp->data.category
             << "\n---------------------------\n";
        temp = temp->next;
    }
}

void searchByName(string name) {
    Node* temp = head;
    bool found = false;

    while (temp != NULL) {
        if (temp->data.name == name) {
            cout << "Book Found!\n";
            cout << "Author: " << temp->data.author << endl;
            found = true;
        }
        temp = temp->next;
    }

    if (!found)
        cout << "Book not found.\n";
}
void searchByRating(float minRating) {
    Node* temp = head;
    bool found = false;

    while (temp != NULL) {
        if (temp->data.rating >= minRating) {
            cout << "\nBook Name: " << temp->data.name
                 << "\nAuthor   : " << temp->data.author
                 << "\nLanguage : " << temp->data.language
                 << "\nRating   : " << temp->data.rating
                 << "\nCategory : " << temp->data.category
                 << "\n---------------------------\n";
            found = true;
        }
        temp = temp->next;
    }

    if (!found)
        cout << "No books found with rating >= " << minRating << endl;
}

void deleteBook(string name) {
    if (head == NULL) {
        cout << "List is empty.\n";
        return;
    }

    if (head->data.name == name) {
        Node* temp = head;
        head = head->next;
        delete temp;
        cout << "Book deleted successfully.\n";
        return;
    }

    Node* temp = head;
    while (temp->next != NULL && temp->next->data.name != name)
        temp = temp->next;

    if (temp->next == NULL) {
        cout << "Book not found.\n";
        return;
    }

    Node* deleteNode = temp->next;
    temp->next = deleteNode->next;
    delete deleteNode;
    cout << "Book deleted successfully.\n";
}

void countBooks() {
    int count = 0;
    Node* temp = head;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    cout << "Total Books: " << count << endl;
}

void sortByRating() {
    if (head == NULL)
        return;

    bool swapped;
    Node* ptr1;
    Node* lptr = NULL;

    do {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->data.rating < ptr1->next->data.rating) {
                swap(ptr1->data, ptr1->next->data);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    cout << "Books sorted by rating (descending).\n";
}

void loadFromFile() {
    ifstream file("book.csv");
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;


        stringstream ss(line);
        Book b;
        string ratingStr;

        getline(ss, b.name, ',');
        getline(ss, b.author, ',');
        getline(ss, b.language, ',');
        getline(ss, ratingStr, ',');
        getline(ss, b.category);
        try {
            b.rating = ratingStr.empty() ? 0.0f : stof(ratingStr);
        } catch (...) {
            b.rating = 0.0f;
        }

        insertBook(b);
    }

    file.close();
}

void saveToFile() {
    ofstream file("book.csv");
    Node* temp = head;

    while (temp != NULL) {
        file << temp->data.name << ","
             << temp->data.author << ","
             << temp->data.language << ","
             << fixed << setprecision(1) << temp->data.rating << ","
             << temp->data.category << "\n";
        temp = temp->next;
    }

    file.close();
}

int main() {
    loadFromFile();

    int choice;
    do {
        cout << "\n===== BOOK JOURNAL (Linked List) =====\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Search Book\n";
        cout << "4. Delete Book\n";
        cout << "5. Count Books\n";
        cout << "6. Sort by Rating\n";
        cout << "7. Search by Rating\n";
        cout << "8. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            Book b;
            cout << "Enter Name: ";
            getline(cin, b.name);
            cout << "Enter Author: ";
            getline(cin, b.author);
            cout << "Enter Language: ";
            getline(cin, b.language);
            cout << "Enter Rating: ";
            cin >> b.rating;
            cin.ignore();
            cout << "Enter Category: ";
            getline(cin, b.category);

            insertBook(b);
            saveToFile();
            cout << "Added sucessfully";
        }
        else if (choice == 2)
            displayBooks();
        else if (choice == 3) {
            string name;
            cout << "Enter name to search: ";
            getline(cin, name);
            searchByName(name);
        }
        else if (choice == 4) {
            string name;
            cout << "Enter name to delete: ";
            getline(cin, name);
            deleteBook(name);
            saveToFile();
            cout << "Deleted Sucessfully";  
        }
        else if (choice == 5)
            countBooks();
        else if (choice == 6)
            sortByRating();
        else if (choice == 7) {
            float minRating;
            cout << "Enter minimum rating: ";
            cin >> minRating;
            cin.ignore();
            searchByRating(minRating);
        }
        else if (choice == 8)
            cout << "Goodbye!\n";
        else
            cout << "Invalid choice.\n";

    } while (choice != 8);

    return 0;
}