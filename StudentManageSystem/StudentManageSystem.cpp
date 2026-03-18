// 学生成绩管理系统
// 开发语言：C语言
// 开发工具：Visual Studio 2019
// 开发时间：2019.4.14
// 开发者：summer

#include "StudentManageSystem.h"

/*
<> 直接从系统目录下查找包含的头文件
"" 先从工程的项目目录下查找，若没有，再到系统目录下查找
*/

// 获取科目名称
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
        // 打印菜单
        Menu();
        // 读取一个字符 数字,字符在内存中映射为ASCII码
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

// 菜单
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

// 1.录入学生信息
void InputStudent() {
    // 创建一个新节点
    Node* pNewNode = (Node*)malloc(sizeof(Node));
    pNewNode->pNext = NULL;

    // 找到链表尾部
    Node* p = g_pHead;
    while (g_pHead != NULL && p->pNext != NULL)
    {
        p = p->pNext;
    }

    // 将新节点添加到链表尾部
    if (g_pHead == NULL) {
        g_pHead = pNewNode;
    }
    else {
        p->pNext = pNewNode;
    }

    // 录入学生信息
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
    
    // 录入各科成绩
    for (int i = 0; i < SUBJECT_COUNT; i++) {
        printf("请输入%s成绩:\n", GetSubjectName(i));
        scanf_s("%d", &pNewNode->stu.nScores[i]);
    }

    printf("学生信息录入成功!\n\n");
    system("pause");
    system("cls");
}

// 2.打印学生信息
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
            // 计算平均分
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

// 3.保存学生信息
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
        fprintf(pFile,"%d %s %s %d %s %d %d %d\n",
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

    printf("数据保存成功!\n");
    system("pause");
    system("cls");
}

// 4.读取学生信息
void ReadStudent() {
    system("cls");

    FILE* pFile;
    pFile = fopen(".\\stuinfo.dat", "r");

    if (pFile == NULL) {
        printf("打开文件失败。\n");
        return;
    }
    
    // 释放原有链表内存
    Node* pTemp = g_pHead;
    while (pTemp != NULL) {
        Node* pNext = pTemp->pNext;
        free(pTemp);
        pTemp = pNext;
    }
    g_pHead = NULL;

    Node* pTail = NULL;
    
    while (!feof(pFile)) {
        Node* pNewNode = (Node*)malloc(sizeof(Node));
        pNewNode->pNext = NULL;
        
        int result = fscanf(pFile, "%d %s %s %d %s %d %d %d\n",
            &pNewNode->stu.nStuNo,
            pNewNode->stu.szName,
            pNewNode->stu.szSex,
            &pNewNode->stu.nAge,
            pNewNode->stu.szClassName,
            &pNewNode->stu.nScores[0],
            &pNewNode->stu.nScores[1],
            &pNewNode->stu.nScores[2]);
        
        if (result == 8) {
            if (g_pHead == NULL) {
                g_pHead = pNewNode;
                pTail = pNewNode;
            } else {
                pTail->pNext = pNewNode;
                pTail = pNewNode;
            }
        } else {
            free(pNewNode);
            break;
        }
    }
    
    fclose(pFile);

    printf("数据读取成功!\n");
    PrintStudent();
}

// 5.统计学生人数
void CountStudent() {
    int countStu = 0;

    Node* p = g_pHead;
    while (p != NULL)
    {
        countStu++;
        p = p->pNext;
    }
    printf("学生总人数为:%d\n\n", countStu);

    system("pause");
    system("cls");
}

// 6.查找学生信息
void FindStudent() {
    system("cls");
    int stuNum;
    printf("请输入要查找学生的学号:");
    scanf("%d", &stuNum);
    
    Node* p = g_pHead;
    bool isShowHead = false;
    bool isFindStu = false;
    while (p != NULL)
    {
        if (stuNum == p->stu.nStuNo) {
            if (!isShowHead) {
                printf("****************************************************************************************************\n");
                printf("*  学号  *  姓名  * 性别 * 年龄 *    班级    *  语文  *  数学  *  英语  *\n");
                printf("****************************************************************************************************\n");
                isShowHead = true;
            }
            printf("* %6d * %6s *  %s  *  %2d  * %10s *  %3d   *  %3d   *  %3d   *\n",
                p->stu.nStuNo,
                p->stu.szName,
                p->stu.szSex,
                p->stu.nAge,
                p->stu.szClassName,
                p->stu.nScores[0],
                p->stu.nScores[1],
                p->stu.nScores[2]
            );
            isFindStu = true;
            printf("****************************************************************************************************\n");
        }
        p = p->pNext;
    }

    if (!isFindStu) {
        printf("学号不存在系统中，请修改学号。\n\n");
    }

    system("pause");
    system("cls");
}

// 7.修改学生信息
void ChangeStudent() {
    int stuNum;
    printf("请输入要修改学生的学号:");
    scanf("%d", &stuNum);
    
    Node* p = g_pHead;
    bool isShowHead = false;
    bool isFindStu = false;
    while (p != NULL)
    {
        if (stuNum == p->stu.nStuNo) {
            if (!isShowHead) {
                printf("****************************************************************************************************\n");
                printf("*  学号  *  姓名  * 性别 * 年龄 *    班级    *  语文  *  数学  *  英语  *\n");
                printf("****************************************************************************************************\n");
                isShowHead = true;
            }
            printf("* %6d * %6s *  %s  *  %2d  * %10s *  %3d   *  %3d   *  %3d   *\n",
                p->stu.nStuNo,
                p->stu.szName,
                p->stu.szSex,
                p->stu.nAge,
                p->stu.szClassName,
                p->stu.nScores[0],
                p->stu.nScores[1],
                p->stu.nScores[2]
            );
            // 修改学生信息
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
            printf("学生信息修改成功，请及时保存。\n\n");
        }
        p = p->pNext;
    }

    if (!isFindStu) {
        printf("学号不存在系统中，无法进行修改。\n\n");
    }

    system("pause");
    system("cls");
}

// 8.删除学生信息
void DeleteStudent() {
    system("cls");
    int stuNum;
    printf("请输入要删除学生的学号:");
    scanf("%d", &stuNum);
    
    Node* p = g_pHead;
    Node* beforeNode = NULL;

    bool isShowHead = false;
    bool isFindStu = false;
    while (p != NULL)
    {
        if (stuNum == p->stu.nStuNo) {
            if (!isShowHead) {
                printf("****************************************************************************************************\n");
                printf("*  学号  *  姓名  * 性别 * 年龄 *    班级    *  语文  *  数学  *  英语  *\n");
                printf("****************************************************************************************************\n");
                isShowHead = true;
            }
            printf("* %6d * %6s *  %s  *  %2d  * %10s *  %3d   *  %3d   *  %3d   *\n",
                p->stu.nStuNo,
                p->stu.szName,
                p->stu.szSex,
                p->stu.nAge,
                p->stu.szClassName,
                p->stu.nScores[0],
                p->stu.nScores[1],
                p->stu.nScores[2]
            );
            isFindStu = true;
            printf("****************************************************************************************************\n");

            // 删除节点为头节点
            if (p == g_pHead) {
                g_pHead = p->pNext;
                free(p);
                p = g_pHead;
            }
            // 删除节点为中间或尾节点
            else {
                beforeNode->pNext = p->pNext;
                free(p);
                p = beforeNode->pNext;
            }
            printf("删除成功，记得保存。\n\n");
            continue;
        }
        beforeNode = p;
        p = p->pNext;
    }

    if (!isFindStu) {
        printf("学号不存在系统中，无法删除。\n\n");
    }

    system("pause");
    system("cls");
}

// 9.班级成绩统计分析
void ClassStatistics() {
    system("cls");
    
    if (g_pHead == NULL) {
        printf("系统中暂无学生信息，请先录入学生信息。\n\n");
        system("pause");
        system("cls");
        return;
    }
    
    char className[30];
    printf("请输入要统计的班级名称:");
    scanf("%s", className);
    
    // 统计该班级的学生
    int count = 0;
    double subjectTotals[SUBJECT_COUNT] = {0};
    double studentAvgSum = 0;
    
    Node* p = g_pHead;
    bool found = false;
    
    printf("\n");
    printf("================================================================================\n");
    printf("                        班级成绩统计分析报告                                    \n");
    printf("================================================================================\n");
    printf("班级名称: %s\n", className);
    printf("--------------------------------------------------------------------------------\n");
    printf("学生名单:\n");
    printf("--------------------------------------------------------------------------------\n");
    printf("*  学号  *  姓名  *  语文  *  数学  *  英语  *  平均分  *\n");
    printf("--------------------------------------------------------------------------------\n");
    
    while (p != NULL) {
        if (strcmp(p->stu.szClassName, className) == 0) {
            found = true;
            count++;
            
            // 计算该学生总分和平均分
            int studentSum = 0;
            for (int i = 0; i < SUBJECT_COUNT; i++) {
                studentSum += p->stu.nScores[i];
                subjectTotals[i] += p->stu.nScores[i];
            }
            double studentAvg = (double)studentSum / SUBJECT_COUNT;
            studentAvgSum += studentAvg;
            
            printf("* %6d * %6s *  %3d   *  %3d   *  %3d   *   %5.1f   *\n",
                p->stu.nStuNo,
                p->stu.szName,
                p->stu.nScores[0],
                p->stu.nScores[1],
                p->stu.nScores[2],
                studentAvg
            );
        }
        p = p->pNext;
    }
    
    printf("--------------------------------------------------------------------------------\n");
    
    if (!found) {
        printf("未找到该班级的学生信息。\n\n");
    } else {
        // 计算班级平均分
        double classAvg = studentAvgSum / count;
        
        printf("\n");
        printf("================================================================================\n");
        printf("                        班级整体情况统计                                        \n");
        printf("================================================================================\n");
        printf("班级学生人数: %d 人\n", count);
        printf("--------------------------------------------------------------------------------\n");
        printf("班级平均分(所有学生平均分的均值): %.2f 分\n", classAvg);
        printf("--------------------------------------------------------------------------------\n");
        printf("各科平均分:\n");
        for (int i = 0; i < SUBJECT_COUNT; i++) {
            printf("  %s: %.2f 分\n", GetSubjectName(i), subjectTotals[i] / count);
        }
        printf("================================================================================\n");
    }
    
    printf("\n");
    system("pause");
    system("cls");
}
