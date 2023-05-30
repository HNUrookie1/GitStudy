#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define bufferSize 100

char buffer[bufferSize];

char *tfgets(char *buf, int n, FILE *fp)
{
    if (n <= 0 || buf == NULL || fp == NULL)
    {
        return NULL;
    }

    char *s = buf;
    char c;
    int count = 0;
    n--; // 为末尾字符'\0'留下空间
    while (count < n)
    {
        c = fgetc(fp);
        if (c == EOF) // 到文件末尾
            break;

        *s = (char)c; // 将读取到的字符存储到缓冲区，s指向下一个位置,count累计加1
        count++;
        s++;

        if (c == '\n') // 当读取到换行符时，终止循环
            break;
    }

    if (count == 0 && c == EOF)
        return NULL; // 空文件返回 NULL

    *s = '\0'; // 将最后的字符设置为'\0'
    return buf;
}

int isdigits()
{
    for (int i = 0; i < strlen(buffer); i++)
        if (buffer[i] < '0' || buffer[i] > '9')
            return 0;
    return 1;
}

int ischar()
{
    for (int i = 0; i < strlen(buffer); i++)
        if (buffer[i] < 'A' || buffer[i] > 'Z' && buffer[i] < 'a' || buffer[i] > 'z')
            return 0;
    return 1;
}

int main()
{
    FILE *fp = fopen("test.txt", "r");
    char tmp[bufferSize];
    if (fp == NULL || tfgets(tmp, bufferSize, fp) == NULL)
    {
        printf("Failed to open the file.\n");
        exit(0);
    }
    for (int i = 0; i < strlen(tmp) - 1; i++)
        buffer[i] = tmp[i];
    if (isdigits())
        printf("Prompt: String consists of digits\n");
    else if (ischar())
        printf("Prompt: String consists of char\n");
    else
        printf("Prompt: String consists of digits and char\n");
    int kase = 1;
    printf("Case %d:", kase++);
    while (kase<50)
    {
        char tmp1[bufferSize];
        tfgets(tmp1, bufferSize, stdin);
	char input[bufferSize]={'\0'};
	for(int i=0;i<strlen(tmp1)-1;i++)
	    input[i]=tmp1[i];
        if (strlen(input) < strlen(buffer))
        {
            printf("Input length is too short!\nCase %d:", kase++);
            continue;
        }
        else if (strlen(input) > strlen(buffer))
        {
            printf("Input length is too long!\nCase %d:", kase++);
            continue;
        }
        if (strcmp(input, buffer) > 0)
        {
            printf("Input is larger than presupposed information\nCase %d:", kase++);
            continue;
        }
        else if (strcmp(input, buffer) < 0)
        {
            printf("Input is smaller than presupposed information\nCase %d:", kase++);
            continue;
        }
        break;
    }
    if(kase<50) printf("Success!\n");
    else printf("Too many input groups.\n");
    return 0;
}

