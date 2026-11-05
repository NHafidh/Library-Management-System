#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct Book {
    string title;
    string author;
    string isbn;
    int copies;
};

struct BorrowRecord{
    string borrowerName;
    string bookTitle;
};

vector<BorrowRecord> borrowRecords;
vector<Book> books; 
int BorrowedBook = 0;


void addBook() {
    Book newBook;
    bool isValidAdd = false;
    do {
        cout << "\nEnter book title: ";
        getline(cin, newBook.title);
            if (newBook.title.empty()) {
                cout << "Title cannot be empty. Book not added." << endl;
            } else {
            isValidAdd = true;
            }
} while (!isValidAdd);

    bool isValidAuthor = false;
    do{
        cout << "Enter book author: ";
        getline(cin, newBook.author);
            if (newBook.author.empty()) {
                cout << "Author cannot be empty. Book not added." << endl;
            } else {
                isValidAuthor = true;
            }
    } while (!isValidAuthor);

    string isbnInput;
    bool isValidISBN = false;
    do {
        cout << "Enter book ISBN: ";
        getline(cin, isbnInput);
            if (isbnInput.empty()) {
                cout << "ISBN cannot be empty. Book not added." << endl;
            }
            else if (isbnInput.length() != 13) {
                cout << "ISBN must be 13 characters long. Book not added." << endl;
            }
            else {
                try {
                    stoll(isbnInput); // Check if ISBN is numeric
                    isValidISBN = true;
                } catch (const invalid_argument&) {
                    cout << "ISBN must be numeric. Book not added." << endl;
                }
            }
    } while (!isValidISBN);
    newBook.isbn = isbnInput;
    

    string copiesInput;
    bool isValidCopies = false;
    do {
        cout << "Enter book number of copies: ";
        getline(cin, copiesInput);
            if (copiesInput.empty()) {
                cout << "Number of copies cannot be empty. Book not added." << endl;
            }
            else {
                try {
                        newBook.copies = stoi(copiesInput);
                        isValidCopies = true;
                        if (newBook.copies < 0) {
                            cout << "Number of copies cannot be negative. Book not added." << endl;
                        }
                    } catch (const invalid_argument&) {
                        cout << "Invalid input for number of copies. Book not added." << endl;
                    }
            }
    } while (!isValidCopies);
    books.push_back(newBook);
    cout << "Book added successfully!" << endl;
}

void searchBook() {
    string searchTitle;
    cout << "\nEnter the title of the book to search: ";
    getline(cin, searchTitle);

    bool found = false;
        for (const auto& book : books) {
            if (book.title == searchTitle) {
                cout << "Book found!" << endl;
                cout << "Title: " << book.title << " | Author: " << book.author
                    << " | ISBN: " << book.isbn << " | Copies: " << book.copies << endl;
                found = true;
                break;
            }
        }

    if (!found) {
        cout << "Book not found in the library." << endl;
    }
}

void displayBooks() {
    if (books.empty()) {
        cout << "No books available in the library." << endl;
        return;
    }

    cout << "\n=== List of Books ===" << endl;
    for (const auto& book : books) {
        cout << "Title: " << book.title << " | Author: " << book.author
             << " | ISBN: " << book.isbn << " | Copies: " << book.copies << endl;
    }
}

void borrowBook() {
    string borrowTitle;
    bool found = false;

    cout << "\nEnter the title of the book to borrow: ";
    getline(cin, borrowTitle);

    for (auto& book : books) {
        if (book.title == borrowTitle) {
            found = true;
            if (book.copies > 0) {
                book.copies--;
                string borrowerName;
                cout << "Enter your name: ";
                getline(cin, borrowerName);
                borrowRecords.push_back({borrowerName, book.title});
                cout << "You have successfully borrowed \"" << book.title << "\"." << endl;
                BorrowedBook++;
            } else {
                cout << "Sorry, \"" << book.title << "\" is currently unavailable." << endl;
            }
            return;
        }
    }

    if (!found) {
        cout << "Book not found in the library." << endl;
    }
}

void returnBook() {

      if (BorrowedBook == 0) {
            cout << "You have not borrowed any books to return." << endl;
            return;
        }
    string borrowerName;
    cout << "\nEnter your name: ";
    getline(cin, borrowerName);
    string returnTitle;
    cout << "\nEnter the title of the book to return: ";
    getline(cin, returnTitle);

    bool foundRecord = false;
    for (auto it = borrowRecords.begin(); it != borrowRecords.end(); ++it) {
        if (it->borrowerName == borrowerName && it->bookTitle == returnTitle) {
            foundRecord = true;
            borrowRecords.erase(it);
            break;
        }
    }
    if (!foundRecord) {
        cout << "No matching borrow record found." << endl;
        return;
    }
    for (auto& book : books) {
        if (book.title == returnTitle) {
            book.copies++;
            BorrowedBook--;
            cout << "You have successfully returned \"" << book.title << "\"." << endl;
            return;
        }
    }

    cout << "Book not found in the library." << endl;
}

void displayBorrowers() {
    if (borrowRecords.empty()) {
        cout << "No borrowers found." << endl;
        return;
    }

    cout << "\n=== List of Borrowers ===" << endl;
    for (const auto& record : borrowRecords) {
        cout << "Borrower Name: " << record.borrowerName << " | Book Title: " << record.bookTitle << endl;
    }
}

void saveData() {
    // Save books data to a file
    ofstream bookFile("books.txt");
    for (const auto& book : books) {
        bookFile << book.title << "|" << book.author << "|" << book.isbn << "|" << book.copies << endl;
    }
    bookFile.close();

    // Save borrow records data to a file
    ofstream borrowFile("borrow_records.txt");
    for (const auto& record : borrowRecords) {
        borrowFile << record.borrowerName << "|" << record.bookTitle << endl;
    }
    borrowFile.close();
}

void loadData() {
    // Load books data from a file
    ifstream bookFile("books.txt");
    string line;
    while (getline(bookFile, line)) {
        Book book;
        size_t pos = 0;
        string token;
        int fieldIndex = 0;

        while ((pos = line.find('|')) != string::npos) {
            token = line.substr(0, pos);
            switch (fieldIndex) {
                case 0: book.title = token; break;
                case 1: book.author = token; break;
                case 2: book.isbn = token; break;
                case 3: book.copies = stoi(token); break;
            }
            line.erase(0, pos + 1);
            fieldIndex++;
        }
        if(!line.empty() && fieldIndex == 3) {
            book.copies = stoi(line); // Last field (copies)
        }
        books.push_back(book);
    }
    bookFile.close();

    // Load borrow records data from a file
    ifstream borrowFile("borrow_records.txt");
    while (getline(borrowFile, line)) {
        BorrowRecord record;
        size_t pos = line.find('|');
        if (pos != string::npos) {
            record.borrowerName = line.substr(0, pos);
            record.bookTitle = line.substr(pos + 1);
            borrowRecords.push_back(record);
        }
    }
    borrowFile.close();
}

void changeBookInformation() {
    string searchTitle;
    cout << "\nEnter the title of the book to change information: ";
    getline(cin, searchTitle);

    for (auto& book : books) {
        if (book.title == searchTitle) {
            cout << "Book found! Enter new information" << endl;

            cout << "Enter new title (leave empty to keep current): ";
            string newTitle;
            getline(cin, newTitle);
            if (!newTitle.empty()) {
                book.title = newTitle;
            }

            cout << "Enter new author (leave empty to keep current): ";
            string newAuthor;
            getline(cin, newAuthor);
            if (!newAuthor.empty()) {
                book.author = newAuthor;
            }

            cout << "Enter new ISBN (leave empty to keep current): ";
            string newISBN;
            getline(cin, newISBN);
            if (!newISBN.empty()) {
                book.isbn = newISBN;
            }

            cout << "Enter new number of copies (leave empty to keep current): ";
            string copiesInput;
            getline(cin, copiesInput);
            if (!copiesInput.empty()) {
                try {
                    int newCopies = stoi(copiesInput);
                    if (newCopies >= 0) {
                        book.copies = newCopies;
                    } else {
                        cout << "Number of copies cannot be negative. Keeping current value." << endl;
                    }
                } catch (const invalid_argument&) {
                    cout << "Invalid input for number of copies. Keeping current value." << endl;
                }
            }

            cout << "Book information updated successfully!" << endl;
            return;
        }
    }

    cout << "Book not found in the library." << endl;
}

void deleteBook() {
    string deleteTitle;
    cout << "\nEnter the title of the book to delete: ";
    getline(cin, deleteTitle);

    for (auto it = books.begin(); it != books.end(); ++it) {
        if (it->title == deleteTitle) {
            books.erase(it);
            cout << "Book \"" << deleteTitle << "\" deleted successfully!" << endl;
            return;
        }
    }

    cout << "Book not found in the library." << endl;
}

int main() {
    loadData(); // Load existing data when the program starts

    while (true) {
        int choice;
        cout << "\n=== Welcome to Digital Library ===" << endl;
        cout << "1. Add new Book" << endl;
        cout << "2. Search for a Book" << endl;
        cout << "3. Display all Books" << endl;
        cout << "4. Borrow a Book" << endl;
        cout << "5. Return a Book" << endl;
        cout << "6. Borrowers List" << endl;
        cout << "7. Change Book Information" << endl;
        cout << "8. Delete Book" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore the newline character left in the input buffer

        if (choice == 1) {
        addBook();
        } else if (choice == 2) {
            searchBook();
        } else if (choice == 3) {
            displayBooks();
        } else if (choice == 4) {
            borrowBook();
        } else if (choice == 5) {
            returnBook();
        } else if (choice == 6) {
            displayBorrowers();
        } else if (choice == 7) {
            changeBookInformation();
        } else if (choice == 8) {
            deleteBook();
        } else if (choice == 9) {
            saveData(); // Save data before exiting
            cout << "Exiting the program. Goodbye!" << endl;
            exit(0);
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}
