#include "StudentManageSystem.h"

const char* GetSubjectName(int index) {
	switch (index) {
	case 0: return "语文";
	case 1: return "数学";
	case 2: return "英语";
	default: return "未知";
	}
}

int main() {
	while (1)
	{
		Menu();
		char ch = _getch();

		switch (ch)
		{
		case '1':
			InputStudent();
			break;
		case '2':
			PrintStudent();
			break;
		case '3':
			SaveStudent();
			break;
		case '4':
			ReadStudent();
			break;
		case '5':
			CountStudent();
			break;
		case '6':
			FindStudent();
			break;
		case '7':
			ChangeStudent();
			break;
		case '8':
			DeleteStudent();
			break;
		case '9':
			ClassStatistics();
			break;
		case '0':
			return 0;
			break;
		default:
			printf("您输入的没有该功能\n\n");
			system("pause");
			system("cls");
			break;
		}
	}

	return 0;
}

void Menu() {
	printf("*************************************************\n");
	printf("*\t欢迎使用高校学生成绩管理系统V2.0\t*\n");
	printf("*\t\t请选择功能\t\t\t*\n");
	printf("*************************************************\n");
	printf("*\t\t1.录入学生信息\t\t\t*\n");
	printf("*\t\t2.打印学生信息\t\t\t*\n");
	printf("*\t\t3.保存学生信息\t\t\t*\n");
	printf("*\t\t4.读取学生信息\t\t\t*\n");
	printf("*\t\t5.统计学生人数\t\t\t*\n");
	printf("*\t\t6.查找学生信息\t\t\t*\n");
	printf("*\t\t7.修改学生信息\t\t\t*\n");
	printf("*\t\t8.删除学生信息\t\t\t*\n");
	printf("*\t\t9.班级成绩统计\t\t\t*\n");
	printf("*\t\t0.退出系统\t\t\t*\n");
	printf("*************************************************\n");
}

void InputStudent() {
	Node* pNewNode = (Node*)malloc(sizeof(Node));
	pNewNode->pNext = NULL;

	Node* p = g_pHead;
	while (g_pHead != NULL && p->pNext != NULL)
	{
		p = p->pNext;
	}

	if (g_pHead == NULL) {
		g_pHead = pNewNode;
	}
	else {
		p->pNext = pNewNode;
	}

	printf("请输入学生姓名:\n");
	scanf_s("%s", pNewNode->stu.szName, sizeof(pNewNode->stu.szName));
	printf("请输入性别:\n");
	scanf_s("%s", pNewNode->stu.szSex, sizeof(pNewNode->stu.szSex));
	printf("请输入学生年龄:\n");
	scanf_s("%d", &pNewNode->stu.nAge);
	printf("请输入学号:\n");
	scanf_s("%d", &pNewNode->stu.nStuNo);
	printf("请输入班级名称:\n");
	scanf_s("%s", pNewNode->stu.szClassName, sizeof(pNewNode->stu.szClassName));

	for (int i = 0; i < SUBJECT_COUNT; i++) {
		printf("请输入%s成绩:\n", GetSubjectName(i));
		scanf_s("%d", &pNewNode->stu.nScores[i]);
	}

	printf("学生信息录入成功!\n\n");
	system("pause");
	system("cls");
}

void PrintStudent() {
	system("cls");
	Node* p = g_pHead;
	if (p == NULL) {
		printf("系统中暂无学生信息，请先录入后再打印查看。\n\n");
	}
	else {
		printf("****************************************************************************************************\n");
		printf("*\t\t\t欢迎使用高校学生成绩管理系统V2.0\t\t\t\t\t     *\n");
		printf("****************************************************************************************************\n");
		printf("*  学号  *  姓名  * 性别 * 年龄 *    班级    *  语文  *  数学  *  英语  *  平均分  *\n");
		printf("****************************************************************************************************\n");

		while (p != NULL)
		{
			int sum = 0;
			for (int i = 0; i < SUBJECT_COUNT; i++) {
				sum += p->stu.nScores[i];
			}
			double avg = (double)sum / SUBJECT_COUNT;

			printf("* %6d * %6s *  %s  *  %2d  * %10s *  %3d   *  %3d   *  %3d   *   %5.1f   *\n",
				p->stu.nStuNo,
				p->stu.szName,
				p->stu.szSex,
				p->stu.nAge,
				p->stu.szClassName,
				p->stu.nScores[0],
				p->stu.nScores[1],
				p->stu.nScores[2],
				avg
			);

			p = p->pNext;
			printf("****************************************************************************************************\n");
		}
	}

	system("pause");
	system("cls");
}

void SaveStudent() {
	FILE* pFile;
	pFile = fopen(".\\stuinfo.dat", "w");

	if (pFile == NULL) {
		printf("打开文件失败。\n");
		return;
	}

	Node* p = g_pHead;
	while (p != NULL)
	{
		fprintf(pFile, "%d %s %s %d %s %d %d %d\n",
			p->stu.nStuNo,
			p->stu.szName,
			p->stu.szSex,
			p->stu.nAge,
			p->stu.szClassName,
			p->stu.nScores[0],
			p->stu.nScores[1],
			p->stu.nScores[2]);
		p = p->pNext;
	}
	fclose(pFile);

	printf("数据保存成功。\n");
	system("pause");
	system("cls");
}

void ReadStudent() {
	system("cls");

	FILE* pFile;
	pFile = fopen(".\\stuinfo.dat", "r");

	if (pFile == NULL) {
		printf("打开文件失败。\n");
		return;
	}

	Node* p = (Node*)malloc(sizeof(Node));
	p->pNext = NULL;
	g_pHead = p;

	while (fscanf(pFile, "%d %s %s %d %s %d %d %d",
		&p->stu.nStuNo,
		p->stu.szName,
		p->stu.szSex,
		&p->stu.nAge,
		p->stu.szClassName,
		&p->stu.nScores[0],
		&p->stu.nScores[1],
		&p->stu.nScores[2]) != EOF) {

		Node* pNewNode = (Node*)malloc(sizeof(Node));
		pNewNode->pNext = NULL;
		p->pNext = pNewNode;
		p = pNewNode;
	}

	fclose(pFile);
	PrintStudent();
}

void CountStudent() {
	int countStu = 0;

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

void FindStudent() {
	system("cls");
	int stuNum;
	printf("请输入查找学生学号：");
	scanf("%d", &stuNum);

	Node* p = g_pHead;
	bool isShowHead = false;
	bool isFindStu = false;
	while (p != NULL)
	{
		if (stuNum == p->stu.nStuNo) {
			if (!isShowHead) {
				printf("****************************************************************************************************\n");
				printf("*  学号  *  姓名  * 性别 * 年龄 *    班级    *  语文  *  数学  *  英语  *  平均分  *\n");
				printf("****************************************************************************************************\n");
				isShowHead = true;
			}
			int sum = 0;
			for (int i = 0; i < SUBJECT_COUNT; i++) {
				sum += p->stu.nScores[i];
			}
			double avg = (double)sum / SUBJECT_COUNT;

			printf("* %6d * %6s *  %s  *  %2d  * %10s *  %3d   *  %3d   *  %3d   *   %5.1f   *\n",
				p->stu.nStuNo,
				p->stu.szName,
				p->stu.szSex,
				p->stu.nAge,
				p->stu.szClassName,
				p->stu.nScores[0],
				p->stu.nScores[1],
				p->stu.nScores[2],
				avg
			);
			isFindStu = true;
			printf("****************************************************************************************************\n");
		}
		p = p->pNext;
	}

	if (!isFindStu) {
		printf("学生不存在于系统中，请核对信息！\n\n");
	}

	system("pause");
	system("cls");
}

void ChangeStudent() {
	int stuNum;
	printf("请输入修改学生学号：");
	scanf("%d", &stuNum);

	Node* p = g_pHead;
	bool isShowHead = false;
	bool isFindStu = false;
	while (p != NULL)
	{
		if (stuNum == p->stu.nStuNo) {
			if (!isShowHead) {
				printf("****************************************************************************************************\n");
				printf("*  学号  *  姓名  * 性别 * 年龄 *    班级    *  语文  *  数学  *  英语  *  平均分  *\n");
				printf("****************************************************************************************************\n");
				isShowHead = true;
			}
			int sum = 0;
			for (int i = 0; i < SUBJECT_COUNT; i++) {
				sum += p->stu.nScores[i];
			}
			double avg = (double)sum / SUBJECT_COUNT;

			printf("* %6d * %6s *  %s  *  %2d  * %10s *  %3d   *  %3d   *  %3d   *   %5.1f   *\n",
				p->stu.nStuNo,
				p->stu.szName,
				p->stu.szSex,
				p->stu.nAge,
				p->stu.szClassName,
				p->stu.nScores[0],
				p->stu.nScores[1],
				p->stu.nScores[2],
				avg
			);

			printf("请输入学生姓名:\n");
			scanf_s("%s", p->stu.szName, sizeof(p->stu.szName));
			printf("请输入性别:\n");
			scanf_s("%s", p->stu.szSex, sizeof(p->stu.szSex));
			printf("请输入学生年龄:\n");
			scanf_s("%d", &p->stu.nAge);
			printf("请输入学号:\n");
			scanf_s("%d", &p->stu.nStuNo);
			printf("请输入班级名称:\n");
			scanf_s("%s", p->stu.szClassName, sizeof(p->stu.szClassName));

			for (int i = 0; i < SUBJECT_COUNT; i++) {
				printf("请输入%s成绩:\n", GetSubjectName(i));
				scanf_s("%d", &p->stu.nScores[i]);
			}

			isFindStu = true;
			printf("****************************************************************************************************\n");
			printf("学生信息修改成功！请注意及时保存。\n\n");
		}
		p = p->pNext;
	}

	if (!isFindStu) {
		printf("学生不存在于系统中，无法进行修改。\n\n");
	}

	system("pause");
	system("cls");
}

void DeleteStudent() {
	system("cls");
	int stuNum;
	printf("请输入删除学生学号：");
	scanf("%d", &stuNum);

	Node* p = g_pHead;
	Node* beforeNode = g_pHead;

	bool isShowHead = false;
	bool isFindStu = false;
	while (p != NULL)
	{
		if (stuNum == p->stu.nStuNo) {
			if (!isShowHead) {
				printf("****************************************************************************************************\n");
				printf("*  学号  *  姓名  * 性别 * 年龄 *    班级    *  语文  *  数学  *  英语  *  平均分  *\n");
				printf("****************************************************************************************************\n");
				isShowHead = true;
			}
			int sum = 0;
			for (int i = 0; i < SUBJECT_COUNT; i++) {
				sum += p->stu.nScores[i];
			}
			double avg = (double)sum / SUBJECT_COUNT;

			printf("* %6d * %6s *  %s  *  %2d  * %10s *  %3d   *  %3d   *  %3d   *   %5.1f   *\n",
				p->stu.nStuNo,
				p->stu.szName,
				p->stu.szSex,
				p->stu.nAge,
				p->stu.szClassName,
				p->stu.nScores[0],
				p->stu.nScores[1],
				p->stu.nScores[2],
				avg
			);
			isFindStu = true;
			printf("****************************************************************************************************\n");

			if (p == g_pHead) {
				g_pHead = p->pNext;
			}
			else if (p->pNext == NULL) {
				p = beforeNode;
				p->pNext = NULL;
			}
			else {
				beforeNode->pNext = p->pNext;
			}
			printf("删除成功！记得保存。\n\n");
		}
		beforeNode = p;
		p = p->pNext;
	}

	if (!isFindStu) {
		printf("学生不存在于系统中，无法进行删除操作！\n\n");
	}

	system("pause");
	system("cls");
}

void ClassStatistics() {
	system("cls");

	if (g_pHead == NULL) {
		printf("系统中没有学生信息，请先录入！\n\n");
		system("pause");
		system("cls");
		return;
	}

	char targetClass[20];
	printf("请输入要统计的班级名称：");
	scanf("%s", targetClass);

	int countStu = 0;
	int totalScores[SUBJECT_COUNT] = { 0 };
	double totalAvgScore = 0;

	Node* p = g_pHead;
	bool hasClass = false;

	while (p != NULL)
	{
		if (strcmp(p->stu.szClassName, targetClass) == 0) {
			hasClass = true;
			countStu++;
			int sum = 0;
			for (int i = 0; i < SUBJECT_COUNT; i++) {
				totalScores[i] += p->stu.nScores[i];
				sum += p->stu.nScores[i];
			}
			totalAvgScore += (double)sum / SUBJECT_COUNT;
		}
		p = p->pNext;
	}

	if (!hasClass) {
		printf("未找到班级【%s】的学生信息！\n\n", targetClass);
	}
	else {
		printf("\n=================================================\n");
		printf("           班级成绩统计分析报告\n");
		printf("=================================================\n");
		printf("  班级名称：%s\n", targetClass);
		printf("  学生人数：%d 人\n", countStu);
		printf("-------------------------------------------------\n");
		printf("  成绩整体情况：\n");
		printf("  ├─ 班级平均分：%.2f 分\n", totalAvgScore / countStu);
		printf("  ├─ 语文平均分：%.2f 分\n", (double)totalScores[0] / countStu);
		printf("  ├─ 数学平均分：%.2f 分\n", (double)totalScores[1] / countStu);
		printf("  └─ 英语平均分：%.2f 分\n", (double)totalScores[2] / countStu);
		printf("=================================================\n\n");
	}

	system("pause");
	system("cls");
}