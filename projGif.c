#define CV_IGNORE_DEBUG_BUILD_GUARD
#pragma warning(disable : 4996)
#include <opencv2/imgcodecs/imgcodecs_c.h>
#include <opencv2/core/core_c.h>
#include <opencv2/highgui/highgui_c.h>
#include "view.h"
#include "linkedList.h"
#include "framesFuncs.h"
#include "fileFunc.h"
#include <stdio.h>
#include <stdlib.h>

#define NAME_LEN 100
#define PATH_LEN 200
#define BUFFER 256

void options();
void freeList(FrameNode* head);

enum NumOption {
	EXIT_OP,
	ADD_OP,
	REMOVE_OP,
	CHANGEF_OP,
	CHANGED_OP,
	CHANGEALLD_OP,
	PRINT_OP,
	PLAY_OP,
	REVERSE_PLAY_OP,
	SAVE_OP
}NumOption;

int main(void)
{
	FrameNode* firstFrame = NULL;
	int op;
	file_proj(&firstFrame);
	while (true)
	{
		options();
		scanf("%d", &op);

		switch (op)
		{
			case EXIT_OP:
				freeList(firstFrame);
				puts("Bye!");
				getchar();
				return 1;
			case ADD_OP:
				addFrame(&firstFrame);
				break;
			case REMOVE_OP:
				removeFrame(&firstFrame);
				break;
			case CHANGEF_OP:
				changeFrame(&firstFrame);
				break;
			case CHANGED_OP:
				changeFrameDuration(&firstFrame);
				break;
			case CHANGEALLD_OP:
				changeAllDuration(&firstFrame);
				break;
			case PRINT_OP:
				printList(firstFrame);
				break;
			case PLAY_OP:
				play(firstFrame);
				break;
			case REVERSE_PLAY_OP:
				reversePlay(&firstFrame);
				break;
			case SAVE_OP:
				saveProj(firstFrame);
				break;
			default:
				freeList(firstFrame);
				getchar();
				return;
		}
	}
	return 0;
}

void options()
{
	puts("What would you like to do?");
	puts("[0] Exit");
	puts("[1] Add new Frame");
	puts("[2] Remove a Frame");
	puts("[3] Change frame index");
	puts("[4] Change frame duration");
	puts("[5] Change duration of all frames");
	puts("[6] List frames");
	puts("[7] Play movie!");
	puts("[8] Play reversed movie!");
	puts("[9] Save project");
}

void freeList(FrameNode* head)
{
	FrameNode* tmp;
	if (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->frame);
		free(tmp);
		freeList(head);
	}
}