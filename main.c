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
