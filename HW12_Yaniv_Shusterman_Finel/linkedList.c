#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STR_LEN 1024

/*
this is a function to get a string from the user , it gets the size of the string and the char array
and gets the string and adds a null terminator at his and so he will be a string.
*/
void myFgets(char str[], int n)
{
	fgets(str, n, stdin);
	str[strcspn(str, "\n")] = 0;
}

/*
This function checks if a name of a frame already exsits in the linked list
input: name - name to check if in list.
		head - pointer to the head of the linked list.
output: 1 if in list 0 if not.
*/
int checkIfInList(char* name, FrameNode* head)
{
	FrameNode* curr = head;
	while(curr)
	{
		if(strcmp(curr->frame->name, name) == 0)
		{
			return 1;
		}
	}
	return 0;
}
/*
This function crates a frame node with the frame data: path, duration, name.
input: none.
output: pointer to the frame struct.
*/
FrameNode* addFrameNode(FrameNode* head)
{
	int nameValidOrNot = 1;
	int pathValidOrNot = 1;
	char pathToCheck[STR_LEN] = { 0 };
	char nameToCheck[STR_LEN] = { 0 };
	FrameNode* newNode = (FrameNode*)malloc(sizeof(FrameNode));
	newNode->frame->name = (char*)malloc(STR_LEN);
	newNode->frame->path = (char*)malloc(STR_LEN);
	if(newNode || newNode->frame->name || newNode->frame->path)
	{
		printf("malloc didn't worked! (createNode)");
	}
	else
	{
		printf("Please insert frame path:\n");
		myFgets(newNode->frame->path, STR_LEN);
		printf("Please insert frame duration<in milliseconds>:\n");
		scanf("%d", newNode->frame->duration);
		getchar();
		printf("Please choose a name for that frame: \n");
		myFgets(nameToCheck, STR_LEN);
		nameValidOrNot = checkIfInList(nameToCheck, head);
		while(nameValidOrNot == 1)
		{
			printf("The name is already taken, please enter another name\n");
			myFgets(nameToCheck, STR_LEN);
			nameValidOrNot = checkIfInList(nameToCheck, head);
		}
		strncpy(newNode->frame->name, nameToCheck, STR_LEN);

	}
}

/*
This function prints the data inside the frames of the linked list.
input: head of the list.
output: none.
*/
void printFrames(FrameNode* head)
{
	FrameNode* curr = head;
	printf("Name     Duration     Path");
	while(curr)
	{
		printf("%s     ", curr->frame->name);
		printf("%d", curr->frame->duration);
		printf("     %s", curr->frame->path);
		curr = curr->next;
	}
}