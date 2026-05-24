/*
 * ============================================================
 *  Library Management System
 *  Using Singly Linked List + Stack in C
 * ============================================================
 *  Group Project — Console Based
 *  Language: C
 *  Data Structures: Singly Linked List, Stack
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ============================================================
   SECTION 1: STRUCTURE DEFINITIONS
   ============================================================ */

/* Book node for the Singly Linked List */
typedef struct Book {
    int id;                  /* Unique Book ID */
    char title[100];         /* Book Title */
    char author[100];        /* Author Name */
    int isIssued;            /* 0 = Available, 1 = Issued */
    struct Book *next;       /* Pointer to next book node */
} Book;

/* Stack node for tracking issue/return history (Undo support) */
typedef struct StackNode {
    int bookId;              /* ID of the book in this operation */
    char action[20];         /* "ISSUED" or "RETURNED" */
    struct StackNode *next;  /* Pointer to next stack node */
} StackNode;

/* ============================================================
   SECTION 2: GLOBAL VARIABLES
   ============================================================ */

Book *head = NULL;           /* Head of the linked list */
StackNode *stackTop = NULL;  /* Top of the stack */

/* ============================================================
   SECTION 3: STACK OPERATIONS
   ============================================================ */

/*
 * push() — Pushes a new action onto the stack
 * Called whenever a book is issued or returned
 */
void push(int bookId, char *action) {
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        printf("[ERROR] Memory allocation failed for stack.\n");
        return;
    }
    newNode->bookId = bookId;
    strcpy(newNode->action, action);
    newNode->next = stackTop;  /* New node points to old top */
    stackTop = newNode;        /* Update top to new node */
    printf("[STACK] Action recorded: Book ID %d -> %s\n", bookId, action);
}

/*
 * pop() — Pops the top action from the stack (for undo)
 * Returns the popped node (caller must free it)
 */
StackNode *pop() {
    if (stackTop == NULL) {
        printf("[INFO] No actions to undo. Stack is empty.\n");
        return NULL;
    }
    StackNode *temp = stackTop;
    stackTop = stackTop->next;  /* Move top down */
    return temp;
}

/*
 * peekStack() — Shows the top of the stack without removing it
 */
void peekStack() {
    if (stackTop == NULL) {
        printf("Stack is empty. No recent actions.\n");
    } else {
        printf("Last Action => Book ID: %d | Action: %s\n",
               stackTop->bookId, stackTop->action);
    }
}

/*
 * displayHistory() — Shows all actions in the stack (top to bottom)
 */
void displayHistory() {
    if (stackTop == NULL) {
        printf("No history available.\n");
        return;
    }
    StackNode *temp = stackTop;
    printf("\n%-15s %-15s\n", "Book ID", "Action");
    printf("------------------------------\n");
    while (temp != NULL) {
        printf("%-15d %-15s\n", temp->bookId, temp->action);
        temp = temp->next;
    }
}

/* ============================================================
   SECTION 4: LINKED LIST OPERATIONS
   ============================================================ */

/*
 * addBook() — Adds a new book at the END of the linked list
 */
void addBook() {
    Book *newBook = (Book *)malloc(sizeof(Book));
    if (newBook == NULL) {
        printf("[ERROR] Memory allocation failed.\n");
        return;
    }

    printf("\nEnter Book ID   : ");
    scanf("%d", &newBook->id);
    getchar(); /* Clear input buffer */

    /* Check for duplicate ID */
    Book *temp = head;
    while (temp != NULL) {
        if (temp->id == newBook->id) {
            printf("[ERROR] Book with ID %d already exists.\n", newBook->id);
            free(newBook);
            return;
        }
        temp = temp->next;
    }

    printf("Enter Book Title : ");
    fgets(newBook->title, 100, stdin);
    newBook->title[strcspn(newBook->title, "\n")] = '\0'; /* Remove newline */

    printf("Enter Author Name: ");
    fgets(newBook->author, 100, stdin);
    newBook->author[strcspn(newBook->author, "\n")] = '\0';

    newBook->isIssued = 0;   /* New book is available by default */
    newBook->next = NULL;

    /* If list is empty, new book becomes head */
    if (head == NULL) {
        head = newBook;
    } else {
        /* Traverse to end of list */
        Book *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newBook;
    }

    printf("[SUCCESS] Book '%s' added successfully!\n", newBook->title);
}

/*
 * displayBooks() — Displays all books in the linked list
 */
void displayBooks() {
    if (head == NULL) {
        printf("[INFO] No books in the library.\n");
        return;
    }

    Book *temp = head;
    printf("\n%-6s %-30s %-25s %-10s\n", "ID", "Title", "Author", "Status");
    printf("------------------------------------------------------------------------\n");

    while (temp != NULL) {
        printf("%-6d %-30s %-25s %-10s\n",
               temp->id,
               temp->title,
               temp->author,
               temp->isIssued ? "Issued" : "Available");
        temp = temp->next;
    }
}

/*
 * searchBook() — Searches for a book by ID
 * Returns pointer to the book, or NULL if not found
 */
Book *searchBook(int id) {
    Book *temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            return temp;  /* Found */
        }
        temp = temp->next;
    }
    return NULL;  /* Not found */
}

/*
 * searchAndDisplay() — Search book by ID and print its details
 */
void searchAndDisplay() {
    int id;
    printf("\nEnter Book ID to search: ");
    scanf("%d", &id);

    Book *found = searchBook(id);
    if (found == NULL) {
        printf("[ERROR] Book with ID %d not found.\n", id);
    } else {
        printf("\n--- Book Found ---\n");
        printf("ID     : %d\n", found->id);
        printf("Title  : %s\n", found->title);
        printf("Author : %s\n", found->author);
        printf("Status : %s\n", found->isIssued ? "Issued" : "Available");
    }
}

/*
 * deleteBook() — Deletes a book from the linked list by ID
 * Cannot delete a book that is currently issued
 */
void deleteBook() {
    int id;
    printf("\nEnter Book ID to delete: ");
    scanf("%d", &id);

    if (head == NULL) {
        printf("[INFO] Library is empty. Nothing to delete.\n");
        return;
    }

    Book *current = head;
    Book *prev = NULL;

    /* Traverse to find the book */
    while (current != NULL && current->id != id) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("[ERROR] Book with ID %d not found.\n", id);
        return;
    }

    if (current->isIssued == 1) {
        printf("[ERROR] Cannot delete. Book '%s' is currently issued.\n", current->title);
        return;
    }

    /* Unlink the node */
    if (prev == NULL) {
        head = current->next;   /* Deleting head node */
    } else {
        prev->next = current->next;  /* Bypass the node */
    }

    printf("[SUCCESS] Book '%s' deleted successfully.\n", current->title);
    free(current);  /* Free memory */
}

/*
 * issueBook() — Issues a book to a student
 * Pushes the action onto the stack
 */
void issueBook() {
    int id;
    printf("\nEnter Book ID to issue: ");
    scanf("%d", &id);

    Book *book = searchBook(id);
    if (book == NULL) {
        printf("[ERROR] Book with ID %d not found.\n", id);
        return;
    }

    if (book->isIssued == 1) {
        printf("[ERROR] Book '%s' is already issued.\n", book->title);
        return;
    }

    book->isIssued = 1;
    printf("[SUCCESS] Book '%s' issued successfully!\n", book->title);
    push(id, "ISSUED");  /* Record in stack */
}

/*
 * returnBook() — Returns a previously issued book
 * Pushes the action onto the stack
 */
void returnBook() {
    int id;
    printf("\nEnter Book ID to return: ");
    scanf("%d", &id);

    Book *book = searchBook(id);
    if (book == NULL) {
        printf("[ERROR] Book with ID %d not found.\n", id);
        return;
    }

    if (book->isIssued == 0) {
        printf("[ERROR] Book '%s' was not issued.\n", book->title);
        return;
    }

    book->isIssued = 0;
    printf("[SUCCESS] Book '%s' returned successfully!\n", book->title);
    push(id, "RETURNED");  /* Record in stack */
}

/*
 * undoLastAction() — Undoes the last issue or return using the stack
 */
void undoLastAction() {
    StackNode *last = pop();
    if (last == NULL) return;  /* Stack was empty */

    Book *book = searchBook(last->bookId);
    if (book == NULL) {
        printf("[ERROR] Book ID %d not found for undo.\n", last->bookId);
        free(last);
        return;
    }

    /* Reverse the last action */
    if (strcmp(last->action, "ISSUED") == 0) {
        book->isIssued = 0;
        printf("[UNDO] Reversed: Book '%s' is now Available again.\n", book->title);
    } else if (strcmp(last->action, "RETURNED") == 0) {
        book->isIssued = 1;
        printf("[UNDO] Reversed: Book '%s' is marked as Issued again.\n", book->title);
    }

    free(last);  /* Free the popped node */
}

/* ============================================================
   SECTION 5: HELPER / UTILITY FUNCTIONS
   ============================================================ */

/*
 * printHeader() — Prints a decorative console header
 */
void printHeader() {
    printf("\n");
    printf("========================================================\n");
    printf("        LIBRARY MANAGEMENT SYSTEM                      \n");
    printf("        Using Linked List + Stack in C                 \n");
    printf("========================================================\n");
}

/*
 * printMenu() — Displays the main menu
 */
void printMenu() {
    printf("\n-------------- MAIN MENU ---------------\n");
    printf(" 1. Add Book\n");
    printf(" 2. Display All Books\n");
    printf(" 3. Search Book by ID\n");
    printf(" 4. Delete Book\n");
    printf(" 5. Issue Book\n");
    printf(" 6. Return Book\n");
    printf(" 7. Undo Last Action\n");
    printf(" 8. View Action History (Stack)\n");
    printf(" 9. Exit\n");
    printf("----------------------------------------\n");
    printf("Enter your choice: ");
}

/*
 * freeLinkedList() — Frees all nodes in the linked list before exit
 */
void freeLinkedList() {
    Book *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

/*
 * freeStack() — Frees all nodes in the stack before exit
 */
void freeStack() {
    StackNode *temp;
    while (stackTop != NULL) {
        temp = stackTop;
        stackTop = stackTop->next;
        free(temp);
    }
}

/* ============================================================
   SECTION 6: MAIN FUNCTION
   ============================================================ */

int main() {
    int choice;

    printHeader();

    while (1) {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                searchAndDisplay();
                break;
            case 4:
                deleteBook();
                break;
            case 5:
                issueBook();
                break;
            case 6:
                returnBook();
                break;
            case 7:
                undoLastAction();
                break;
            case 8:
                printf("\n--- Action History (Stack Top to Bottom) ---\n");
                displayHistory();
                break;
            case 9:
                printf("\nFreeing memory and exiting...\n");
                freeLinkedList();
                freeStack();
                printf("Thank you! Goodbye.\n");
                return 0;
            default:
                printf("[ERROR] Invalid choice. Enter 1-9.\n");
        }
    }

    return 0;
}
