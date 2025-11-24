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
