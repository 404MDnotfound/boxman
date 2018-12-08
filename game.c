#include"function.h"

void init() {

	//�öδ��빦�������ع�꣬������win32��̽ӿڣ�����Ҫ����
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ���ھ��
	CONSOLE_CURSOR_INFO cci;//ʵ�л�һ������̨�����Ϣ��
	GetConsoleCursorInfo(hOut, &cci);//��ȡ�����Ϣ
	cci.bVisible = FALSE;//���ع��
	SetConsoleCursorInfo(hOut, &cci);//���ù����Ϣ

	system("title ������1.0");//�趨��������
	system("mode con cols=120 lines=30");//�趨���ڴ�С
}

void mainloop() {

	//init

	char key = 0;
	int level_choose=1;
	int isEnd = 0;
	int level;
	int scenes = 0;

	//������
	char main_interface[50][50] = {
		"\n\n\n\n\n\n\n",
		"\t\t\t\t\t\t\t ������",
		"\t\t\t\t\t\t   |===============|",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |   ��ʼ(S)     |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |   �˳�(ESC)   |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |===============|",
	};

	//���˵�2
	char menu2[50][50] = {
		"\n\n\n\n\n\n\n\n",
		"\t\t\t\t\t\t\t ������\n",
		"\t\t\t\t\t\t   |===============|",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |   ��ͷ��ʼ(A) |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |    ѡ��(X)    |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |    ����(ESC)  |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |===============|"
	};


	while (1)
	{

		//render
		system("cls");
		switch (scenes)
		{
		case 0:
			for (int i = 0; i < 11; i++)
				puts(main_interface[i]);
			break;
		case 1:
			for (int i = 0; i < 11; i++)
				puts(menu2[i]);
			break;
		case 2:
			//��ӡ�ؿ�ѡ�����
			printf("\n\n\n\n\n\n\n\n\n\n\n");
			printf("\t\t\t\t\t\t");
			printf("��ѡ��ؿ�(1-%d):< %d >\n" , maps_num, level_choose);
			printf("\n");
			printf("\t\t\t\t\t\tA:ǰһ�� D����һ�� �ո��س���ȷ��");
			break;
		case 3:
			level = 0;
			scenes = gameloop(level);
			break;
		case 4:
			scenes = gameloop(level_choose);
			break;
		case 5:
			level++;
			scenes = 4;
			break;
		case 6:
			scenes = 0;
			level = 0;
			break;
		default:
			break;
		}


		//event
		key = getch();

		switch (scenes)
		{
		case 0:
			switch (key)
			{
			case 'S':
			case 's':
				scenes = 1;
				break;
			case 27:

				isEnd = 1;
				break;
			default:
				break;
			}
			break;
		case 1:
			switch (key)
			{
			case 'A':
			case 'a':
				gameloop(level_choose);
				break;
			case 27:
				scenes = 0;
				break;
			case 'x':
			case 'X':
				scenes = 2;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}


		//update
		switch (scenes)
		{
		case 0:

			break;
		case 1:

			break;
		case 2:
			if ((key == 'a' || key == 'A') && level_choose > 1)
				level_choose--;
			else if ((key == 'd' || key == 'D') && level_choose < maps_num)
				level_choose++;
			else if ((key == 'f' || key == 'F') && level_choose > 1)
				level_choose--;
			else if ((key == 13 || key == 32)) {
				key = level_choose - 1;
				level = level_choose - 1;
				scenes = 4;
			}
			else if (key == 27)
				scenes = 1;
			break;
		default:
			break;
		}

		//delay

		//isend
		if (isEnd)
			break;
	}


	//clear

}




int gameloop(int level) {

	//init
	int x = 0;
	int y = 0;

	char key = 0;

	int isEnd = 0;

	int scenes = 0;

	Map *map;
	map = LoadMap(level);
	x = map->x;
	y = map->y;

	while (1)
	{

		//render
		system("cls");
		switch (scenes)
		{
		case 0:
			for (int i = 0; i < map->h; i++)
				puts(map->map[i]);
			break;
		case 1:
			printf("Good Job!\n��N��������һ��");
			break;
		default:
			break;
		}


		//event
		key = getch();

		switch (scenes)
		{
		case 0:
			switch (key)
			{
			case 'W':
			case 'w':
				switch (map->map[y - 1][x])
				{
				case ' ':
				case 'X':
					map->map[y - 1][x] = '@';
					map->map[y][x] = ' ';
					y = y - 1;
					break;
				case 'O':
				case 'Q':
					if (map->map[y - 2][x] != '#'&&map->map[y - 2][x] != 'O'&&map->map[y - 2][x] != 'Q') {
						if (map->map[y - 2][x] == 'X')
							map->map[y - 2][x] = 'Q';
						else
							map->map[y - 2][x] = 'O';
						map->map[y - 1][x] = '@';
						map->map[y][x] = ' ';
						y = y - 1;
					}
					break;
				default:
					break;
				}

				break;
			case 'S':
			case 's':

				switch (map->map[y + 1][x])
				{
				case ' ':
				case 'X':
					map->map[y + 1][x] = '@';
					map->map[y][x] = ' ';
					y = y + 1;
					break;
				case 'O':
				case 'Q':
					if (map->map[y + 2][x] != '#'&&map->map[y + 2][x] != 'O'&&map->map[y + 2][x] != 'Q') {
						if (map->map[y + 2][x] == 'X')
							map->map[y + 2][x] = 'Q';
						else
							map->map[y + 2][x] = 'O';

						map->map[y + 1][x] = '@';
						map->map[y][x] = ' ';
						y = y + 1;
					}
					break;
				default:
					break;
				}

				break;
			case 'A':
			case 'a':
				switch (map->map[y][x - 1])
				{
				case ' ':
				case 'X':
					map->map[y][x - 1] = '@';
					map->map[y][x] = ' ';
					x = x - 1;
					break;
				case 'O':
				case 'Q':
					if (map->map[y][x - 2] != '#'&&map->map[y][x - 2] != 'O'&&map->map[y][x - 2] != 'Q') {
						if (map->map[y][x - 2] == 'X')
							map->map[y][x - 2] = 'Q';
						else
							map->map[y][x - 2] = 'O';
						map->map[y][x - 1] = '@';
						map->map[y][x] = ' ';
						x = x - 1;
					}
					break;
				default:
					break;
				}

				break;
			case 'D':
			case 'd':
				switch (map->map[y][x + 1])
				{
				case ' ':
				case 'X':
					map->map[y][x + 1] = '@';
					map->map[y][x] = ' ';
					x = x + 1;
					break;
				case 'O':
				case 'Q':
					if (map->map[y][x + 2] != '#'&&map->map[y][x + 2] != 'O'&&map->map[y][x + 2] != 'Q') {
						if (map->map[y][x + 2] == 'X')
							map->map[y][x + 2] = 'Q';
						else
							map->map[y][x + 2] = 'O';
						map->map[y][x + 1] = '@';
						map->map[y][x] = ' ';
						x = x + 1;
					}
					break;

				default:
					break;
				}
				break;
			case 'R':
			case'r':
				scenes = 0;
				map = LoadMap(map->level);
				x = map->x;
				y = map->y;

				break;
			case 27:

				isEnd = 1;
				break;
			default:
				break;
			}
			break;
		case 1:
			switch (key)
			{
			case 'R':
			case'r':
				scenes = 0;
				map = LoadMap(map->level);
				x = map->x;
				y = map->y;

				break;
			case 'N':
			case 'n':
				scenes = 0;
				map = LoadMap(map->level + 1);
				x = map->x;
				y = map->y;
				break;

			case 27:
				isEnd = 1;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}


		//update
		int isOver = 1;
		switch (scenes)
		{
		case 0:


			for (int i = 0; i < map->aim_count; i++) {
				if (map->map[map->aimy[i]][map->aimx[i]] != 'Q')
					isOver = 0;
			}
			if (isOver)
				scenes = 1;

			for (int i = 0; i < map->aim_count; i++) {
				if (map->map[map->aimy[i]][map->aimx[i]] == ' ')
					map->map[map->aimy[i]][map->aimx[i]] = 'X';
			}

			break;
		case 1:

			break;
		default:
			break;
		}

		//delay

		//isend
		if (isEnd)
			break;
	}


	//clear



}

Map* LoadMap(int level) {

	Map *temp = (Map*)malloc(sizeof(Map));
	char buffer[256];

	FILE *fp;
	sprintf(buffer, "D://tuixiangzi//data/map/%d.txt", level);
	fp = fopen(buffer, "r");

	temp->level = level;
	temp->aim_count = 0;

	for (int i = 0;; i++) {
		fgets(temp->map[i], 256, fp);

		temp->map[i][strlen(temp->map[i]) - 1] = '\0';

		for (int j = 0; temp->map[i][j] != '\0'; j++) {
			switch (temp->map[i][j]) {
			case '@':
				temp->x = j;
				temp->y = i;
				break;
			case 'X':
			case 'Q':
				temp->aimx[temp->aim_count] = j;
				temp->aimy[temp->aim_count] = i;

				temp->aim_count++;
				break;
			}

		}

		if (temp->map[i][1] == '|') {
			temp->map[i][1] = '=';
			temp->h = i + 1;
			break;
		}
	}

	fclose(fp);
	return temp;
}