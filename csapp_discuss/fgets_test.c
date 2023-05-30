#include <stdio.h>
#include <stdlib.h>
#define bufferSize 100

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
        // 使用 fgets 读取内容
        printf("Using fgets:\n");
        while (fgets(buffer, bufferSize, fp) != NULL)
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

        // 使用 fgets 读取内容
        printf("Using fgets:\n");
        while (fgets(buffer, bufferSize, stdin) != NULL)
        {
            printf("%s", buffer);
        }
        printf("\n-------------\n");
        break;
    }
    }

    return 0;
}
