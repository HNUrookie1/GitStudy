#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#define bufferSize 100
static jmp_buf jmpbuf;
static int error_count = 0;
const char correct_string[] ="hello";
char *tfgets(char *buf, int n, FILE *fp)
{   
        if (n <= 0 || buf == NULL || fp == NULL)
        {
            return NULL;
        }
        char *s = buf;
        int c;
        int count = 0;
       // n --; // 为末尾字符'\0'留下空间
        while (count < n) 
        {
            c = fgetc(fp);
            if (c == EOF) //到文件末尾或标准输入的末尾
                break;
            *s = (char)c;//将读取到的字符存储到缓冲区，s指向下一个位置,count累计加1
            count++;
            if (c == '\n')// 当读取到换行符时，终止循环
                break;
	    s++;
        }    
        if (count == 0 && c == EOF)
            return NULL; // 空文件返回 NULL
        *s = '\0';//将最后的字符设置为'\0'
        if (buf == NULL) {
            printf("error occurred.\n");
            return NULL;
        }
        if (strcmp(buf, correct_string) != 0) {
            error_count++;
            printf("Incorrect input.\n");
            longjmp(jmpbuf, 1);
        }
        else {
    	    error_count = 0;
     	    printf("Passed.\n");
	}
    return buf;
}


int main()
{
    char buffer[20];
    setjmp(jmpbuf);
    if (error_count >= 3) {
        printf("You have exceeded the maximum number of attempts.\n");
	return 0;
    }
    if (tfgets(buffer,10, stdin)!= NULL) {
        printf("Input successful: %s\n", buffer);
    }
    return 0;
}

