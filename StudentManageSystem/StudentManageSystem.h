#pragma once

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

#define SUBJECT_COUNT 3

typedef struct tagStudent {
	char szName[20];
	char szSex[4];
	int  nAge;
	int  nStuNo;
	char szClassName[20];
	int  nScores[SUBJECT_COUNT];
}Student;

typedef struct tagNode
{
	Student stu;
	struct tagNode* pNext;
}Node;

Node* g_pHead = NULL;

void Menu();
void InputStudent();
void PrintStudent();
void SaveStudent();
void ReadStudent();
void CountStudent();
void FindStudent();
void ChangeStudent();
void DeleteStudent();
void ClassStatistics();
const char* GetSubjectName(int index);