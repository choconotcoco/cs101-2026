#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_GROUPS 5
#define NUMBERS_PER_GROUP 7
#define MAX_NUMBER 69

void sort_numbers(int numbers[], int count)
{
    int i, j, temp;

    for (i = 0; i < count - 1; i++) {
        for (j = i + 1; j < count; j++) {
            if (numbers[i] > numbers[j]) {
                temp = numbers[i];
                numbers[i] = numbers[j];
                numbers[j] = temp;
            }
        }
    }
}

int main(void)
{
    int n;
    int i, j, number;
    int numbers[NUMBERS_PER_GROUP];
    int used[MAX_NUMBER + 1];
    FILE *file;
    time_t current_time;
    struct tm *time_info;
    char date_string[64];

    srand((unsigned int)time(NULL));

    printf("歡迎光臨長庚樂透彩購買機台\n");
    printf("請問您要買幾組樂透彩 (1 <= n <= 5)：");

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_GROUPS) {
        printf("輸入錯誤，組數必須介於 1 到 5。\n");
        return 1;
    }

    file = fopen("lotto.txt", "w");
    if (file == NULL) {
        printf("無法建立 lotto.txt。\n");
        return 1;
    }

    current_time = time(NULL);
    time_info = localtime(&current_time);
    strftime(date_string, sizeof(date_string),
             "%a %b %d %H:%M:%S %Y", time_info);

    fprintf(file, "========== lotto649 ==========\n");
    fprintf(file, "= %s =\n", date_string);

    for (i = 0; i < n; i++) {
        for (j = 0; j <= MAX_NUMBER; j++) {
            used[j] = 0;
        }

        for (j = 0; j < 6; j++) {
            do {
                number = rand() % MAX_NUMBER + 1;
            } while (used[number]);

            used[number] = 1;
            numbers[j] = number;
        }

        do {
            number = rand() % MAX_NUMBER + 1;
        } while (used[number]);

        numbers[6] = number;

        sort_numbers(numbers, 6);

        fprintf(file, "[%d]:", i + 1);

        for (j = 0; j < 6; j++) {
            fprintf(file, " %02d", numbers[j]);
        }

        fprintf(file, " %02d\n", numbers[6]);
    }

    fprintf(file, "========== csie@CGU ==========\n");
    fclose(file);

    printf("已將 %d 組樂透號碼輸出至 lotto.txt\n", n);

    return 0;
}
