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
		curr = curr->next;
	}
	return 0;
}

/*
This function crates a frame node with the frame data: path, duration, name and adds it to the linked list.
input: heaed - pointer to the pointer of the head of the list.
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
	// checking if all mallocs worked.
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
			fclose(frameFile);
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
	// if the path isn't valid i won't add the frame.
	if(pathValidOrNot == 0)
	{
		printf("Can't find file! Frame will not be added\n");
		free(newNode->frame->name);
		free(newNode->frame->path);
		free(newNode->frame);
		free(newNode);
	}
	// if the path is valid we will ad the frame.
	else
	{
		// if the list is empty wr eill make the new frame the first in the list.
		if(*head == NULL)
		{
			*head = newNode;
		}
		//if the list isn't empty we will add the new frame node to the end of the list.
		else
		{
			FrameNode* lastNode = *head;
			while(lastNode->next)
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
		printf("%s        ", curr->frame->name);
		printf("%u ms", curr->frame->duration);
		printf("     %s\n", curr->frame->path);
		curr = curr->next;
	}
}

/*
This function free all the allocated memory and the linked list.
input: poniter to the pointer of the head of the function.
output: none.
*/
void freeList(FrameNode** head)
{
	FrameNode* curr = *head;
	FrameNode* temp = NULL;
	while (curr)
	{
		// freeing the name, path , the frame it self and them the node.
		temp = curr->next;
		free(curr->frame->name);
		free(curr->frame->path);
		free(curr->frame);
		free(curr);
		curr = temp;
	}
	*head = NULL;
}

/*
This function deletes a frame from the linked list of frames.
input: head - pointer to the pointer of the head of the list.
		nameOfFrame - the name of the frame i wan't to delete.
output: 1 if the frame exist in the linked list and 0 if not.
*/
int deleteFrame(FrameNode** head, char* nameOfFrame)
{
	FrameNode* p = *head;
	FrameNode* dNode = NULL;
	int exists = 0;
	// checking if the list is empty.
	if (*head)
	{
		// checking if frame i want to delete is in the first node of the linked list.
		if (0 == strcmp((*head)->frame->name, nameOfFrame))
		{
			*head = (*head)->next;
			// freeing all the node.
			free(p->frame->name);
			free(p->frame->path);
			free(p->frame);
			free(p);
			exists++;
		}
		else
		{
			// looping throush the list until i get to the name of the frame or the list ends.
			while (p->next && 0 != strcmp(p->next->frame->name, nameOfFrame))
			{
				p = p->next;

			}
			// if frame was found i will delete it.
			if (p->next)
			{
				dNode = p->next;
				p->next = dNode->next;
				// freeing all the node.
				free(dNode->frame->name);
				free(dNode->frame->path);
				free(dNode->frame);
				free(dNode);
				exists++;
			}
		}
	}
	return exists;
}

/*
This function changes the duration of a specific frame is he exists in the linked list.
input: head - pointer to the pointer to the linked list head.
		newDuration - the new duration of the frame.
		nameFrame - the name of the specific frame im looking for.
output: none.
*/
void changeDuration(FrameNode** head, unsigned int newDuration, char* nameFrame)
{
	FrameNode* curr = *head;
	while(curr)
	{
		// checking if the name equel to the name is need.
		if(strcmp(curr->frame->name, nameFrame) == 0)
		{
			// checnging the duration.
			curr->frame->duration = newDuration;
		}
		curr = curr->next;
	}
}

/*
This function chenges the duration of all of the frames in the list to the new duration.
input: head - pointer to the pointer of the first frame in the list.
		newDuration - the new duration of all of the frames.
output: none.
*/
void changeAllDuration(FrameNode** head, int newDuration)
{
	FrameNode* curr = *head;
	while(curr)
	{
		curr->frame->duration = newDuration;
		curr = curr->next;
	}
}

/*
This function checnges the entered frame position by an entered index.
example:
1->2->3->4 with index = 2 and the frame name is 1 will be:
2->1->3->4
input: head - pinter to the pointer to the head of the list.
		newLocation - the index the frame will move to.
		frameToMove - name of the frame you want to move.
output: none.
*/
void changeFramePosition(FrameNode** head, int newLocation, char* frameToMove)
{
	FrameNode* curr = *head;
	FrameNode* nodeToMove = NULL;
	FrameNode* prev = NULL;
	int index = 1;
	// looping throghe the linked list until i found the node im moving and the one before it.
	while(curr && strcmp(curr->frame->name, frameToMove) != 0)
	{
		prev = curr;
		curr = curr->next;
	}
	nodeToMove = curr;
	// if the node that i want to move is found and the one before it we will connect the on before it to the one that after the one i need to move.
	if(curr != NULL && prev != NULL)
	{
		prev->next = curr->next;
	}
	// if only the node i need was found and there is not a previous node, that means the node i need is the head and i remove the head.
	else if(curr != NULL)
	{
		*head = (*head)->next;
	}
	prev = NULL;
	curr = (*head);
	// if the node to move exists and the list isn't empty we will make the switch.
	if(nodeToMove != NULL && *head != NULL)
	{
		// finding the new previous node and current node in the place of the index that the user entered.
		while(curr && index != newLocation)
		{
			prev = curr;
			curr = curr->next;
			index++;
		}
		// if the prev exists we will concat the list we the node we want to move in his new place.
		if(prev != NULL)
		{
			prev->next = nodeToMove;
			nodeToMove->next = curr;
		}
		// of the prev doesn't exists that means the node we wont to move we go before the head.
		else if(*head)
		{
			nodeToMove->next = *head;
			*head = nodeToMove;
		}
	}
	// if the node to move exits but the list is empty we will make it the first one.
	else if(nodeToMove != NULL)
	{
		*head = nodeToMove;
	}

}

/*
this function returns the length of the list.
input: head - pinter to the pointer to the head of the list.
output: the length of the list.
*/
int findListLength(FrameNode** head)
{
	FrameNode* curr = *head;
	int length = 0;
	while(curr)
	{
		length++;
		curr = curr->next;
	}
	return length;
}

/*
This function reversing the linked list , the first one becomes the last and the last one becomes the first.
input: head - pointer to the first node in the list.
output: pointer to the reversed list.
*/
FrameNode* reverseTheList(FrameNode* head)
{
	FrameNode* before = NULL;
	FrameNode* tmp = head;
	FrameNode* next = NULL;

	while (tmp)
	{
		// switch the pointers.
		next = tmp->next;
		tmp->next = before;
		// move one position in the list.
		before = tmp;
		tmp = next;
	}
	//the last is the head.
	head = before;
	return head;

}