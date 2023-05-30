#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define bufferSize 100
char *tfgets(char *buf, int n, FILE *stream)
{
    if (n <= 0 || buf == NULL || stream == NULL)
    {
        return NULL;
    }
    char *s = buf;
    char c;
    int count = 0;
    n--; // 为末尾字符'\0'留下空间
    while (count < n)
    {
        c = fgetc(stream);
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
/*
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
        FILE *stream = fopen("test.txt", "r"); // 打开测试文件
        if (stream == NULL)
        {
            printf("Failed to open the file.\n");
            exit(0);
        }

        // 使用 tfgets 读取内容
        printf("Using tfgets:\n");
        while (tfgets(buffer, bufferSize, stream) != NULL)
        {
            printf("%s", buffer);
        }
         printf("\n-------------\n");

        // 关闭文件
        fclose(stream);
        break;
    }
    default:
    {
        printf("Enter text (press Ctrl+C or Ctrl+Z to stop):\n");

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
}*/


int main()
{
    char buffer[20];
    while (1)
    {
        tfgets(buffer, 5, stdin);
        printf("%s", buffer);
        printf("继续输入\n");
        // 检查输入的字符长度是否超过缓冲区大小
       /* if (buffer[strlen(buffer) - 1] != '\n')
        {
            int c;
            while ((c = getchar()) != '\n');
        }*/
    }

    return 0;
}

