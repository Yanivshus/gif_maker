/*********************************
* Class: MAGSHIMIM Final Project *
* Play function declaration          *
**********************************/

#ifndef VIEWH
#define VIEWH
#define CV_IGNORE_DEBUG_BUILD_GUARD

#include <opencv2/imgcodecs/imgcodecs_c.h>

#include <opencv2\core\core_c.h>
#include <opencv2\highgui\highgui_c.h>
#include "LinkedList.h"

void play(FrameNode* list);
void applyFilter(char* name, FrameNode** head);
void mouseCallback(int event, int x, int y, int flags, void* userdata);
#endif
