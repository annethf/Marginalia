#include <stdio.h>
#include <stdlib.h>
//����ַ�����Ĵ�С����һ�ַ���
#define getArrarySize(arrary) ((sizeof(arrary)) / (sizeof(arrary[0])))

//int��char�Ľ����һ��
int main()
{
    //int b[] = {0, 1, 2, 3, 4, 5};
    //int *a = b;
    char *b = "abcdefg";
    char *a = b;
    printf("sizeof(a) = %d\n", sizeof(a));
    printf("sizeof(b) = %d\n", sizeof(b));
    printf("sizeof(c) = %d\n", sizeof(b)/sizeof(char));
    return 0;
}
