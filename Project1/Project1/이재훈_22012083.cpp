//#include <stdio.h>
//#include <math.h>
#define ABS(x) ((x < 0) ? -(x) : (x))

void get_school_position(int school_index, int* posX, int* posY);
void get_student_position(int student_index, int* posX, int* posY);
void set_student_school(int student_index, int school_index);

struct student_info {
    int index;
    int posX;
    int posY;
    int distance[3];
    int order_distance[3];
    int dist_diff;
    int assigned_school;
};

struct school_info {
    int index;
    int posX;
    int posY;
    int assigned_count;
};

int get_distance(int x1, int x2, int y1, int y2) {
    int dx = ABS(x2 - x1);
    int dy = ABS(y2 - y1);
    return dx * dx + dy * dy;
}

void set_school_info(struct school_info* sch_info, int index, int x, int y) {
    sch_info->index = index;
    sch_info->posX = x;
    sch_info->posY = y;
    sch_info->assigned_count = 0;
}

void set_student_info(struct student_info* std_info, int index, int x, int y) {
    std_info->index = index;
    std_info->posX = x;
    std_info->posY = y;
    std_info->assigned_school = -1;
    std_info->dist_diff = 0;
}

void sort_distances(struct student_info* s) {
    for (int i = 0; i < 3; i++) {
        s->order_distance[i] = i;
    }
    for (int i = 0; i < 2; i++) {
        int idx = i;
        for (int j = i + 1; j < 3; j++) {
            if (s->distance[j] < s->distance[idx]) {
                idx = j;
            }
        }
        if (idx != i) {
            int tmp = s->distance[i];
            s->distance[i] = s->distance[idx];
            s->distance[idx] = tmp;

            int tmp2 = s->order_distance[i];
            s->order_distance[i] = s->order_distance[idx];
            s->order_distance[idx] = tmp2;
        }
    }
    s->dist_diff = s->distance[1] - s->distance[0];
}

void get_priority(struct student_info std_info[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (std_info[i].dist_diff < std_info[j].dist_diff) {
                struct student_info temp = std_info[i];
                std_info[i] = std_info[j];
                std_info[j] = temp;
            }
        }
    }
}

void run_contest(void) {
    struct student_info std_info[10000];
    struct school_info sch_info[3];
    //long long total_distance = 0;

    for (int i = 0; i < 3; i++) {
        int posX, posY;
        get_school_position(i, &posX, &posY);
        set_school_info(&sch_info[i], i, posX, posY);
    }

    for (int i = 0; i < 10000; i++) {
        int posX, posY;
        get_student_position(i, &posX, &posY);
        set_student_info(&std_info[i], i, posX, posY);

        int std_x = std_info[i].posX;
        int std_y = std_info[i].posY;
        for (int j = 0; j < 3; j++) {
            int sch_x = sch_info[j].posX;
            int sch_y = sch_info[j].posY;
            std_info[i].distance[j] = get_distance(std_x, sch_x, std_y, sch_y);
        }

        sort_distances(&std_info[i]);
    }

    get_priority(std_info, 10000);

    for (int i = 0; i < 10000; i++) {
        for (int k = 0; k < 3; k++) {
            int preferred_school = std_info[i].order_distance[k];
            if (sch_info[preferred_school].assigned_count < 3500) {
                set_student_school(std_info[i].index, preferred_school);
                sch_info[preferred_school].assigned_count++;
                std_info[i].assigned_school = preferred_school;

                //total_distance += std_info[i].distance[k];
                break;
            }
        }
    }
    //printf("Æò±Õ °Å¸®: %.2f\n", (double)sqrt(total_distance / 10000));
}
