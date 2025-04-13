extern void my_push(int s);
extern int my_pop(int s);
extern void enqueue(void);

// ������ �������� ������ ������ ��Ҹ� �����Ͽ� ť�� �ִ� �Լ�
void sort_stack_to_queue(int from_stack, int range_start, int range_end) {
    for (int num = range_start; num <= range_end; num++) {
        while (1) {
            int val = my_pop(from_stack);
            if (val == -1) break;

            if (val == num) {
                enqueue();
            }
            else {
                my_push(0); // �ӽ� ���ÿ� ����
            }
        }

        // �ӽ� ����(0)�� �ִ� ��Ҹ� �ٽ� ���� �������� ����
        while (1) {
            int val = my_pop(0);
            if (val == -1) break;
            my_push(from_stack);
        }
    }
}
void test_main(void) {
    // 1�ܰ�: bucket ����
    while (1) {
        int val = my_pop(0);
        if (val == -1) break;

        int bucket = val / 128; // 0~1023 �� 8�� bucket (0~7), �������� bucket 8
        if (bucket > 7) bucket = 8;
        my_push(bucket + 1); // stack[1]~[9] ���
    }

    // 2�ܰ�: �� bucket ������ �� �����ؼ� queue�� �̵�
    for (int b = 1; b <= 9; b++) {
        for (int target = (b - 1) * 128; target < b * 128 && target <= 1023; target++) {
            while (1) {
                int val = my_pop(b);
                if (val == -1) break;

                if (val == target) {
                    enqueue();
                }
                else {
                    my_push(0); // �ӽ÷�
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

