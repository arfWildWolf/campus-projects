#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct words{
	int isWord;
	char meaning[200]="null";
	
	struct words* letter[26];
	
} *root;

struct words* createWord(char meaning[200]){
	struct words* newWord = (struct words*) malloc (sizeof(struct words));
    newWord->isWord=0;
    strcpy(newWord->meaning, meaning);
    
    for(int i=0; i<26; i++){
    	newWord->letter[i]=NULL; 
	}
	
	return newWord;
}

struct words* find(char word[100]){
	struct words* curr=root;
	
	
}

void insertWord(char word[100], char meaning[200]) {
    struct words* curr = root;
    int wordLen = strlen(word);

    for (int i = 0; i < wordLen; i++) {
        int index = tolower(word[i]) - 'a';

        if (curr->letter[index] == NULL) {
            curr->letter[index] = createWord("null");
        }

        curr = curr->letter[index];
    }

    if (curr->isWord == 1) {
        printf("Slang '%s' already exists. Updating meaning.\n", word);
    } else {
        printf("Inserted new slang '%s'.\n", word);
    }

    curr->isWord = 1;
    strcpy(curr->meaning, meaning);
}

void insertMenu() {
    char word[100], meaning[200];

    // Input slang word (no spaces, >1 char)
    while (1) {
        printf("Enter new slang word (no spaces, more than 1 character): ");
        scanf(" %[^\n]", word);  // leading space clears leftover newline

        // check for space and length
        if (strlen(word) > 1 && strchr(word, ' ') == NULL) {
            break;
        } else {
            printf("Invalid slang word. Try again.\n");
        }
    }

    // Input meaning (must contain space, so >1 word)
    while (1) {
        printf("Enter description (more than 1 word): ");
        scanf(" %[^\n]", meaning);  // read full line, spaces allowed

        if (strchr(meaning, ' ') != NULL) {
            break;
        } else {
            printf("Description must contain more than 1 word. Try again.\n");
        }
    }

    insertWord(word, meaning);
}




int hasNoChildren(struct words* node) {
    for (int i = 0; i < 26; i++) {
        if (node->letter[i] != NULL) return 0;
    }
    return 1;
}

int deleteHelper(struct words* curr, char word[100], int depth) {
    if (curr == NULL) return 0;

    if (word[depth] == '\0') {
        // End of word
        if (curr->isWord == 0) return 0; // Word not found
        curr->isWord = 0;

        // If no children, signal to delete this node
        return hasNoChildren(curr);
    }

    int index = tolower(word[depth]) - 'a';
    if (deleteHelper(curr->letter[index], word, depth + 1)) {
        // Child can be safely deleted
        free(curr->letter[index]);
        curr->letter[index] = NULL;

        // Check if current node should be deleted
        return !curr->isWord && hasNoChildren(curr);
    }

    return 0;
}

void deleteWord(char word[100]) {
    deleteHelper(root, word, 0);
}


void searchWord() {
    char word[100];

    // Input slang word with validation
    while (1) {
        printf("Input a slang word to be searched [Must be more than 1 characters and contains no space]: ");
        scanf(" %[^\n]", word); // Read full line, including leading space to clear buffer

        if (strlen(word) > 1 && strchr(word, ' ') == NULL) {
            break;
        } else {
            printf("Invalid input.\n");
        }
    }

    // Search logic in Trie
    struct words* curr = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = tolower(word[i]) - 'a';
        if (index < 0 || index > 25 || curr->letter[index] == NULL) {
            curr = NULL;
            break;
        }
        curr = curr->letter[index];
    }

    if (curr == NULL || curr->isWord == 0) {
        printf("\nThere is no word \"%s\" in the dictionary.\n", word);
    } else {
        printf("\nSlang word  : %s\n", word);
        printf("Description : %s\n", curr->meaning);
    }

    printf("Press enter to continue...");
    getchar(); // clear leftover newline
    getchar(); // wait for user to press enter
}

void collectWords(struct words* node, char* buffer, int depth, int* count) {
    if (node == NULL) return;

    if (node->isWord) {
        buffer[depth] = '\0';
        printf("%d. %s\n", ++(*count), buffer);
    }

    for (int i = 0; i < 26; i++) {
        if (node->letter[i]) {
            buffer[depth] = i + 'a';
            collectWords(node->letter[i], buffer, depth + 1, count);
        }
    }
}

void searchPrefix() {
    char prefix[100];
    printf("Input a prefix to be searched: ");
    scanf(" %[^\n]", prefix);

    struct words* curr = root;
    for (int i = 0; prefix[i] != '\0'; i++) {
        int index = tolower(prefix[i]) - 'a';
        if (index < 0 || index > 25 || curr->letter[index] == NULL) {
            curr = NULL;
            break;
        }
        curr = curr->letter[index];
    }

    if (curr == NULL) {
        printf("\nThere is no prefix \"%s\" in the dictionary.\n", prefix);
    } else {
        char buffer[100];
        strcpy(buffer, prefix);
        int count = 0;
        printf("\nWords starts with \"%s\":\n", prefix);
        collectWords(curr, buffer, strlen(prefix), &count);

        if (count == 0) {
            printf("No complete words start with this prefix.\n");
        }
    }

    printf("\nPress enter to continue...");
    getchar(); // flush newline
    getchar(); // wait for enter
}

void printAllHelper(struct words* curr, char* wordSoFar, int depth) {
    if (curr == NULL) return;

    if (curr->isWord == 1) {
        wordSoFar[depth] = '\0';  // terminate the string
        printf("%s: %s\n", wordSoFar, curr->meaning);
    }

    for (int i = 0; i < 26; i++) {
        if (curr->letter[i] != NULL) {
            wordSoFar[depth] = 'a' + i;
            printAllHelper(curr->letter[i], wordSoFar, depth + 1);
        }
    }
}

void printAll(){
	char buffer[100];  // to hold current word being built
	printAllHelper(root, buffer, 0);
}

void showMenu() {
    int choice;

    do {
        printf("\n=== Slang Dictionary Menu ===\n");
        printf("1. Release a new slang word\n");
        printf("2. Search a slang word\n");
        printf("3. View all slang words starting with a certain prefix word\n");
        printf("4. View all slang words\n");
        printf("5. Exit\n");
        printf("Choose [1-5]: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        switch (choice) {
            case 1:
                insertMenu();
                break;
            case 2:
                searchWord();
                break;
            case 3:
                searchPrefix();
                break;
            case 4:
                printAll();
                printf("\nPress enter to continue...");
                getchar();
                break;
            case 5:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    } while (choice != 5);
}


int main() {
    root = createWord("null");

	void showMenu();
    int choice;

    do {
        printf("\n=== Slang Dictionary Menu ===\n");
        printf("1. Release a new slang word\n");
        printf("2. Search a slang word\n");
        printf("3. View all slang words starting with a certain prefix word\n");
        printf("4. View all slang words\n");
        printf("5. Exit\n");
        printf("Choose [1-5]: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        switch (choice) {
            case 1:
                insertMenu();
                break;
            case 2:
                searchWord();
                break;
            case 3:
                searchPrefix();
                break;
            case 4:
                printAll();
                printf("\nPress enter to continue...");
                getchar();
                break;
            case 5:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    } while (choice != 5);
    
    puts("Thanks for using Boogle!");


	
//    insertWord("lol", "laugh out loud");
//    insertWord("hello", "a greeting");
//    insertWord("hi", "short hello");
//    
//    insertMenu();
//    
//    
//	printAll();
//	
//	deleteWord("lol");
//	
//	printAll();
//	
//	puts("");
//	
//	searchWord();
//	
//	searchPrefix();
	
	
    return 0;
}

