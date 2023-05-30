#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#define bufferSize 100
#define TIME 10 //定义的超时时限
#define warning1 "输入错误"//输入错误返回warning1
#define warning2 "已超时"//超时返回warning2

char *ans="ABC\n";//预置正确输入
int flag=0;//用于判断

void handler()//超时处理函数
{
    printf("%s\n",warning2);//打印超时警告
    flag=1;
}
char *tfgets(char *buf, int n, FILE *fp)
{
    signal(SIGALRM,handler); //signal函数处理信号
    if (n <= 0 || buf == NULL || fp == NULL)
    {
        return NULL;
    }
    alarm(TIME);//alarm函数计时
    char *s = buf;
    int c;
    int count = 0;
    n --; // 为末尾字符'\0'留下空间
    while (count < n) 
    {
        c = fgetc(fp);
        if (c == EOF) //到文件末尾或标准输入的末尾
            break;

        *s = (char)c;//将读取到的字符存储到缓冲区，s指向下一个位置,count累计加1
        count++;
        s++;

        if (c == '\n')// 当读取到换行符时，终止循环
            break;
    }

    if (count == 0 && c == EOF)
        return NULL; // 空文件返回 NULL

    *s = '\0';//将最后的字符设置为'\0'

    if(strcmp(buf,ans)!=0)//错误输入
    {
        printf("%s\n",warning1);
        return warning1;
    }
    else if(flag==1)//超时
    {
        flag=0;
        return warning2;
    }
    else return buf;//正确输入
}

int main()
{
    char buffer[bufferSize];

    int choice;

    printf("Enter '1' to read from file, or any other key to read from standard input: ");
    char input[10];
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d", &choice);

    switch (choice)
    {
    case 1:
    {
        FILE *fp = fopen("test.txt", "r"); // 打开测试文件
        if (fp == NULL)
        {
            printf("Failed to open the file.\n");
            exit(0);
        }

        // 使用 tfgets 读取内容
        printf("Using tfgets:\n");
        while (tfgets(buffer, bufferSize, fp) != NULL)
        {
            printf("%s", buffer);
        }
         printf("\n-------------\n");

        // 关闭文件
        fclose(fp);
        break;
    }
    default:
    {
        printf("Enter text (press Ctrl+D or Ctrl+Z to stop):\n");

        // 使用 tfgets 读取内容
        printf("Using tfgets:\n");
        while (tfgets(buffer, bufferSize, stdin) != NULL)
        {
            printf("%s", buffer);
        }
        printf("\n-------------\n");
        break;
    }
    }

    return 0;
}
