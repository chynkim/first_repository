#include<stdio.h>

main()
{
    int num[] = { 501,601,702,802,902,905 };
    char* name[] = { "kim","mun","park","lee","choe","gang" };
    int score[] = { 90,100,40,80,60,50 };
    int i, a, sw, n;

    printf("��ȣ : ");
    scanf("%d", &a);

    sw=n=0;
    for (i = 0; i < 6; i++) {
        if (a == num[i])
            sw = 1;
            n++;
    }

    if (sw) {
        printf("�̸� : %s\n", name[n]);
        printf("���� : %d", score[n]);
    }
    else {
        printf("ã�� ���� �����ϴ�.");
    }
}