#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#define SIZE 10000

void test_main(void);

static int stack[10][SIZE];

static int sp[10];

static int queue[SIZE];

static int qs;

static int hold;

static long long SCORE = 0;

void my_push(int s)
 {
   SCORE++;
    stack[s][sp[s]++] = hold;
}

int my_pop(int s)
{
    SCORE++;
    return hold = stack[s][--sp[s]];
}

void enqueue(void)
{
    queue[qs++] = hold;
    hold = -1;
}

static void build_data(void)
{
    for (int c = 0; c < SIZE; c++)
    {
        stack[0][c] = rand() % 1024;
    }
    sp[0] = SIZE;
    for (int c = 1; c < 10; c++) sp[c] = 0;
    qs = 0;
}
// 큐 출력 함수
void print_queue(void)
{
    for (int i = 0; i < qs; i++) {
        printf("%d ", queue[i]);
        if ((i + 1) % 20 == 0) printf("\n"); // 20개마다 줄바꿈 (가독성)
    }
    printf("\n");
}

int main(void)
{
    SCORE = 0;
    srand(1); // 랜덤 시드 고정
    for (int c = 0; c < 10; c++) {
        build_data();
        test_main();
    }
    printf("SCORE = %lld\n", SCORE);

    // ⭐ 큐 출력 추가
    print_queue(); 
}
