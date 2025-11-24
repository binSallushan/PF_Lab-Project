#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void EncryptionScreen();
void EncryptText(char *text);

void DecryptionScreen();
void DecryptText(char *text);

void HelpScreen();

void DisplayMenu();
void DisplayHelp();

int InputMenuChoice();
char *InputText();
int InputYesNo();
char *InputFileName();

// Main menu
int main()
{
    while (1)
    {
        DisplayMenu();
        int choice = InputMenuChoice();
        switch (choice)
        {
        case 1:
            EncryptionScreen();
            break;
        case 2:
            DecryptionScreen();
            break;
        case 3:
            HelpScreen();
            break;
        default:
            return 0;
        }
    }
}

// Display main menu
void DisplayMenu()
{
    system("cls"); // clear console
    printf("1. Encryption\n");
    printf("2. Decryption\n");
    printf("3. Help\n");
    printf("0. Exit\n\n");
}

int InputMenuChoice()
{
    int choice;
    do
    {
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n'); // flush invalid input
            choice = -1; // force loop
        }
    } while (choice < 0 || choice > 3);
    while (getchar() != '\n');
    return choice;
}

void EncryptionScreen()
{
    system("cls");

    printf("Enter text to encrypt: ");
    char *input = InputText();

    EncryptText(input);

    printf("\nEncrypted text: %s\n", input);

    // Ask to save to file
    printf("\nDo you want to save to a file? (1 = Yes, 0 = No): ");
    if (InputYesNo())
    {
        char *filename = InputFileName();
        FILE *f = fopen(filename, "w");
        if (f)
        {
            fprintf(f, "%s", input);
            fclose(f);
            printf("Saved to %s successfully.\n", filename);
        }
        else
        {
            printf("Failed to open file.\n");
        }
        free(filename);
    }

    free(input);
    printf("\nPress Enter to return to menu...");
    getchar();
}

// Decryption screen
void DecryptionScreen()
{
    system("cls");

    printf("Do you want to read from a file? (1 = Yes, 0 = No): ");
    if (InputYesNo())
    {
        char *filename = InputFileName();
        FILE *f = fopen(filename, "r");
        if (!f)
        {
            printf("Failed to open file %s\n", filename);
            free(filename);
            printf("\nPress Enter to return to menu...");
            getchar();
            return;
        }

        fseek(f, 0, SEEK_END);
        long length = ftell(f);
        fseek(f, 0, SEEK_SET);

        char *buffer = malloc(length + 1);
        if (!buffer)
        {
            fclose(f);
            free(filename);
            exit(1);
        }

        fread(buffer, 1, length, f);
        buffer[length] = '\0';
        fclose(f);
        free(filename);

        DecryptText(buffer);
        printf("\nDecrypted text: %s\n", buffer);
        free(buffer);
    }
    else
    {
        printf("Enter text to decrypt: ");
        char *input = InputText();
        DecryptText(input);
        printf("\nDecrypted text: %s\n", input);
        free(input);
    }

    printf("\nPress Enter to return to menu...");
    getchar();
}

// Encrypt text: shift letters 1 backward
void EncryptText(char *text)
{
    if (!text)
        return;

    for (int i = 0; text[i] != '\0'; i++)
    {
        char c = text[i];

        if (isupper(c))
            text[i] = ((c - 'A' - 1 + 26) % 26) + 'A';
        else if (islower(c))
            text[i] = ((c - 'a' - 1 + 26) % 26) + 'a';
    }
}

// Decrypt text: shift letters 1 forward
void DecryptText(char *text)
{
    if (!text)
        return;

    for (int i = 0; text[i] != '\0'; i++)
    {
        char c = text[i];

        if (isupper(c))
            text[i] = ((c - 'A' + 1) % 26) + 'A';
        else if (islower(c))
            text[i] = ((c - 'a' + 1) % 26) + 'a';
    }
}
