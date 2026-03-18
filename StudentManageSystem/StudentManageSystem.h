#pragma once

#include<stdio.h>
#include<conio.h>		
#include<stdlib.h>		
#include<string.h>		

#define SUBJECT_COUNT 3

// 学生结构体
typedef struct tagStudent {
	char szName[20];	
	char szSex[4];		
	int  nAge;			
	int  nStuNo;		
	int  nScores[SUBJECT_COUNT];	
	char szClassName[30];			
}Student;

// 班级信息结构体
typedef struct tagClassInfo {
	char szClassName[30];	
	int  nStudentCount;		
}ClassInfo;

// 节点结构体
typedef struct tagNode
{
	Student stu;			
	struct tagNode* pNext;	
}Node;

// 全局变量
Node* g_pHead = NULL;		

// 菜单
void Menu();
// 1.录入学生信息
void InputStudent();
// 2.打印学生信息
void PrintStudent();
// 3.保存学生信息
void SaveStudent();
// 4.读取学生信息
void ReadStudent();
// 5.统计学生人数
void CountStudent();
// 6.查找学生信息
void FindStudent();
// 7.修改学生信息
void ChangeStudent();
// 8.删除学生信息
void DeleteStudent();
// 9.班级成绩统计分析
void ClassStatistics();
// 获取科目名称
const char* GetSubjectName(int index);
