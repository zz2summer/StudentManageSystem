//学生成绩管理系统
//开发语言：C语言
//开发工具：Visual Studio 2019
//开发时间：2019.4.14
//开发者：summer

#include "StudentManageSystem.h"

/*
<> 直接从系统目录下查找包含这个文件
"" 先从工程的项目目录下查找这个，如果没有，再到系统目录下查找
*/

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
		//fwrite(&p->stu, sizeof(Node), 1, pFile);
		fprintf(pFile,"*\t%d\t*\t%s\t*\t%s\t*\t%d\t*\t%d\t*\n",
			p->stu.nStuNo,
			p->stu.szName,
			p->stu.szSex,
			p->stu.nAge,
			p->stu.nScore);
		p = p->pNext;
	}
	//关闭文件
	fclose(pFile);

	printf("数据保存成功。\n");
	system("pause");
	system("cls");
}

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