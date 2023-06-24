#define _CRT_SECURE_NO_WARNINGS
#include "linkedList.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


/*
This function save a linked list of frames into a file in this format = path,duration,frame name.
input: head - pointer to pointer of the head of the linked list.
		path - the path of the file i will be saving to.
output: none.
*/
void saveGif(FrameNode** head, char* path)
{
	FILE* fileToSave = fopen(path, "w");
	FrameNode* curr = *head;
	// looping throughe the linked list nodes and adding them to the file one by one.
	while (curr)
	{
		fprintf(fileToSave, "%s,", curr->frame->path);
		fprintf(fileToSave, "%u,", curr->frame->duration);
		fprintf(fileToSave, "%s\n", curr->frame->name);
		curr = curr->next;
	}
	fclose(fileToSave);
}

/*
This function loads a file like csv and make its contect to a linked list of frames , each frame got: name , duration and path.
input: pathFile - path of a file im going to read from.
output: pointer to a linked list of frames.
*/
FrameNode* loadGif(char* pathFile)
{
	FILE* inputFile = fopen(pathFile, "r");
	int sizeFile = 0;
	FrameNode* head = NULL;
	char line[STR_LEN] = { 0 };
	if(inputFile == NULL)// cecking if there is a problem with the file.
	{
		printf("The file opening didn't worked!");
	}
	else
	{
		fseek(inputFile, 0, SEEK_END);
		sizeFile = ftell(inputFile);// cecking file length.
		// checking if the file is empty or not.
		if (sizeFile == 0)
		{
			printf("The file is empty :( starting new project!\n");
		}
		else// if yes we will load it.
		{
			fseek(inputFile, 0, SEEK_SET); // moving the arrow to the start of the file.
			while (fgets(line, sizeof(line), inputFile))// moving line by line on the file.
			{
				FrameNode* newNode = (FrameNode*)malloc(sizeof(FrameNode));
				newNode->frame = (Frame*)malloc(sizeof(Frame));
				// mallocating memory for the name of the frame and it's path.
				newNode->frame->name = (char*)malloc(STR_LEN * sizeof(char));
				newNode->frame->path = (char*)malloc(STR_LEN * sizeof(char));
				sscanf(line, "%[^,],%u,%[^\n]", newNode->frame->path, &(newNode->frame->duration), newNode->frame->name);
				newNode->next = NULL;
				// if the list is empty we will make the new frame the first in the list.
				if (head == NULL)
				{
					head = newNode;
				}
				//if the list isn't empty we will add the new frame node to the end of the list.
				else
				{
					FrameNode* lastNode = head;
					while (lastNode->next)
					{
						lastNode = lastNode->next;
					}
					lastNode->next = newNode;
				}
			}
			printf("Project loaded successfully\n");
		}
	}
	fclose(inputFile);
	return head;
}
