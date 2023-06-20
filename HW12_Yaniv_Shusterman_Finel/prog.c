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
	int choiceMenu = 1, loadOrSave = 0;
	FrameNode* head = NULL;
	printf("Welcome to Magshimim Movie Maker! what would you like to do?\n");
	
	do
	{
		printf(" [0] Create a new project\n [1] Load existing project\n");
		scanf("%d", &loadOrSave);
		if (loadOrSave > 1 || loadOrSave < 0)
		{
			printf("Invalid choice, try again:\n");
		}
	} 
	while (loadOrSave > 1 || loadOrSave < 0);

	do
	{
		printMenu();
		scanf("%d", &choiceMenu);
		switch (choiceMenu)
		{
			case 1:
				addFrameNode(&head);
				break;

			default:
				printf("You should type one of the options - 0-8!\n");
				break;
		}



	} while (choiceMenu != 0);

	return 0;
}

/*
This function print the menu of project.
*/
void printMenu()
{
	printf("What would you like to do?\n\n[0] Exit\n[1] Add new Frame\n[2] Remove a Frame\n[3] Change frame index\n[4] Change frame duration\n[5] Change duration of all frames\n[6] List frames\n[7] Play movie!\n[8] Save project\n");
}