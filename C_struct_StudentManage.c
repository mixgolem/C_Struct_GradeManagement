#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define MAX_STUDENT 32 // �ִ� �л���
#define MAX_LEN 10 // �ִ� �̸� ����

typedef struct STUDENT
{
    int number;
    char name[MAX_LEN];
    double grade;
} STUDENT;

// �л� �迭�� �Ķ���ͷ� �޾� ���� ���
void print_student(STUDENT student_arr[], int cnt)
{
    printf("\n");
    for (int i = 0; i < cnt; i++)
    {
        printf("�й�: %d\n", student_arr[i].number);
        printf("�̸�: %s", student_arr[i].name);
        printf("����: %.2lf\n\n", student_arr[i].grade);
    }
}

// �л��� �л� �迭�� �߰��ϴ� �Լ�
// cnt�� �ּҸ� �޾ƿ�(call by reference)
int add_student(STUDENT student_arr[], int *cnt)
{
    printf("�й��� �Է��Ͻÿ�: ");
    scanf("%d", &student_arr[*cnt].number);
    if (student_arr[*cnt].number == -1) // �й� �Է� �� -1�� �Է��ϸ� �Լ��� -1�� �����ϰ� ����
        return -1;
    rewind(stdin); // scanf ���� ����

    printf("�̸��� �Է��Ͻÿ�: ");
    fgets(student_arr[*cnt].name, MAX_LEN, stdin);

    printf("������ �Է��Ͻÿ�(�Ǽ�): ");
    scanf("%lf", &student_arr[(*cnt)++].grade); // ī��Ʈ�� ����Ű�� ���� �ε����� ��� �� 1��ŭ ����

    rewind(stdin); // scanf ���� ����
    return 0;
}

// ���� ���� �˰����� �̿��� �л� �迭�� ������ �������� �������� ����
void sort_by_grade(STUDENT student_arr[], int cnt)
{
    for (int i = 0; i < cnt - 1; i++)
    {
        for (int j = 0; j < cnt - i - 1; j++)
        {
            if (student_arr[j].grade > student_arr[j + 1].grade)
            {
                // ������ �������� ������������ ��ȯ
                STUDENT temp = student_arr[j];
                student_arr[j] = student_arr[j + 1];
                student_arr[j + 1] = temp;
            }
        }
    }
}

// ���� ���� �˰����� �̿��� �л� �迭�� ������ �������� �������� ����
void sort_by_grade_desc(STUDENT student_arr[], int cnt)
{
    for (int i = 0; i < cnt - 1; i++)
    {
        for (int j = 0; j < cnt - i - 1; j++)
        {
            if (student_arr[j].grade < student_arr[j + 1].grade)
            {
                // ������ �������� ������������ ��ȯ
                STUDENT temp = student_arr[j];
                student_arr[j] = student_arr[j + 1];
                student_arr[j + 1] = temp;
            }
        }
    }
}

// �л����� ���� �� �ְ��� Ȥ�� �������� ��ȯ�ϴ� �Լ�
// mode�� 0�� �� ��� �ְ���, 1�� �� ��� �֤������� ��ȯ
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

// �л����� ���� ������ ���
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
    int cnt = 0; // �迭�� ���ڸ� ī��Ʈ
    char select = '0';

    while (1)
    {
        printf("\n======================================================================================\n");
        printf("\t[1]�л��߰�\t[2]������������\t[3]������������\n\t[4]�ְ���\t[5]������\t[6]�������\t[7]���ο����\n");
        printf("======================================================================================\n");

        select = getche(); // ����ڷκ��� �޴���ư�� �Է¹���
        fputs("�� ����\n\0", stdout);

        if (select == '1')
        { // 1�� : �л� �߰� ���
            if (add_student(student_arr, &cnt) == -1)
                break;
        }
        else if (select == '2')
        { // 2�� : ���� ������������ �����Ͽ� ���
            sort_by_grade(student_arr, cnt);
            printf("\n������ ������������ ���ĵǾ����ϴ�.\n");
            print_student(student_arr, cnt);
        }
        else if (select == '3')
        { // 3�� : ���� ������������ �����Ͽ� ���
            sort_by_grade_desc(student_arr, cnt);
            printf("\n������ ������������ ���ĵǾ����ϴ�.\n");
            print_student(student_arr, cnt);
        }
        else if (select == '4')
        { // 4�� : �л����� ���� �� �ְ����� ���
            printf("�ְ����� %.2lf �Դϴ�.\n", max_min_grade(0, student_arr, cnt));
        }
        else if (select == '5')
        { // 5�� : �л����� ���� �� �������� ���
            printf("�������� %.2lf �Դϴ�.\n", max_min_grade(1, student_arr, cnt));
        }
        else if (select == '6')
        { // 6�� : ������ ���� �� ����� ���
            printf("������ ������ %.2lf, ����� %.2lf �Դϴ�.\n", sum_grade(student_arr, cnt), sum_grade(student_arr, cnt) / (double)cnt);
        }
        else if (select == '7')
        { // 7�� : ���� �� �ο��� ���
            printf("���� �� �ο��� %d�� �Դϴ�.\n", cnt);
            print_student(student_arr, cnt);
        }
        else // �ش���� ���� ��� ���α׷� ����
            break;
    }

    return 0;
}
