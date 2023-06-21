#ifndef LINKEDLISTH
#define LINKEDLISTH

#define FALSE 0
#define TRUE !FALSE
#define STR_LEN 1024

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

void addFrameNode(FrameNode** head);
int deleteFrame(FrameNode** head, char* nameOfFrame);
void changeFramePosition(FrameNode** head, int newLocation, char* frameToMove);
void changeDuration(FrameNode** head,unsigned int newDuration, char* nameFrame);
void changeAllDuration(FrameNode** head, int newDuration);
void printFrames(FrameNode* head);
void myFgets(char str[], int n);
int checkIfInList(char* name, FrameNode* head);
void freeList(FrameNode** head);
int findListLength(FrameNode** head);

#endif