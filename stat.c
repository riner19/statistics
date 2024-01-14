#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Word list representing list in code
typedef struct Words {
    char *word;
    int wordcounter;
    struct Words *next;
} Words;

// Prototypes of fucntions before main code to call them
Words *pushword(Words *head, const char *word);
void display(Words *head);
void stats(Words *head, int *wordSum, int *wordUnique);
void FileWriter(Words *head, FILE *outputFile);
void delList(Words *head);

int main() {
    Words *head = NULL;  // Head of the linked list
    int wordSum = 0;     // Total number of words in the database
    int wordUnique = 0;    // Number of unique words in the database

    int choice;
    char filename[100]; // variable for name of file
    char word[100]; // variable to store the word
    FILE *file; // file stream

    do {
        // // Displaying the menu
        printf("\nMenu:\n");
        printf("1. Read from file\n");
        printf("2. Enter text manually\n");
        printf("3. Display stats\n");
        printf("4. Display database\n");
        printf("5. Write to file\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        //scanf("%d", &choice);
        int result = scanf("%d", &choice);
        if (result != 1) { // checking the choice if its integer to avoid infinite loop
            // Invalid input, clear the input buffer
            while (getchar() != '\n');
            printf("Invalid input! Please enter a valid option.\n");
            continue;
        }
        switch (choice) {
            case 1:
                // Read the text from file
                printf("Enter the name of the file: ");
                scanf("%s", filename);
                file = fopen(filename, "r");
                if (file == NULL) {
                    printf("Error opening file!\n");
                } else {
                    char buffer[100];
                    while (fscanf(file, "%s", buffer) == 1) {
                        head = pushword(head, buffer);
                        wordSum++;
                    }
                    fclose(file);
                    printf("File read successfully!\n");
                }
                break;


            case 2:
                // Enter text manually
                printf("Enter text (type 'exit7' to stop):\n");
                while (1) {
                    scanf("%s", word);
                    if (strcmp(word, "exit7") == 0) {
                        break;
                    }
                    head = pushword(head, word);
                    wordSum++;
                }
                break;

            case 3:
                // Display statstistics
                stats(head, &wordSum, &wordUnique);
                printf("Total words: %d\n", wordSum);
                printf("Unique words: %d\n", wordUnique);
                break;

            case 4:
                // Display database
                display(head);
                break;

            case 5:
                // Write the results into a file
                printf("Enter output filename: ");
                scanf("%s", filename);
                file = fopen(filename, "w");
                if (file == NULL) {
                    printf("Error opening file for writing!\n");
                } else {
                    FileWriter(head, file);
                    fclose(file);
                    printf("Data written to file successfully!\n");
                }
                break;

            case 6:
                // Exit
                break;

            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 6);

    // Free the memory used by the linked list befor finishing
    delList(head);

    return 0;
}

// Function to pushword a word into the linked list
Words *pushword(Words *head, const char *word) {
    Words *newNode = (Words *)malloc(sizeof(Words));
    if (newNode == NULL) {
        // Memory allocation failed
        printf("Memory allocation failed for new node\n");
        free(newNode); // free the allocated memory 
        return NULL;
    }

    newNode->word = strdup(word);
    if (newNode->word == NULL) {
        // Memory allocation failed for the word
        printf("Memory allocation failed for word: %s\n", word);
        free(newNode); // free the allocated memory for word
        return NULL;
    }

    newNode->wordcounter = 1;
    newNode->next = NULL;

    // To check if the word already exists in the list
    Words *current = head;
    Words *prev = NULL;
    while (current != NULL) {
        if (strcasecmp(current->word, word) == 0) {
            // Word already exists in the linked list, so free the new node
            current->wordcounter++; // increment wordcounter
            free(newNode->word);
            free(newNode);
            return head;
        }
        prev = current;
        current = current->next;
    }

    // Insert the new node at the beginning of the list
    newNode->next = head;
    head = newNode;
    return head;
}

  


// Function to display the linked list
void display(Words *head) {
    Words *current = head;
    while (current != NULL) {
        printf("%s: %d\n", current->word, current->wordcounter);
        current = current->next;
    }
}

// Function to calculate statistics of the words in the linked list
void stats(Words *head, int *wordSum, int *wordUnique) {
    *wordSum = 0;
    *wordUnique = 0;

    Words *current = head;
    while (current != NULL) {
        (*wordUnique)++;
        *wordSum += current->wordcounter;
        current = current->next;
    }
}
// Function to write the linked list to a file
void FileWriter(Words *head, FILE *outputFile) {
    Words *current = head;
    while (current != NULL) {
        fprintf(outputFile, "%s: %d\n", current->word, current->wordcounter);
        current = current->next;
    }
}

// Function to free the memory used by the linked list to avoid memory leak
void delList(Words *head) {
    Words *current = head;
    while (current != NULL) {
        Words *tmp = current;
        current = current->next; // move to next node
        free(tmp->word); // free the node's data
        free(tmp);
    }
}

