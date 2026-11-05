# 📚 Digital Library System (C++)

A Command Line Interface (CLI) application built with C++ to manage a simple library system. This project was created to practice and demonstrate core programming concepts including **Structs, Vectors, Relational Data, and File I/O**.

## ✨ Key Features
- **Book CRUD**: Create, Read, Update, and Delete book records.
- **Borrowing System**: Users can borrow books (inventory automatically decreases).
- **Returning System**: Return books with validation to ensure the borrower's name and book title match the records.
- **Borrower History**: View a list of users who currently have books borrowed.
- **Permanent Storage (File I/O)**: All book and borrow records are automatically saved to `.txt` files, so data is not lost when the program is closed.
- **Input Validation**: Prevents empty inputs, invalid ISBN formats, and negative copy counts.

## 🛠️ How to Run the Program
1. Ensure you have a C++ compiler installed (e.g., `g++` or MinGW).
2. Clone this repository:
   ```bash
   git clone https://github.com/NHafidh/Library-Management-System.git
3. Navigate to the project directory and compile the C++ file:
   g++ LMS.cpp -o library
4. Run the program:
   ./library
