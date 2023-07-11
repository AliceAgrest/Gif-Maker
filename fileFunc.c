#include "fileFunc.h"
#pragma warning(disable : 4996)

#define NAME_LEN 100
#define PATH_LEN 200
#define BUFFER 256

void readFromFile(FILE* file, FrameNode** head);

//The func is checking if the client have started project and load it else it creates a new project
void file_proj(FrameNode** head)
{
	FrameNode* curr = *head;
	FrameNode* perv = NULL;
	char fp[PATH_LEN] = { 0 };
	int op;
	puts("Welcome to Magshimim Movie Maker! what would you like to do?");
	puts("[0] Create a new project");
	puts("[1] Load existing project");
	scanf("%d", &op);
	if (op == 1)
	{
		puts("Enter the path of the project (including project name):");
		scanf("%s", fp);
		FILE* file = fopen(fp, "r");
		if (file == NULL)
		{
			puts("Error! - cant open file, creating a new project");
		}
		else
		{
			readFromFile(file, head);
		}
		puts("Project loaded successfully");
	}
	else
		puts("Working on a new project.");
}

//The func is reading from the file name, path, duration and writes it into the linked list
void readFromFile(FILE* file, FrameNode** head)
{
	FrameNode* curr = *head;
	FrameNode* perv = NULL;
	char name[BUFFER] = { 0 };
	char path[BUFFER] = { 0 };
	unsigned duration = 0;
	while (fscanf(file, "%s - %s - %u\n", name, path, &duration) == 3)
	{
		curr = (FrameNode*)malloc(sizeof(FrameNode));
		curr->frame = (Frame*)malloc(sizeof(Frame));
		curr->frame->name = (char*)malloc(sizeof(char) * NAME_LEN);
		curr->frame->path = (char*)malloc(sizeof(char) * PATH_LEN);
		strcpy(curr->frame->name, name);
		strcpy(curr->frame->path, path);
		curr->frame->duration = duration;
		curr->next = NULL;
		if (*head == NULL)
		{
			perv = curr;
			*head = curr;
		}
		else
		{
			perv->next = curr;
			curr = curr->next;
			perv = perv->next;
		}
	}
}