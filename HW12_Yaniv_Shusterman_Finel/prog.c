/*********************************
* Class: MAGSHIMIM C2			 *
* openCV template      			 *
**********************************/
#define _CRT_SECURE_NO_DEPRECATE
#define CV_IGNORE_DEBUG_BUILD_GUARD
#include <opencv2/imgcodecs/imgcodecs_c.h>
#include <stdio.h>
#include <opencv2/core/core_c.h>
#include <opencv2/highgui/highgui_c.h>
#include "linkedList.h"
#include "view.h"
#include <string.h>
#include <stdlib.h>

void printMenu();

int main(void)
{
	int choiceMenu = 1, loadOrSave = 0, exists = 0;
	unsigned int newDuration = 0;
	char nameFrame[STR_LEN] = { 0 };
	FrameNode* head = NULL;
	printf("Welcome to Magshimim Movie Maker! what would you like to do?\n");
	printf(" [0] Create a new project\n [1] Load existing project\n");
	scanf("%d", &loadOrSave);
	getchar();
	do
	{
		switch (loadOrSave)
		{
		case 0:
			printf("\n");
			break;
		case 1:
			printf("\n");
			break;
		default:
			printf("Invalid choice, try again:\n");
			printf(" [0] Create a new project\n [1] Load existing project\n");
			scanf("%d", &loadOrSave);
			getchar();
			break;
		}
	} while (loadOrSave < 0 || loadOrSave > 1);

	do
	{
		printMenu();
		scanf("%d", &choiceMenu);
		getchar();
		switch (choiceMenu)
		{
			case 0:
				choiceMenu = 0;
				break;
			case 1:
				// creating a new node.
				printf("*** Creating new frame ***\n");
				addFrameNode(&head);
				break;
			case 2:
				// delteing a node.
				printf("Enter the name of the frame you wish to erase\n");
				myFgets(nameFrame, STR_LEN);
				exists = deleteFrame(&head, nameFrame);
				// checking if the node exists.
				if(exists == 0)
				{
					printf("The frame was not found\n");
				}
				else
				{
					printf("\n");
				}
				break;
			case 4:
				// changing the duration of a specific frame.
				printf("enter the name of the frame\n");
				myFgets(nameFrame, STR_LEN);
				exists = checkIfInList(nameFrame, head);
				//checking if the frame exists.
				if(exists == 0)
				{
					printf("The frame does not exist\n");
				}
				else
				{
					printf("Enter the new duration\n");
					scanf("%u", &newDuration);
					getchar();
					changeDuration(&head, newDuration, nameFrame);
				}
				break;
			case 5:
				//change the duration of all of the frames in the linked list.
				printf("Enter the duration for all frames:\n");
				scanf("%u", &newDuration);
				getchar();
				changeAllDuration(&head, newDuration);
				break;
			case 6:
				//printing the frames.
				printFrames(head);
				break;
			default:
				//didn't type the choice number right.
				printf("You should type one of the options - 0-8!\n");
				break;
		}
	} while (choiceMenu != 0);
	printf("\nBye!");
	// freeing all the linked list.
	freeList(&head);
	getchar();
	return 0;
}

/*
This function print the menu of project.
*/
void printMenu()
{
	printf("\nWhat would you like to do?\n[0] Exit\n[1] Add new Frame\n[2] Remove a Frame\n[3] Change frame index\n[4] Change frame duration\n[5] Change duration of all frames\n[6] List frames\n[7] Play movie!\n[8] Save project\n");
}