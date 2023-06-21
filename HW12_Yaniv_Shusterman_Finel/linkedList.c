#include "linkedList.h"
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STR_LEN 1024


/*
this is a function to get a string from the user , it gets the size of the string and the char array
and gets the string and adds a null terminator at his end so he will be a string.
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
This function crates a frame node with the frame data: path, duration, name and adds it to the linked list.
input: heaed - pointer to the head of the list.
output: pointer to the head of the list.
*/
void addFrameNode(FrameNode** head)
{
	int nameValidOrNot = 0;
	int pathValidOrNot = 0;
	FILE* frameFile = NULL;
	FrameNode* newNode = (FrameNode*)malloc(sizeof(FrameNode));
	newNode->frame = (Frame*)malloc(sizeof(Frame));
	// mallocating memory for the name of the frame and it's path.
	newNode->frame->name = (char*)malloc(STR_LEN * sizeof(char));
	newNode->frame->path = (char*)malloc(STR_LEN * sizeof(char));
	if(newNode == NULL || newNode->frame == NULL ||newNode->frame->name == NULL || newNode->frame->path == NULL)
	{
		printf("malloc didn't worked! (createNode)");
	}
	else
	{
		printf("Please insert frame path:\n");
		myFgets(newNode->frame->path, STR_LEN);
		// chacking if the file exists.
		if(frameFile = fopen(newNode->frame->path, "rb"))
		{
			pathValidOrNot++;
			printf("vsddfbd");
		}

		//gettting the duration from the user.
		printf("Please insert frame duration(in milliseconds):\n");
		scanf("%u", &(newNode->frame->duration));
		getchar();

		printf("Please choose a name for that frame: \n");
		myFgets(newNode->frame->name, STR_LEN);
		nameValidOrNot = checkIfInList(newNode->frame->name, *head);
		// checking if name is already on the list, if yes it will ask the user to enter other name.
		while (nameValidOrNot != 0)
		{
			printf("The name is already taken, please enter another name\n");
			myFgets(newNode->frame->name, STR_LEN);
			nameValidOrNot = checkIfInList(newNode->frame->name, *head);
		}

		newNode->next = NULL;
	}

	if(pathValidOrNot == 0)
	{
		printf("Can't find file! Frame will not be added\n");
		free(newNode->frame->name);
		free(newNode->frame->path);
		free(newNode->frame);
		free(newNode);
	}
	else
	{
		if(*head == NULL)
		{
			*head = newNode;
		}
		else
		{
			FrameNode* lastNode = *head;
			while(lastNode->next != NULL)
			{
				lastNode = lastNode->next;
			}
			lastNode->next = newNode;
		}
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
	printf("Name     Duration     Path\n");
	while(curr)
	{
		printf("%s     ", curr->frame->name);
		printf("%u", curr->frame->duration);
		printf("     %s\n", curr->frame->path);
		curr = curr->next;
	}
}