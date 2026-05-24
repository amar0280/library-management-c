# 📚 Library Management System in C

**Using Singly Linked List and Stack**

![Language](https://img.shields.io/badge/Language-C-blue)
![Platform](https://img.shields.io/badge/Platform-Console-lightgrey)
![Status](https://img.shields.io/badge/Status-Complete-brightgreen)

---

## 📌 Project Overview

A console-based Library Management System implemented in C that uses:
- **Singly Linked List** — to store and manage book records dynamically
- **Stack** — to track recently issued/returned books and support Undo functionality

---

## 🚀 Features

| Feature | Description |
|---|---|
| Add Book | Add a new book to the library |
| Display Books | View all books with status |
| Search Book | Find a book by its ID |
| Delete Book | Remove a book (only if not issued) |
| Issue Book | Mark a book as issued |
| Return Book | Mark a book as returned |
| Undo | Reverse the last issue or return action |
| History | View full action log via stack |

---

## 📁 Project Structure

```
library_management/
├── src/
│   └── library.c       ← Main source code
├── docs/
│   └── report.md       ← Project report
├── screenshots/        ← Output screenshots
└── README.md           ← This file
```

---

## 🛠️ How to Compile and Run

### On Linux / macOS:
```bash
gcc src/library.c -o library
./library
```

### On Windows (using GCC/MinGW):
```bash
gcc src\library.c -o library.exe
library.exe
```

---

## 📊 Data Structures Used

### Singly Linked List (for Books)
```
HEAD → [Book1] → [Book2] → [Book3] → NULL
```
Each node stores: ID, Title, Author, isIssued flag, next pointer.

### Stack (for Action History / Undo)
```
TOP → [RETURNED-101] → [ISSUED-102] → [ISSUED-101] → NULL
```
Each node stores: Book ID, Action ("ISSUED" / "RETURNED"), next pointer.

---

## 💡 Sample Output

```
========================================================
        LIBRARY MANAGEMENT SYSTEM
        Using Linked List + Stack in C
========================================================

-------------- MAIN MENU ---------------
 1. Add Book
 2. Display All Books
 3. Search Book by ID
 4. Delete Book
 5. Issue Book
 6. Return Book
 7. Undo Last Action
 8. View Action History (Stack)
 9. Exit
----------------------------------------
Enter your choice: 2

ID     Title                          Author                    Status
------------------------------------------------------------------------
101    The C Programming Language     Kernighan and Ritchie     Available
102    Data Structures in C           Tanenbaum                 Issued
```

---

## 👥 Team Members & Contributions

| Member | Role | Modules |
|---|---|---|
| Member 1 | Linked List Developer | addBook, deleteBook, displayBooks, searchBook |
| Member 2 | Stack Developer | push, pop, undoLastAction, displayHistory |
| Member 3 | UI & Testing | printMenu, printHeader, main(), test cases |
| Member 4 | Documentation & GitHub | README, report, repository management |

---

## 🔧 Concepts Used

- Dynamic Memory Allocation (`malloc`, `free`)
- Pointer manipulation
- Struct definitions
- String handling (`strcpy`, `strcmp`, `fgets`)
- Stack (LIFO) operations
- Linked list traversal and node manipulation

---

## 📝 License

This project is for educational purposes only.
