#define ABS(x) ((x < 0) ? -(x) : (x))

void get_school_position(int school_index, int* posX, int* posY);
void get_student_position(int student_index, int* posX, int* posY);
void set_student_school(int student_index, int school_index);

struct student_info
{
	int index;
	int posX;
	int posY;
	int distance[10000][3];
	int dist_diff[2];
};
struct school_info
{
	int index;
	int posX;
	int posY;
};


int get_distance(int x1, int x2, int y1, int y2) 
{
	int dx = ABS(x2 - x1);
	int dy = ABS(y2 - y1);
	return dx * dx + dy * dy;
}

void set_school_info(school_info *sch_info, int index, int x, int y)
{
	sch_info->index = index;
	sch_info->posX = x;
	sch_info->posY = y;
}

void set_student_info(student_info* std_info, int index, int x, int y)
{
	std_info->index = index;
	std_info->posX = x;
	std_info->posY = y;
}

void run_contest(void)
{
	student_info std_info[10000];
	school_info sch_info[3];
	for (int i = 0; i < 3; i++)
	{
		int posX, posY;
		get_school_position(i, &posX, &posY);
		set_school_info(&sch_info[i], i, posX, posY);
	}
	for (int i = 0; i < 10000; i++)
	{
		int posX, posY;
		get_student_position(i, &posX, &posY);
		set_student_info(&std_info[i], i, posX, posY);
	}
	for (int i = 0; i < 10000; i++)
	{
		int std_x = std_info[i].posX;
		int std_y = std_info[i].posY;
		for (int j = 0; j < 3; j++)
		{
			int sch_x = sch_info[j].posX;
			int sch_y = sch_info[j].posY;
			std_info[i].distance[i][j] = get_distance(std_x, sch_x, std_y, sch_y);
		}
	}
}