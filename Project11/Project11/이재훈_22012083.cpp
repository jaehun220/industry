#define SIZE 10000
#define NUM_STACKS 10
#define MAXVAL 1024

extern void my_push(int s);
extern int my_pop(int s);
extern void enqueue(void);

void test_main(void)
{
    int count[NUM_STACKS] = {0};
    int current = 1;

    for (int i = 0; i < SIZE; i++) 
    {
        int val = my_pop(0);
        if (val == 0) 
        {
            enqueue();
        }
        else 
        {
            int sid = (val * (NUM_STACKS - 1)) / (MAXVAL + 1) + 1;
            my_push(sid);
            count[sid]++;
        }
    }
    for (int sid = 1; sid < NUM_STACKS; sid++) 
    {
        int low = (sid - 1) * (MAXVAL + 1) / (NUM_STACKS - 1);
        int high = (sid * (MAXVAL + 1) / (NUM_STACKS - 1)) - 1;

        while (current < MAXVAL)
        {
            if (current < low || current > high)
                break;
            int found = 0;
            for (int phase = 0; phase < 2; phase++) 
            {
                int from = (phase == 0) ? sid : 0;
                int limit = count[from];
                int temp_count = 0;
                for (int j = 0; j < limit; j++) 
                {
                    int val = my_pop(from);
                    count[from]--;
                    if (val == current) 
                    {
                        enqueue();
                        found = 1;
                        break;
                    }
                    else 
                    {
                        my_push(0);
                        count[0]++;
                        temp_count++;
                    }
                }
                for (int r = 0; r < temp_count; r++)
                {
                    int temp = my_pop(0);
                    count[0]--;
                    my_push(from);
                    count[from]++;
                }
                if (found) break;
            }
            current++;
        }
    }
}
