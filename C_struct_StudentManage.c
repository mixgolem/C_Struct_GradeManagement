#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define MAX_STUDENT 32 // 최대 학생수
#define MAX_LEN 10 // 최대 이름 길이

typedef struct STUDENT
{
    int number;
    char name[MAX_LEN];
    double grade;
} STUDENT;

// 학생 배열을 파라미터로 받아 전부 출력
void print_student(STUDENT student_arr[], int cnt)
{
    printf("\n");
    for (int i = 0; i < cnt; i++)
    {
        printf("학번: %d\n", student_arr[i].number);
        printf("이름: %s", student_arr[i].name);
        printf("학점: %.2lf\n\n", student_arr[i].grade);
    }
}

// 학생을 학생 배열에 추가하는 함수
// cnt의 주소를 받아옴(call by reference)
int add_student(STUDENT student_arr[], int *cnt)
{
    printf("학번을 입력하시오: ");
    scanf("%d", &student_arr[*cnt].number);
    if (student_arr[*cnt].number == -1) // 학번 입력 시 -1을 입력하면 함수도 -1을 리턴하고 종료
        return -1;
    rewind(stdin); // scanf 버퍼 비우기

    printf("이름을 입력하시오: ");
    fgets(student_arr[*cnt].name, MAX_LEN, stdin);

    printf("학점을 입력하시오(실수): ");
    scanf("%lf", &student_arr[(*cnt)++].grade); // 카운트가 가리키는 값을 인덱스로 사용 후 1만큼 증가

    rewind(stdin); // scanf 버퍼 비우기
    return 0;
}

// 버블 정렬 알고리즘을 이용해 학생 배열을 성적을 기준으로 오름차순 정렬
void sort_by_grade(STUDENT student_arr[], int cnt)
{
    for (int i = 0; i < cnt - 1; i++)
    {
        for (int j = 0; j < cnt - i - 1; j++)
        {
            if (student_arr[j].grade > student_arr[j + 1].grade)
            {
                // 성적을 기준으로 오름차순으로 교환
                STUDENT temp = student_arr[j];
                student_arr[j] = student_arr[j + 1];
                student_arr[j + 1] = temp;
            }
        }
    }
}

// 버블 정렬 알고리즘을 이용해 학생 배열을 성적을 기준으로 내림차순 정렬
void sort_by_grade_desc(STUDENT student_arr[], int cnt)
{
    for (int i = 0; i < cnt - 1; i++)
    {
        for (int j = 0; j < cnt - i - 1; j++)
        {
            if (student_arr[j].grade < student_arr[j + 1].grade)
            {
                // 성적을 기준으로 내림차순으로 교환
                STUDENT temp = student_arr[j];
                student_arr[j] = student_arr[j + 1];
                student_arr[j + 1] = temp;
            }
        }
    }
}

// 학생들의 성적 중 최고점 혹은 최하점을 반환하는 함수
// mode에 0을 줄 경우 최고점, 1을 줄 경우 최ㅎ하점을 반환
double max_min_grade(int mode, STUDENT student_arr[], int cnt)
{
    double tmp = student_arr[0].grade;
    if (!mode)
    {

        for (int i = 1; i < cnt; i++)
        {
            if (tmp < student_arr[i].grade)
                tmp = student_arr[i].grade;
        }
        return tmp;
    }
    else
    {
        for (int i = 1; i < cnt; i++)
        {
            if (tmp > student_arr[i].grade)
                tmp = student_arr[i].grade;
        }
        return tmp;
    }
}

// 학생들의 성적 총합을 계산
double sum_grade(STUDENT student_arr[], int cnt)
{
    double sum = 0;

    for (int i = 0; i < cnt; i++)
    {
        sum += student_arr[i].grade;
    }

    return sum;
}

int main(void)
{
    STUDENT student_arr[MAX_STUDENT];
    int cnt = 0; // 배열의 숫자를 카운트
    char select = '0';

    while (1)
    {
        printf("\n======================================================================================\n");
        printf("\t[1]학생추가\t[2]오름차순정렬\t[3]내림차순정렬\n\t[4]최고점\t[5]최하점\t[6]성적평균\t[7]총인원출력\n");
        printf("======================================================================================\n");

        select = getche(); // 사용자로부터 메뉴버튼을 입력받음
        fputs("번 선택\n\0", stdout);

        if (select == '1')
        { // 1번 : 학생 추가 모드
            if (add_student(student_arr, &cnt) == -1)
                break;
        }
        else if (select == '2')
        { // 2번 : 성적 오름차순으로 정렬하여 출력
            sort_by_grade(student_arr, cnt);
            printf("\n성적이 오름차순으로 정렬되었습니다.\n");
            print_student(student_arr, cnt);
        }
        else if (select == '3')
        { // 3번 : 성적 내림차순으로 정렬하여 출력
            sort_by_grade_desc(student_arr, cnt);
            printf("\n성적이 내림차순으로 정렬되었습니다.\n");
            print_student(student_arr, cnt);
        }
        else if (select == '4')
        { // 4번 : 학생들의 성적 중 최고점을 출력
            printf("최고점은 %.2lf 입니다.\n", max_min_grade(0, student_arr, cnt));
        }
        else if (select == '5')
        { // 5번 : 학생들의 성적 중 최하점을 출력
            printf("최하점은 %.2lf 입니다.\n", max_min_grade(1, student_arr, cnt));
        }
        else if (select == '6')
        { // 6번 : 성적의 총합 및 평균을 출력
            printf("성적의 총합은 %.2lf, 평균은 %.2lf 입니다.\n", sum_grade(student_arr, cnt), sum_grade(student_arr, cnt) / (double)cnt);
        }
        else if (select == '7')
        { // 7번 : 현재 총 인원을 출력
            printf("현재 총 인원은 %d명 입니다.\n", cnt);
            print_student(student_arr, cnt);
        }
        else // 해당되지 않을 경우 프로그램 종료
            break;
    }

    return 0;
}
