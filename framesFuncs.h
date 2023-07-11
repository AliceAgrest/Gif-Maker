#ifndef FRAMESfUNCSH
#define FRAMESfUNCSH
#define CV_IGNORE_DEBUG_BUILD_GUARD

#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"
#include "view.h"
#include <stdbool.h>
#include <string.h>

void addFrame(FrameNode** head);
void removeFrame(FrameNode** head);
void changeFrame(FrameNode** head);
void changeFrameDuration(FrameNode** head);
void changeAllDuration(FrameNode** head);
void saveProj(FrameNode* head);
void reversePlay(FrameNode** head);
void printList(FrameNode* head);

#endif
