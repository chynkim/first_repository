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
    int user_choice;        /* 유저가 선택한 메뉴 */
    int num_total_book = 0; /* 현재 책의 수 */

    BOOK* book_list;
    int i;

    printf("도서관의 최대 보관 장서 수를 설정해주세요 : ");
    scanf("%d", &user_choice);

    book_list = (BOOK*)malloc(sizeof(BOOK) * user_choice);

    while (1) {
        printf("메뉴를 선택하세요 \n");
        printf("1. 책을 새로 추가하기 \n");
        printf("2. 책을 검색하기 \n");
        printf("3. 책 정보 수정하기 \n");
        printf("4. 책 삭제하기 \n");
        printf("5. 현재 총 책 목록 출력하기 \n");
        printf("6. 책들의 내용을 입력파일에 저장하기 \n");
        printf("7. 프로그램 나가기 \n");

        printf("1~7 중 선택하세요 : ");
        scanf("%d", &user_choice);

        if (user_choice == 1) {
            /* 책을 새로 추가하는 함수 호출 */
            register_book(book_list, &num_total_book);
        }
        else if (user_choice == 2) {
            /* 책을 검색하는 함수 호출 */
            search_book(book_list, num_total_book);
        }
        else if (user_choice == 3) {
            /* 책을 수정하는 함수 호출 */
            change_book(* book_list);
        }
        else if (user_choice == 4) {
            /* 책을 삭제하는 함수 호출 */
            remove_book(* book_list);
        }
        else if (user_choice == 5) {
            /* 현재 총 책 목록을 출력하는 함수 호출 */
            print_book_list(* book_list, &num_total_book);
        }
        else if (user_choice == 6) {
            /* book.txt에 저장하는 함수 호출*/
            save_book_list(*book_list, num_total_book);
        }
        else if (user_choice == 7) {
            /* 프로그램 나가기 */
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
        printf("출력 오류 ! \n");
        return -1;
    }

    fprintf(fp, "%d\n", total_num_book);

    for (i = 0; i < total_num_book; i++) {
        fprintf(fp, "%s\n %s\n %d\n %s\n %s\n", book_list[i].book_name, book_list[i].auth_name, book_list[i].year,
            book_list[i].publ_name, book_list[i].genre);
    }

    printf("출력 완료! \n");
    fclose(fp);

    return 0;
}


int retrieve_book_info(BOOK** book_list, int* total_num_book) {
    FILE* fp = fopen("book.txt", "r");
    int total_book;
    int i;
    char str[10];

    if (fp == NULL) {
        printf("지정한 파일을 찾을 수 없습니다! \n");
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
/* 책을 추가하는 함수*/
int register_book(BOOK* book, int* nth) {
    printf("책의 이름 : ");
    scanf("%s", book[*nth].book_name);

    printf("책의 저자 : ");
    scanf("%s", book[*nth].auth_name);

    printf("출판연도 : ");
    scanf("%d", book[*nth].year);

    printf("책의 출판사 : ");
    scanf("%s", book[*nth].publ_name);

    printf("장르 : ");
    scanf("%s", book[*nth].genre);

    (*nth)++;

    return 0;
}
/* 책을 검색하는 함수 */
int search_book(BOOK* book_list, int total_num_book) {
    int user_input; /* 사용자의 입력을 받는다. */
    int i;
    char user_search[100];

    printf("검색할 내용 선택 \n");
    printf("1. 책 제목 검색 \n");
    printf("2. 지은이 검색 \n");
    printf("3. 출판사 검색 \n");
    scanf("%d", &user_input);

    printf("검색할 단어를 입력해주세요 : ");
    scanf("%s", user_search);

    printf("검색 결과 \n");

    if (user_input == 1) {
        /*

        i 가 0 부터 num_total_book 까지 가면서 각각의 책 제목을
        사용자가 입력한 검색어와 비교하고 있다.

        */
        for (i = 0; i < total_num_book; i++) {
            if (compare(book_list[i].book_name, user_search)) {
                printf("번호 : %d // 책 이름 : %s // 지은이 : %s // 출판사 : %s \n", i,
                    book_list[i].book_name, book_list[i].auth_name,
                    book_list[i].publ_name);
            }
        }

    }
    else if (user_input == 2) {
        /*

        i 가 0 부터 num_total_book 까지 가면서 각각의 지은이 이름을
        사용자가 입력한 검색어와 비교하고 있다.

        */
        for (i = 0; i < total_num_book; i++) {
            if (compare(book_list[i].auth_name, user_search)) {
                printf("번호 : %d // 책 이름 : %s // 지은이 : %s // 출판사 : %s \n", i,
                    book_list[i].book_name, book_list[i].auth_name,
                    book_list[i].publ_name);
            }
        }

    }