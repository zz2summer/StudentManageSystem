
<h1>学生成绩管理系统</h1>

<h5>开发语言：C语言</h5>

<h5>开发工具：Visual Studio 2019</h5>

<h5>开发时间：2019.4.14</h5>

<h5>开发者：summer</h5>

[一、系统使用展示](#1)

[二、系统功能](#2)

[三、菜单](#3)

[四、录入学生信息](#4)

[五、打印学生信息](#5)

[六、保存学生信息](#6)

[七、读取学生信息](#7)

[八、统计所有学生人数](#8)

[九、查找学生信息](#9)

[十、修改学生信息](#10)

[十一、删除学生信息](#11)

[十二、退出系统](#12)

[十三、出错](#13)


<h3 id="1">一、系统使用展示</h3>


![Alt](demo.gif)


<h3 id="2">二、系统功能</h3>

1. 系统功能介绍

```
1.录入学生信息：用户可以自由输入学生信息到系统中。
2.打印学生信息：格式化展示系统中的学生信息。
3.保存学生信息：将系统中的学生信息保存到本地文档。
4.读取学生信息：读取本地文档中的学生信息并显示。
5.统计所有学生人数
6.查找学生信息：根据用户给定的信息（学号）在系统中查找该学生的信息
7.修改学生信息
8.删除学生信息
0.退出系统
```


2. 系统main函数，while循环在外，系统程序能够持续运行，switch判断语句进行功能选择与函数切换。

```C
int main() {
	while (1)
	{
		//打印菜单
		Menu();
		//读取一个字符 整数,字符在内存中映射为ASCII码
		char ch = _getch();

		switch (ch)
		{
		case '1'://1.录入学生信息
			InputStudent();
			break;
		case '2'://2.打印学生信息
			PrintStudent();
			break;
		case '3'://3.保存学生信息
			SaveStudent();
			break;
		case '4'://4.读取学生信息
			ReadStudent();
			break;
		case '5'://5.统计所有学生人数
			CountStudent();
			break;
		case '6'://6.查找学生信息
			FindStudent();
			break;
		case '7'://7.修改学生信息
			ChangeStudent();
			break;
		case '8'://8.删除学生信息
			DeleteStudent();
			break;
		case '0'://0.退出系统
			return 0;
			break;
		default:
			printf("输入有误，没有该功能\n\n");
			system("pause");  //暂停
			system("cls");    //清屏
			break;
		}
	}

	return 0;
}
```

<h3 id="3">三、菜单</h3>

1. 菜单显示

```C
//菜单
void Menu() {
	printf("*************************************************\n");
	printf("*\t欢迎使用高校学生成绩管理系统V1.0\t*\n");
	printf("*\t\t请选择功能\t\t\t*\n");
	printf("*************************************************\n");
	printf("*\t\t1.录入学生信息\t\t\t*\n");
	printf("*\t\t2.打印学生信息\t\t\t*\n");
	printf("*\t\t3.保存学生信息\t\t\t*\n");
	printf("*\t\t4.读取学生信息\t\t\t*\n");
	printf("*\t\t5.统计所有学生人数\t\t*\n");
	printf("*\t\t6.查找学生信息\t\t\t*\n");
	printf("*\t\t7.修改学生信息\t\t\t*\n");
	printf("*\t\t8.删除学生信息\t\t\t*\n");
	printf("*\t\t0.退出系统\t\t\t*\n");
	printf("*************************************************\n");
}
```

2. 打印菜单

scanf()、getchar()输入后均需要按enter，而getch()不用

```C
	//打印菜单
	Menu();
	//读取一个字符 整数,字符在内存中映射为ASCII码
	char ch = _getch();
```


<h3 id="4">四、录入学生信息</h3>

1. 定义学生结构体、链表节点结构体

```C
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
```


2. 利用学生结构体，以及链表操作输入学生信息

```C
//1.录入学生信息
void InputStudent() {
	//创建一个人，在堆中分配内存
	Node* pNewNode = (Node*)malloc(sizeof(Node));
	//指针下一个指向空
	pNewNode->pNext = NULL;

	//查找链表的尾结点
	Node* p = g_pHead;
	while (g_pHead != NULL && p->pNext != NULL)
	{
		p = p->pNext;
	}

	//把节点插到链表的尾节点
	if (g_pHead == NULL) {
		g_pHead = pNewNode;
	}
	else {
		p->pNext = pNewNode;
	}

	//录入学生信息
	printf("请输入学生姓名：\n");
	scanf_s("%s", pNewNode->stu.szName, sizeof(pNewNode->stu.szName));
	printf("请输入性别：\n");
	scanf_s("%s", pNewNode->stu.szSex, sizeof(pNewNode->stu.szSex));
	printf("请输入学生年龄：\n");
	scanf_s("%d", &pNewNode->stu.nAge);
	printf("请输入学号：\n");
	scanf_s("%d", &pNewNode->stu.nStuNo);
	printf("请输入成绩：\n");
	scanf_s("%d", &pNewNode->stu.nScore);

	printf("学生信息录入成功。\n\n");
	system("pause");
	system("cls");
}
```

<h3 id="5">五、打印学生信息</h3>

1. 读取链表结构，输出学生信息。先进行判空处理，如果无学生信息则输出提示信息，反之则正确输出学生信息。

```C
//2.打印学生信息
void PrintStudent() {

	system("cls");
	//遍历链表
	Node* p = g_pHead;
	if (p == NULL) {
		printf("系统中暂无学生信息，请录入后再来打印查看。\n\n");
	}
	else {
		printf("*********************************************************************************\n");
		printf("*\t\t\t欢迎使用高校学生成绩管理系统V1.0\t\t\t*\n");
		printf("*********************************************************************************\n");
		printf("*\t学号\t*\t姓名\t*\t性别\t*\t年龄\t*\t成绩\t*\n");
		printf("*********************************************************************************\n");

		while (p != NULL)
		{
			printf("*\t%d\t*\t%s\t*\t%s\t*\t%d\t*\t%d\t*\n",
				p->stu.nStuNo,
				p->stu.szName,
				p->stu.szSex,
				p->stu.nAge,
				p->stu.nScore
			);

			//下一个节点
			p = p->pNext;
			printf("*********************************************************************************\n");
		}
	}

	system("pause");
	system("cls");
}
```

<h3 id="6">六、保存学生信息</h3>

1. 利用文件对学生信息进行存储

```C
//3.保存学生信息
void SaveStudent() {
	//打开文件
	FILE* pFile;
	pFile = fopen(".\\stuinfo.dat", "w");
	
	if (pFile == NULL) {
		printf("打开文件失败。\n");
		return;
	}

	//写入数据
	Node* p = g_pHead;
	while (p != NULL)
	{
		fwrite(&p->stu, sizeof(Node), 1, pFile);
		p = p->pNext;
	}

	//关闭文件
	fclose(pFile);

	printf("数据保存成功。\n");
	system("pause");
	system("cls");
}
```

2. fopen在vs中会报错，解决方式

（1）按照vs的提示，将fopen换成fopen_s

（2）不修改函数，仅仅修改项目的属性。因为fopen_s是一种Microsoft的函数，若纯做Windows开发则直接改为_s也无妨，但是我们尽量还是用标准C++比较好，这样代码有较好的移植性。

具体操作：

右键工程名–>属性–>C/C++–>预处理器–>预处理器定义，编辑右边输入框加入： _CRT_SECURE_NO_WARNINGS 

保存（注意用分号隔开）。

<h3 id="7">七、读取学生信息</h3>

1. 打开存储学生信息的文本，单个单词读取，判断非分隔符或者空时则赋值给链表中的节点，读取完毕后，直接调用PrintStudent（）函数进行打印结果。

```C
//4.读取学生信息
void ReadStudent() {
	system("cls");

	//打开文件
	FILE* pFile;
	pFile = fopen(".\\stuinfo.dat", "r");

	if (pFile == NULL) {
		printf("打开文件失败。\n");
		return;
	}
	
	//创建一个人，在堆中分配内存
	Node* p = (Node*)malloc(sizeof(Node));
	p->pNext = NULL;
	//重新建立链表
	g_pHead = p;

	//逐个单词读入文本内容
	char str[200];
	int i = 0;
	while (fscanf(pFile, "%s", str) != EOF) {  //读文件 
		//单词不是*或者空时，进行赋值
		if (strcmp(str, "*") && str != NULL) {
			switch (i)
			{
			case 0:
				p->stu.nStuNo = atoi(str);
				break;
			case 1:
				strcpy(p->stu.szName, str);
				break;
			case 2:
				strcpy(p->stu.szSex, str);
				break;
			case 3:
				p->stu.nAge = atoi(str);
				break;
			case 4:
				p->stu.nScore = atoi(str);
				break;
			default:
				Node* pNewNode = (Node*)malloc(sizeof(Node));
				pNewNode->pNext = NULL;
				p->pNext = pNewNode;
				p = pNewNode;
				p->stu.nStuNo = atoi(str);
				i = 0;
				break;
			}
			i++;
		}
	}
	//打印读取结果
	PrintStudent();
}
```

2. 读取文本时，将内容全部赋值给char数组，所有赋值时需特殊处理。

- char数组赋值给整数

  在<stdlib.h>头文件中有两个函数，int atoi(char *p)和char *itoa(int p),分别将装有整数的char数组转化为整数，和将整数按位数分解依次存入char数组中。
  
- char数组赋值给char数组

  用strcpy函数！
  
  原型声明：extern char *strcpy(char *dest,char *src);
  
  头文件：string.h
  
  功能：把src所指由NULL结束的字符串复制到dest所指的数组中。
  
  说明：src和dest所指内存区域不可以重叠且dest必须有足够的空间来容纳src的字符串。
  
  返回指向dest的指针。
  
  注：不能使用memcpy(a, b, strlen(b)),会导致中文乱码。
  

<h3 id="8">八、统计所有学生人数</h3>

1. 设置计数器，遍历链表

```C
//5.统计所有学生人数
void CountStudent() {
	int countStu = 0;

	//遍历链表
	Node* p = g_pHead;
	while (p != NULL)
	{
		countStu++;
		p = p->pNext;
	}
	printf("学生总人数：%d\n\n", countStu);

	system("pause");
	system("cls");
}
```

<h3 id="9">九、查找学生信息</h3>

1. 本次查找以学号为示例，改用姓名等信息查询流程基本一致。

   遍历链表，如果有符合信息的学生则打印，反之则继续下一个节点，若系统中无该学生信息，给予用户无结果提示。
   
```C
//6.查找学生信息
void FindStudent() {
	system("cls");
	//以学号为查找示例，其他信息查找流程基本相似
	int stuNum;
	printf("请输入查找学生学号：");
	scanf("%d", &stuNum);
	//遍历链表查找，查找到后进行信息显示
	Node* p = g_pHead;
	//对表头进行展示一次
	bool isShowHead = false;
	//记录是否有找到该学号的学生信息
	bool isFindStu = false;
	while (p != NULL)
	{
		if (stuNum == p->stu.nStuNo) {
			if (!isShowHead) {
				printf("*********************************************************************************\n");
				printf("*\t学号\t*\t姓名\t*\t性别\t*\t年龄\t*\t成绩\t*\n");
				printf("*********************************************************************************\n");
				isShowHead = true;
			}
			printf("*\t%d\t*\t%s\t*\t%s\t*\t%d\t*\t%d\t*\n",
				p->stu.nStuNo,
				p->stu.szName,
				p->stu.szSex,
				p->stu.nAge,
				p->stu.nScore
			);
			isFindStu = true;
			printf("*********************************************************************************\n");
		}
		p = p->pNext;
	}

	if (!isFindStu) {
		printf("学号输入有误，系统中暂无该学生信息。\n\n");
	}

	system("pause");
	system("cls");
}
```

<h3 id="10">十、修改学生信息</h3>

1. 可参考查找学生信息代码段，在查找后进行修改即可

```C
//7.修改学生信息
void ChangeStudent() {
	//以学号为查找示例，其他信息查找流程基本相似
	int stuNum;
	printf("请输入欲修改学生的学号：");
	scanf("%d", &stuNum);
	//遍历链表查找，查找到后进行信息显示
	Node* p = g_pHead;
	//对表头进行展示一次
	bool isShowHead = false;
	//记录是否有找到该学号的学生信息
	bool isFindStu = false;
	while (p != NULL)
	{
		if (stuNum == p->stu.nStuNo) {
			if (!isShowHead) {
				printf("*********************************************************************************\n");
				printf("*\t学号\t*\t姓名\t*\t性别\t*\t年龄\t*\t成绩\t*\n");
				printf("*********************************************************************************\n");
				isShowHead = true;
			}
			printf("*\t%d\t*\t%s\t*\t%s\t*\t%d\t*\t%d\t*\n",
				p->stu.nStuNo,
				p->stu.szName,
				p->stu.szSex,
				p->stu.nAge,
				p->stu.nScore
			);
			//修改学生信息
			printf("请输入学生姓名：\n");
			scanf_s("%s", p->stu.szName, sizeof(p->stu.szName));
			printf("请输入性别：\n");
			scanf_s("%s", p->stu.szSex, sizeof(p->stu.szSex));
			printf("请输入学生年龄：\n");
			scanf_s("%d", &p->stu.nAge);
			printf("请输入学号：\n");
			scanf_s("%d", &p->stu.nStuNo);
			printf("请输入成绩：\n");
			scanf_s("%d", &p->stu.nScore);
			isFindStu = true;
			printf("*********************************************************************************\n");
			printf("学生信息修改成功，请注意及时保存。\n\n");
		}
		p = p->pNext;
	}

	if (!isFindStu) {
		printf("学号输入有误，系统中暂无该学生信息，无法进行修改。\n\n");
	}

	system("pause");
	system("cls");
}
```

<h3 id="11">十一、删除学生信息</h3>

1. 仍然以查找学生信息操作为基础，以学号为线索，查找到则进行删除，未查找到则进行错误提示，删除时需要区分当前节点是头结点、尾节点或者中间节点，不同节点操作不同，同时该删除仅作用于本次操作，需保存学生信息才能长久生效。

```C
//8.删除学生信息
void DeleteStudent() {
	system("cls");
	//以学号为查找示例，其他信息查找流程基本相似
	int stuNum;
	printf("请输入删除学生的学号：");
	scanf("%d", &stuNum);
	//遍历链表查找，查找到后进行信息显示
	Node* p = g_pHead;
	//记录前一个节点，删除时方便操作
	Node* beforeNode = g_pHead;

	//对表头进行展示一次
	bool isShowHead = false;
	//记录是否有找到该学号的学生信息
	bool isFindStu = false;
	while (p != NULL)
	{
		if (stuNum == p->stu.nStuNo) {
			if (!isShowHead) {
				printf("*********************************************************************************\n");
				printf("*\t学号\t*\t姓名\t*\t性别\t*\t年龄\t*\t成绩\t*\n");
				printf("*********************************************************************************\n");
				isShowHead = true;
			}
			printf("*\t%d\t*\t%s\t*\t%s\t*\t%d\t*\t%d\t*\n",
				p->stu.nStuNo,
				p->stu.szName,
				p->stu.szSex,
				p->stu.nAge,
				p->stu.nScore
			);
			isFindStu = true;
			printf("*********************************************************************************\n");

			//删除节点为头节点
			if (p == g_pHead) {
				g_pHead = p->pNext;
			}
			//删除节点为尾节点
			else if (p->pNext == NULL) {
				p = beforeNode;
				p->pNext = NULL;
			}
			//删除节点为中间节点
			else {
				beforeNode->pNext = p->pNext;
			}
			printf("删除成功，请记得保存。\n\n");
		}
		beforeNode = p;
		p = p->pNext;
	}

	if (!isFindStu) {
		printf("学号输入有误，系统中暂无该学生信息，无法进行删除操作。\n\n");
	}

	system("pause");
	system("cls");
}
```

<h3 id="12">十二、退出系统</h3>

直接在选择0时，设置return即可。


<h3 id="13">十三、出错</h3>

用户输入有误时，进行提示信息输出即可。

```C
	printf("输入有误，没有该功能\n\n");
	system("pause");  //暂停
	system("cls");    //清屏
```
***
项目源码：[C语言开发简单的学生成绩管理系统](https://github.com/zz2summer/C-CPP-Programs/tree/master/C%E8%AF%AD%E8%A8%80%E5%BC%80%E5%8F%91%E7%AE%80%E5%8D%95%E7%9A%84%E5%AD%A6%E7%94%9F%E6%88%90%E7%BB%A9%E7%AE%A1%E7%90%86%E7%B3%BB%E7%BB%9F)