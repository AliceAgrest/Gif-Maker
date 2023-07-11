#include "framesFuncs.h"
#pragma warning(disable : 4996)

#define NAME_LEN 100
#define PATH_LEN 200

bool isExist(FrameNode* head, char* nameToCheck);

//adding new frame into list
void addFrame(FrameNode** head)
{
	char* inputPath = (char*)malloc(sizeof(char) * PATH_LEN);
	char* inputName = (char*)malloc(sizeof(char) * NAME_LEN);
	int inputDuration;
	puts("*** Creatiwng new frame ***");
	FrameNode* curr = *head;
	FrameNode* prev = NULL;
	if(*head != NULL)
	{
		while (curr)
		{
			prev = curr;
			curr = curr->next;
		}
	}
	
	puts("Please insert frame path:");
	scanf("%s", inputPath);
	puts("Please insert frame duration (int miliseconds):");
	scanf("%d", &inputDuration);
	puts("Please choose a name for that frame:");
	scanf("%s", inputName);
	while(isExist(*head, inputName))
	{
		puts("The name is already taken, please enter another name");
		scanf("%s", inputName);
	}
	if (fopen(inputPath, "rb") == NULL)
		puts("Can't find file! Frame will not be added");
	else
	{
		curr = (FrameNode*)malloc(sizeof(FrameNode));
		curr->frame = (Frame*)malloc(sizeof(Frame));
		curr->frame->name = (char*)malloc(sizeof(char) * NAME_LEN);
		curr->frame->name = inputName;
		curr->frame->path = (char*)malloc(sizeof(char) * PATH_LEN);
		curr->frame->path = inputPath;
		curr->frame->duration = inputDuration;
		curr->next = NULL;
		if (*head == NULL)
			*head = curr;
		else
			prev->next = curr;
	}
}
//The func is checking if the name of frame is already in list
bool isExist(FrameNode* head, char* nameToCheck)
{
	FrameNode* curr = head;
	while (curr)
	{
		if (strcmp(curr->frame->name, nameToCheck) == 0)
			return true;
		curr = curr->next;
	}
	return false;
}

//the func is removing frame from the list
void removeFrame(FrameNode** head)
{
	FrameNode* curr = *head;
	FrameNode* prev = NULL;
	char* frameName = (char*)malloc(sizeof(char) * NAME_LEN);
	puts("Enter the name of the frame you wish to erase");
	scanf("%s", frameName);

	if (*head == NULL) {
		printf("List is empty.\n");
		return;
	}
	while (curr != NULL && strcmp(curr->frame->name, frameName) != 0)//Traverse the list to find the node containing the item
	{
		prev = curr;
		curr = curr->next;
	}
	if (curr == NULL) //If the item was not found
	{
		puts("The frame was not found");
		return;
	}
	if (prev == NULL)//If the item is found at the head of the list 
	{
		*head = curr->next;
	}
	else 
	{
		prev->next = curr->next;
	}
	free(curr);
}

//the func is changing frames by the name and index
void changeFrame(FrameNode** head)
{
	FrameNode* curr = *head;
	FrameNode* toChange = NULL;
	char* frameName = (char*)malloc(sizeof(char) * NAME_LEN);
	int index;
	int listIndex = 1;
	puts("Enter the name of the frame");
	scanf("%s", frameName);
	if (!isExist(*head, frameName))
	{
		puts("This frame does not exist");
		return;
	}
	else
	{
		puts("Enter the new index in the movie you wish to place the frame");
		scanf("%d", &index);

		while (curr)
		{
			if (strcmp(curr->frame->name, frameName) == 0)
			{
				toChange = curr;
				break;
			}
			curr = curr->next;
		}
		curr = *head;
		FrameNode* node = NULL;
		while (curr)
		{
			if (listIndex == index)
			{
				char* name = (char*)malloc(sizeof(char) * NAME_LEN);
				char* path = (char*)malloc(sizeof(char) * PATH_LEN);
				unsigned int dur;

				strcpy(name, curr->frame->name);
				strcpy(path, curr->frame->path);
				dur = curr->frame->duration;
				curr->frame->name = toChange->frame->name;
				curr->frame->path = toChange->frame->path;
				curr->frame->duration = toChange->frame->duration;

				toChange->frame->name = name;
				toChange->frame->path = path;
				toChange->frame->duration = dur;
				break;
			}
			curr = curr->next;
			listIndex++;
		}
	}
}

//The func is changing the duration of choosed frame
void changeFrameDuration(FrameNode** head)
{
	FrameNode* curr = *head;
	char* frameName = (char*)malloc(sizeof(char) * NAME_LEN);
	unsigned int newDuration;

	puts("Enter the name of the frame");
	scanf("%s", frameName);
	if(!isExist(*head, frameName))
		puts("This frame does not exist");
	else
	{
		puts("Enter the duration for frame:");
		scanf("%d", &newDuration);

		while (strcmp(curr->frame->name, frameName) != 0 && curr != NULL)
			curr = curr->next;

		curr->frame->duration = newDuration;
	}
}

//The func is changing all durations in list
void changeAllDuration(FrameNode** head)
{
	FrameNode* curr = *head;
	unsigned int newDuration;

	puts("Enter the duration for all frames:");
	scanf("%d", &newDuration);

	while (curr)
	{
		curr->frame->duration = newDuration;
		curr = curr->next;
	}
}

//The func is saving the project in input path
void saveProj(FrameNode* head)
{
	FrameNode* curr = head;
	char filePath[PATH_LEN] = { 0 };
	puts("Where to save the project? enter a full path and file name");
	scanf("%s", filePath);
	FILE* fp = fopen(filePath, "w");
	while (curr)
	{
		fprintf(fp, "%s - %s - %u\n", curr->frame->name, curr->frame->path, curr->frame->duration);
		curr = curr->next;
	}
	fclose(fp);
}

//The func is prints all the frames in list
void printList(FrameNode* head)
{
	FrameNode* curr = head;
	printf("%10s%10s%10s\n","Name","Duration","Path");
	while (curr)
	{
		printf("%10s%7d ms %15s\n",curr->frame->name, curr->frame->duration, curr->frame->path);
		curr = curr->next;
	}
}

//Bonus func
void reversePlay(FrameNode** head)
{
	FrameNode* perv = NULL;
	FrameNode* curr = *head;
	FrameNode* next1 = NULL;

	while (curr != NULL)
	{
		next1 = curr->next;
		curr->next = perv;
		perv = curr;
		curr = next1;
	}
	play(perv);
}