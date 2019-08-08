#pragma once

#include<stdio.h>
#include<conio.h>		//_getch()
#include<stdlib.h>		//system()
#include<string.h>		//strlen()

//定义一个学生
typedef struct tagStudent {
	char szName[20];	//姓名
	char szSex[4];		//性别
	int  nAge;			//年龄
	int  nStuNo;		//学号
	int  nScore;		//成绩
}Student;

//链表
//节点
typedef struct tagNode
{
	Student stu;			//学生信息
	struct tagNode* pNext;	//指向下一个节点
}Node;

//创建头节点
Node* g_pHead = NULL;		//指向头节点


//菜单
void Menu();
//1.录入学生信息
void InputStudent();
//2.打印学生信息
void PrintStudent();
//3.保存学生信息
void SaveStudent();
//4.读取学生信息
void ReadStudent();
//5.统计所有学生人数
void CountStudent();
//6.查找学生信息
void FindStudent();
//7.修改学生信息
void ChangeStudent();
//8.删除学生信息
void DeleteStudent();