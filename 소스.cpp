#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct BOOK {
    char book_name[100];
    char auth_name[100];
    int year[100];
    char publ_name[100];
    char genre[100];
    int borrowed;
};

typedef struct BOOK BOOK;
int register_book(BOOK* book_list, int* nth);
int search_book(BOOK* book_list, int total_num_book);
int change_book(BOOK* book_list);
int remove_book(BOOK* book_list);
int print_book_list(BOOK* book_list, int total_num_book);
int save_book_list(BOOK** book_list, int* total_num_book);
char compare(char* str1, char* str2);

int main() {
    int user_choice;        /* ������ ������ �޴� */
    int num_total_book = 0; /* ���� å�� �� */

    BOOK* book_list;
    int i;

    printf("�������� �ִ� ���� �弭 ���� �������ּ��� : ");
    scanf("%d", &user_choice);

    book_list = (BOOK*)malloc(sizeof(BOOK) * user_choice);

    while (1) {
        printf("�޴��� �����ϼ��� \n");
        printf("1. å�� ���� �߰��ϱ� \n");
        printf("2. å�� �˻��ϱ� \n");
        printf("3. å ���� �����ϱ� \n");
        printf("4. å �����ϱ� \n");
        printf("5. ���� �� å ��� ����ϱ� \n");
        printf("6. å���� ������ �Է����Ͽ� �����ϱ� \n");
        printf("7. ���α׷� ������ \n");

        printf("1~7 �� �����ϼ��� : ");
        scanf("%d", &user_choice);

        if (user_choice == 1) {
            /* å�� ���� �߰��ϴ� �Լ� ȣ�� */
            register_book(book_list, &num_total_book);
        }
        else if (user_choice == 2) {
            /* å�� �˻��ϴ� �Լ� ȣ�� */
            search_book(book_list, num_total_book);
        }
        else if (user_choice == 3) {
            /* å�� �����ϴ� �Լ� ȣ�� */
            change_book(* book_list);
        }
        else if (user_choice == 4) {
            /* å�� �����ϴ� �Լ� ȣ�� */
            remove_book(* book_list);
        }
        else if (user_choice == 5) {
            /* ���� �� å ����� ����ϴ� �Լ� ȣ�� */
            print_book_list(* book_list, &num_total_book);
        }
        else if (user_choice == 6) {
            /* book.txt�� �����ϴ� �Լ� ȣ��*/
            save_book_list(*book_list, num_total_book);
        }
        else if (user_choice == 7) {
            /* ���α׷� ������ */
            break;
        }
    }

    free(book_list);
    return 0;
}
int save_book_list(BOOK* book_list, int total_num_book) {
    FILE* fp = fopen("book.txt", "w");
    int i;

    if (fp == NULL) {
        printf("��� ���� ! \n");
        return -1;
    }

    fprintf(fp, "%d\n", total_num_book);

    for (i = 0; i < total_num_book; i++) {
        fprintf(fp, "%s\n %s\n %d\n %s\n %s\n", book_list[i].book_name, book_list[i].auth_name, book_list[i].year,
            book_list[i].publ_name, book_list[i].genre);
    }

    printf("��� �Ϸ�! \n");
    fclose(fp);

    return 0;
}


int retrieve_book_info(BOOK** book_list, int* total_num_book) {
    FILE* fp = fopen("book.txt", "r");
    int total_book;
    int i;
    char str[10];

    if (fp == NULL) {
        printf("������ ������ ã�� �� �����ϴ�! \n");
        return -1;
    }

    fscanf(fp, "%d", &total_book);
    (*total_num_book) = total_book;

    free(*book_list);

    (*book_list) = (BOOK*)malloc(sizeof(BOOK) * total_book);

    if (*book_list == NULL) {
        printf("\n ERROR \n");
        return -1;
    }
    for (i = 0; i < total_book; i++) {

        fscanf(fp, "%s", (*book_list)[i].book_name);
        fscanf(fp, "%s", (*book_list)[i].auth_name);
        fscanf(fp, "%d", (*book_list)[i].year);
        fscanf(fp, "%s", (*book_list)[i].publ_name);
        fscanf(fp, "%s", (*book_list)[i].genre);
        fscanf(fp, "%s", str);
    }

    fclose(fp);
    return 0;
}
/* å�� �߰��ϴ� �Լ�*/
int register_book(BOOK* book, int* nth) {
    printf("å�� �̸� : ");
    scanf("%s", book[*nth].book_name);

    printf("å�� ���� : ");
    scanf("%s", book[*nth].auth_name);

    printf("���ǿ��� : ");
    scanf("%d", book[*nth].year);

    printf("å�� ���ǻ� : ");
    scanf("%s", book[*nth].publ_name);

    printf("�帣 : ");
    scanf("%s", book[*nth].genre);

    (*nth)++;

    return 0;
}
/* å�� �˻��ϴ� �Լ� */
int search_book(BOOK* book_list, int total_num_book) {
    int user_input; /* ������� �Է��� �޴´�. */
    int i;
    char user_search[100];

    printf("�˻��� ���� ���� \n");
    printf("1. å ���� �˻� \n");
    printf("2. ������ �˻� \n");
    printf("3. ���ǻ� �˻� \n");
    scanf("%d", &user_input);

    printf("�˻��� �ܾ �Է����ּ��� : ");
    scanf("%s", user_search);

    printf("�˻� ��� \n");

    if (user_input == 1) {
        /*

        i �� 0 ���� num_total_book ���� ���鼭 ������ å ������
        ����ڰ� �Է��� �˻���� ���ϰ� �ִ�.

        */
        for (i = 0; i < total_num_book; i++) {
            if (compare(book_list[i].book_name, user_search)) {
                printf("��ȣ : %d // å �̸� : %s // ������ : %s // ���ǻ� : %s \n", i,
                    book_list[i].book_name, book_list[i].auth_name,
                    book_list[i].publ_name);
            }
        }

    }
    else if (user_input == 2) {
        /*

        i �� 0 ���� num_total_book ���� ���鼭 ������ ������ �̸���
        ����ڰ� �Է��� �˻���� ���ϰ� �ִ�.

        */
        for (i = 0; i < total_num_book; i++) {
            if (compare(book_list[i].auth_name, user_search)) {
                printf("��ȣ : %d // å �̸� : %s // ������ : %s // ���ǻ� : %s \n", i,
                    book_list[i].book_name, book_list[i].auth_name,
                    book_list[i].publ_name);
            }
        }

    }