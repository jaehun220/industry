extern void my_push(int s);
extern int my_pop(int s);
extern void enqueue(void);

// 정해진 범위에서 지정된 스택의 요소를 정렬하여 큐에 넣는 함수
void sort_stack_to_queue(int from_stack, int range_start, int range_end) {
    for (int num = range_start; num <= range_end; num++) {
        while (1) {
            int val = my_pop(from_stack);
            if (val == -1) break;

            if (val == num) {
                enqueue();
            }
            else {
                my_push(0); // 임시 스택에 보관
            }
        }

        // 임시 스택(0)에 있는 요소를 다시 원래 스택으로 복원
        while (1) {
            int val = my_pop(0);
            if (val == -1) break;
            my_push(from_stack);
        }
    }
}
void test_main(void) {
    // 1단계: bucket 정렬
    while (1) {
        int val = my_pop(0);
        if (val == -1) break;

        int bucket = val / 128; // 0~1023 → 8개 bucket (0~7), 나머지는 bucket 8
        if (bucket > 7) bucket = 8;
        my_push(bucket + 1); // stack[1]~[9] 사용
    }

    // 2단계: 각 bucket 내에서 값 정렬해서 queue로 이동
    for (int b = 1; b <= 9; b++) {
        for (int target = (b - 1) * 128; target < b * 128 && target <= 1023; target++) {
            while (1) {
                int val = my_pop(b);
                if (val == -1) break;

                if (val == target) {
                    enqueue();
                }
                else {
                    my_push(0); // 임시로
                }
            }

            while (1) {
                int val = my_pop(0);
                if (val == -1) break;
                my_push(b);
            }
        }
    }
}

