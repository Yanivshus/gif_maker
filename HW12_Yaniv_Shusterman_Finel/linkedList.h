#ifndef LINKEDLISTH
#define LINKEDLISTH

#define FALSE 0
#define TRUE !FALSE

// Frame struct
typedef struct Frame
{
	char* name;
	unsigned int	duration;
	char* path;
} Frame;


// Link (node) struct
typedef struct FrameNode
{
	Frame* frame;
	struct FrameNode* next;
} FrameNode;

FrameNode* addFrameNode(FrameNode* head);
//void deleteLinkedList(FrameNode* head);
//FrameNode* findFrame(FrameNode* head);
//FrameNode* deleteFrame(FrameNode* head);
//FrameNode* changeFramePosition(FrameNode* head, int newLocation);
//void changeDuration(FrameNode* head, int newDuration, char* nameFrame);
////void changeAllDuration(FrameNode* head, int newDuration);
void printFrames(FrameNode* head);
void myFgets(char str[], int n);
int checkIfInList(char* name, FrameNode* head);

#endif