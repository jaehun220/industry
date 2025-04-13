#define SIZE 10000
#define NUM_STACKS 10
#define MAXVAL 1024

extern void my_push(int s);
extern int my_pop(int s);
extern void enqueue(void);

void test_main(void)
{
    int i;
    int stack_sizes[NUM_STACKS] = { 0 };

    // 1. stack[0]에서 pop하면서 1~9번 스택에 균등하게 분산
    for (i = 0; i < SIZE; i++) {
        int value = my_pop(0);  // hold에 저장되고, 리턴값 받아옴
        int target_stack = i % (NUM_STACKS - 1) + 1;  // 1~9번 스택 순환 분산

        my_push(target_stack);  // hold에 저장된 값을 target_stack으로 push
        stack_sizes[target_stack]++;
    }

    int remaining = SIZE;

    // 2. 정렬
    while (remaining > 0) {
        int min_value = MAXVAL + 1;
        int min_stack = -1;
        int valid_stack[NUM_STACKS] = { 0 };  // pop했는지 기록

        // 1~9번 스택에서 각각 pop 한번만 하고 비교
        for (i = 1; i < NUM_STACKS; i++) {
            if (stack_sizes[i] == 0)
                continue;

            int value = my_pop(i);  // hold 세팅 + value 리턴
            stack_sizes[i]--;

            valid_stack[i] = 1;  // 이 스택 pop했음

            if (value < min_value) {
                min_value = value;
                min_stack = i;
            }

            // pop한 값을 hold에 가지고 있으므로 즉시 push하거나 enqueue해야 함
            my_push(i);  // 일단 다시 push
            stack_sizes[i]++;
        }

        // 다시 1~9번 스택을 돌면서, 가장 작은 값인 경우만 진짜 pop
        for (i = 1; i < NUM_STACKS; i++) {
            if (!valid_stack[i]) continue;
            if (i != min_stack) continue;

            my_pop(i);   // 다시 pop해서 hold에 정확한 값 세팅
            stack_sizes[i]--;

            enqueue();   // hold를 그대로 큐에 넣기
            remaining--;
            break;
        }
    }
}

