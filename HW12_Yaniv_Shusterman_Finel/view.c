/*********************************
* Class: MAGSHIMIM Final Project *
* Play function				 	 *
**********************************/

#include "view.h"
#include "linkedList.h"
#include <stdio.h>
#include <string.h>
int buttonPressed = 0;
CvRect buttonRect;
/**
play the movie!!
display the images each for the duration of the frame one by one and close the window
input: a linked list of frames to display
output: none
**/
void play(FrameNode* list)
{
	cvNamedWindow("Display window", CV_WINDOW_AUTOSIZE); //create a window
	FrameNode* head = list;
	int imgNum = 1, playCount = 0;
	IplImage* image;

	// Create a window
	cvNamedWindow("Stop button", CV_WINDOW_NORMAL);
	cvResizeWindow("Stop button", 35, 35);
	// Set the callback function for mouse events
	cvSetMouseCallback("Stop button", mouseCallback, NULL);
	// Initialize button properties
	buttonRect = cvRect(100, 100, 200, 100);
	// Create a black background image
	IplImage* imageButton = cvCreateImage(cvSize(275, 250), IPL_DEPTH_8U, 3);
	cvSet(imageButton, CV_RGB(0, 0, 0), NULL);

	// Draw the button shape
	cvRectangle(imageButton, cvPoint(buttonRect.x, buttonRect.y),
		cvPoint(buttonRect.x + buttonRect.width, buttonRect.y + buttonRect.height),
		CV_RGB(255, 0, 0), CV_FILLED, CV_AA, 0);

	// Draw button text
	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 1.5, 1.5, 0, 2, CV_AA);
	cvPutText(imageButton, "STOP!", cvPoint(buttonRect.x + 50, buttonRect.y + 60), &font, CV_RGB(0, 0, 0));
	// Display the image of button
	cvShowImage("Stop button", imageButton);

	while (buttonPressed == 0)
	{
		while (list != 0)
		{
			image = cvLoadImage(list->frame->path, 1);
			IplImage* pGrayImg = 0;
			pGrayImg = cvCreateImage(cvSize(image->width, image->height), image->depth, 1);
			if (!image) //The image is empty - shouldn't happen since we checked already.
			{
				printf("Could not open or find image number %d", imgNum);
			}
			else
			{
				cvShowImage("Display window", image); //display the image
				cvWaitKey(list->frame->duration); //wait
				list = list->next;
				cvReleaseImage(&image);
			}
			imgNum++;
		}
		list = head; // rewind
		playCount++;
	}
	buttonPressed = 0;
	cvReleaseImage(&imageButton);
	cvDestroyWindow("Display window");
	// Destroy the window
	cvDestroyWindow("Stop button");
	return;
}

/*
This function turn an image from the linked list to be black and white instead of colorful.
input: name - name of image to turn to black and white.
		head - pointer to the pointer that points to the head of the linked list.
output: none.
*/
void applyFilter(char* name, FrameNode** head)
{
	FrameNode* curr = *head;
	// finding the frame to turn gray.
	while(curr != NULL && strcmp(curr->frame->name, name) != 0)
	{
		curr = curr->next;
	}
	// chcking if frame was found.
	if(curr != NULL)
	{
		// loading it as gray.
		IplImage* image = cvLoadImage(curr->frame->path, CV_LOAD_IMAGE_GRAYSCALE);
		if (image == NULL) 
		{
			printf("Could not open or find the image!\n");
		}
		// saving it back to the same path it was but now as gray.
		cvSaveImage(curr->frame->path, image, 0);
		cvReleaseImage(&image);
	}
	else// if wasn't found.
	{
		printf("The frame does not exist\n");
	}

}

void mouseCallback(int event, int x, int y, int flags, void* userdata)
{
	// Check if left mouse button is pressed
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		// Check if the mouse click is within the button region
		if (x >= buttonRect.x && x <= buttonRect.x + buttonRect.width &&
			y >= buttonRect.y && y <= buttonRect.y + buttonRect.height)
		{
				// Set the button state to pressed
			buttonPressed = 1;
		}

	}
}
