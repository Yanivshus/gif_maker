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
#include <stdlib.h>
#include "saveGif.h"

void printMenu();

int main(void)
{
	int choiceMenu = 1, exists = 0, index = 0, listLength = 0, loadOrNew = 0;
	unsigned int newDuration = 0;
	char nameFrame[STR_LEN] = { 0 };
	char pathString[STR_LEN] = { 0 };
	FrameNode* head = NULL;
	FILE* loadTry = NULL;
	printf("Welcome to Magshimim Movie Maker! what would you like to do?\n");
	printf(" [0] Create a new project\n [1] Load existing project\n");
	// checking if the user want to load the project or create a new one.
	do
	{
		scanf("%d", &loadOrNew);
		getchar();
		switch (loadOrNew)
		{
		case 0:
			// if the user entered 0 that means that he want to create new project.
			printf("Working on a new project.\n");
			break;
		case 1:
			printf("Enter the path of the project (including project name):\n");
			myFgets(pathString, STR_LEN);
			loadTry = fopen(pathString, "r");
			// checking if the file exits.
			if(loadTry == NULL)
			{
				printf("Error!- cant open file, creating a new project\n");
				head = NULL;
			}
			else// if exists then we will load it.
			{
				fclose(loadTry);
				head = loadGif(pathString);
			}
			break;
		default:
			// if the user entered the invalid unput it will ask him again 1 or 0.
			printf("Invalid choice, try again:\n");
			printf(" [0] Create a new project\n [1] Load existing project\n");
			break;
		}
	} while (loadOrNew < 0 || loadOrNew > 1);
	// the actual menu loop.
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
			case 3:
				printf("Enter the name of the frame\n");
				myFgets(nameFrame, STR_LEN);
				exists = checkIfInList(nameFrame, head);
				// if the name exits in the list we will continue.
				if (exists == 1)
				{
					listLength = findListLength(&head);
					printf("Enter the new index in the movie you wish to place the frame\n");
					// checking if the index in the list is valid and under the length of the list.
					do
					{
						scanf("%d", &index);
						getchar();
						// printing error massages.
						if (index > listLength || index < 0)
						{
							printf("The movie contains only %d frames!\n", listLength);
							printf("Enter the new index in the movie you wish to place the frame\n");
						}
						// looping until the valid value will be entered.
					} while (index > listLength || index < 0);
					changeFramePosition(&head, index, nameFrame);
				}
				// if the name doesn't exists we will print the right massage to the user.
				else
				{
					printf("this frame does not exist\n");
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
			case 7:
				// playing the video.
				play(head);
				break;
			case 8:
				printf("Where to save the project? enter a full path and file name\n");
				myFgets(pathString, STR_LEN);
				saveGif(&head, pathString);
				break;
			case 9:
				head = reverseTheList(head);
				play(head);
				head = reverseTheList(head);
			case 10:
				// changing the duration of a specific frame.
				printf("enter the name of the frame\n");
				myFgets(nameFrame, STR_LEN);
				exists = checkIfInList(nameFrame, head);
				if(exists == 1)
				{
					turnToBlackWhite(nameFrame, &head);
					printf("Filter applied!\n");
				}
				else
				{
					printf("The frame does not exist\n");
				}
					
				break;
			default:
				//didn't type the choice number right.
				printf("You should type one of the options - 0-9!\n");
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
	printf("\nWhat would you like to do?\n[0] Exit\n[1] Add new Frame\n[2] Remove a Frame\n[3] Change frame index\n[4] Change frame duration\n[5] Change duration of all frames\n[6] List frames\n[7] Play movie!\n[8] Save project\n[9] Play gif from end to start\n[10] Make a frame gray\n");
}