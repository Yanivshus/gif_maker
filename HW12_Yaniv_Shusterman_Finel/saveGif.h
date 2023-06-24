#ifndef SAVEGIFH
#define SAVEGIFH
#include "linkedList.h"

void saveGif(FrameNode** head, char* path);
FrameNode* loadGif(char* pathFile);
void myFgetsFile(char str[], int n, FILE* inputFile);

#endif