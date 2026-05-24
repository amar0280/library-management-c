# Project Report

## Library Management System Using Linked List and Stack in C

---

### 1. Introduction

A Library Management System is software that helps manage books in a library. It allows adding, removing, searching, issuing, and returning books. This project implements these operations using two core data structures — **Singly Linked List** and **Stack** — written in the C programming language.

Traditional arrays have fixed sizes. Linked lists solve this by using dynamic memory allocation, meaning the system can handle as many books as memory allows. The stack adds a unique feature: the ability to **undo** the last action.

---

### 2. Objective

- To implement a practical application using data structures learned in class
- To use **Singly Linked List** for dynamic book record storage
- To use **Stack** for tracking and reversing recent operations (Undo)
- To handle dynamic memory using `malloc` and `free`
- To build a user-friendly menu-driven console interface

---

### 3. Technologies Used

| Technology | Purpose |
|---|---|
| C Language | Core programming language |
| GCC Compiler | Compiling the source code |
| Singly Linked List | Storing book records |
| Stack (Linked List based) | Undo / Action History |
| `malloc()` / `free()` | Dynamic memory management |
| `stdio.h`, `stdlib.h`, `string.h` | Standard C libraries |

---

### 4. System Features

1. **Add Book** — Adds a new book at the end of the linked list. Duplicate IDs are rejected.
2. **Display Books** — Traverses the entire linked list and prints all book details.
3. **Search Book** — Searches by Book ID and displays details if found.
4. **Delete Book** — Removes a book node from the list. Issued books cannot be deleted.
5. **Issue Book** — Changes the book's status to "Issued" and pushes action to stack.
6. **Return Book** — Changes the book's status to "Available" and pushes action to stack.
7. **Undo** — Pops the last action from the stack and reverses it.
8. **View History** — Displays all actions in the stack from top to bottom.

---

### 5. Data Structure Design

#### 5.1 Book Node (Linked List)

```c
typedef struct Book {
    int id;
    char title[100];
    char author[100];
    int isIssued;
    struct Book *next;
} Book;
```

**Why Linked List?**
- Dynamic size — no fixed limit on number of books
- Easy insertion and deletion without shifting elements
- Efficient traversal for search and display

#### 5.2 Stack Node

```c
typedef struct StackNode {
    int bookId;
    char action[20];
    struct StackNode *next;
} StackNode;
```

**Why Stack?**
- LIFO (Last In, First Out) — perfect for "undo last action"
- Each issue/return is pushed; undo pops the top
- History can be displayed by traversing from top to bottom

---

### 6. Algorithm

#### Add Book:
```
1. Allocate memory for new Book node
2. Check for duplicate ID in list
3. If duplicate, free memory and return error
4. Else, traverse to end of list
5. Link new node at the end
6. Set isIssued = 0 (available)
```

#### Issue Book:
```
1. Search for book by ID in linked list
2. If not found, print error
3. If already issued, print error
4. Else, set isIssued = 1
5. Push (bookId, "ISSUED") onto stack
```

#### Undo:
```
1. Pop top node from stack
2. If stack is empty, print info and return
3. Search for the book by bookId
4. If last action was "ISSUED" → set isIssued = 0
5. If last action was "RETURNED" → set isIssued = 1
6. Free the popped node
```

---

### 7. Memory Management

All nodes use `malloc()` for allocation:
- `Book` nodes are allocated when adding books
- `StackNode` nodes are allocated on each issue/return
- `freeLinkedList()` and `freeStack()` are called on exit to prevent memory leaks

---

### 8. Advantages

- Dynamic memory — no size limit
- Undo feature makes it practical and user-friendly
- Clean separation of modules (list functions vs stack functions)
- Error handling for common cases (duplicate ID, issuing already issued books, etc.)
- Memory is properly freed on exit

---

### 9. Limitations

- Data is not saved to a file (data lost on exit)
- No sorting of book records
- No student/borrower information tracked

---

### 10. Future Scope

- Add file handling to save/load data permanently
- Add student records linked to issued books
- Implement due dates and fine calculation
- Add sorting (by ID, title, author)
- Build a GUI version using GTK or ncurses

---

### 11. Conclusion

This project demonstrates practical use of data structures in a real-world scenario. The Singly Linked List provides dynamic, flexible book storage, while the Stack provides undo functionality — showing how different data structures complement each other in a single application.

---

### 12. References

- "The C Programming Language" — Kernighan & Ritchie
- "Data Structures Using C" — Reema Thareja
- GCC Documentation: https://gcc.gnu.org
