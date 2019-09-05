#include "Ushiris.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <random>
#include <time.h>
#include <map>
#include <cctype>
#include <sstream>

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

enum Mode
{
	daifugo,
	shogi,
	doble,
	othello,
	buy,
	end,
};

std::map<Mode,string> ModeStr =
{{daifugo,"��x��"},
 {shogi,"����"},
 {doble,"�h�u��"},
 {othello,"�I�Z��"},
 {buy,"�w��"},
 {end,"�I��"}
};

char window;

vector<string> quest_text_reader(string file_name, int lines);
string vending(Mode mode);
void show_sales(int count);
void setup();
int load_sales();
Mode set_mode(unsigned int &count);
void close(int count);
int games(unsigned int &count);
bool check_int(string str);

int main(void)
{
	setup();

	unsigned int count = load_sales();

	while (true)
	{
		show_sales(count);
		Mode mode = set_mode(count);

		if (mode == end)
		{
			break;
		}

		cout << endl << "[ " << ModeStr.at(mode) << " ]" << "10�~�����Ă��������B" << endl;
		cout << "[end]...�A�v���̏I��  [ret]...���i�I���֖߂�" << endl << endl;

		string in;
		cin >> in;

		//string inputs
		if (in == "end")
		{
			break;
		}
		else if (in == "ret")
		{
			system("cls");
			continue;
		}

		//int inputs
		int in_money = std::atoi(in.c_str());
		if (in_money >= 10)
		{
			cout << vending(mode) << endl;
			if (mode == end)
			{
				break;
			}
			if (in_money > 10)
			{
				cout << "�����" << in_money - 10 << "�~�ł��B" << endl;
			}
			count += 10;
		}

		cout << "loading.";
		for (int i = 0; i < 5; i++)
		{
			MySleep(400);
			putchar('.');
		}
		cout << endl;

		clear_buff();

		cout << "0�������ƃ��[�h��I�ԉ�ʂɖ߂�܂�" << endl;
		command_set("0", 1);
		system("cls");
	}

	close(count);

	return 0;
}

vector<string> quest_text_reader(string file_name, int lines)
{
	std::ifstream quests(file_name.c_str());
	vector<string> quest_list;
	for (int i = 0; i < lines; i++)
	{
		char rule[200] = { 0, };
		quests.getline(rule, 200);
		quest_list.push_back(rule);
	}

	return quest_list;
}

string vending(Mode mode)
{
	switch (mode)
	{
	case daifugo:
		return quest_text_reader("rule_daifugo.txt", 15)[rand() % 15];
		break;

	case shogi:
		return quest_text_reader("shogi.txt", 4)[rand() % 4];
		break;

	case doble:
		return quest_text_reader("doble.txt", 4)[rand() % 4];
		break;

	case othello:
		return quest_text_reader("othello.txt", 4)[rand() % 4];
		break;

	case end:
		return "���悤�Ȃ�I";
		break;

	default:
		return "�G���[�F�s���ȃG���[�ivending-switch-default�j";
		break;
	}
}

void show_sales(int count)
{
	cout << "-*-*-*-*-*-*-*������グ��" << count << "�~�ł�*-*-*-*-*-*-*-" << endl;
}

void setup()
{
	srand(time(0));
	string title = "QUEST VENDOR var1.7";
	print_center(title.c_str(), &window, 1500, 200);
}

int load_sales()
{
	std::ifstream sales_in("sales.txt");

	char sales_str[1000];
	sales_in.getline(sales_str, 1000);
	sales_in.close();

	return std::atoi(sales_str);
}

Mode set_mode(unsigned int &count)
{
	while (true)
	{
		system("cls");
		show_sales(count);
		cout << "���[�h��I��ł�������" << endl;
		cout << "[0]...��x��  [1]...����  [2]...�h�u��  [3]...�I�Z��  [4]...�{�[�h�Q�[���̍w��  [9]...�A�v���̏I��" << endl;

		string comms = "012349";
		char mode_in = command_set(comms.c_str(), comms.length());

		switch (mode_in)
		{
		case '0':
			return daifugo;
			break;

		case '1':
			return shogi;
			break;

		case '2':
			return doble;
			break;

		case '3':
			return othello;
			break;

		case '4':
			games(count);
			break;

		case '9':
			return end;
			break;

		default:
			cout << "�G���[�F�������Ȃ����͂ł��B" << endl << "" << endl;
			break;
		}
	}
}

void close(int count)
{
	std::ofstream output("sales.txt");

	output << count;
	output.close();

	system("cls");
	print_center("SEE YOU AGEIN!", &window, 2000, 100);

	exit(0);
}

int games(unsigned int &count)
{

	char game_str[7][200];
	char price_str[7][200];

	while (true)
	{
		std::ifstream price("price.txt");
		system("cls");

		cout << "�{�[�h�Q�[���̑I����ʂł�" << endl;
		for (int i = 0; i < 7; i++)
		{
			price.getline(game_str[i], 200);
			price.getline(price_str[i], 200);

			cout << '[' << i << "]..." << game_str[i] << ':' << price_str[i] << "�~" << endl;
		}
		cout << "[8]...���j���[��ʂɖ߂�" << endl;
		cout << "[9]...�A�v�����I������" << endl;

		//�w��
		string comms = "012345689";
		char comm = command_set(comms.c_str(), comms.length());

		char *price_c;
		char *game_c;
		switch (comm)
		{
		case '0':
			price_c = price_str[0];
			game_c = game_str[0];
			break;

		case '1':
			price_c = price_str[1];
			game_c = game_str[1];
			break;

		case '2':
			price_c = price_str[2];
			game_c = game_str[2];
			break;

		case '3':
			price_c = price_str[3];
			game_c = game_str[3];
			break;

		case '4':
			price_c = price_str[4];
			game_c = game_str[4];
			break;

		case '5':
			price_c = price_str[5];
			game_c = game_str[5];
			break;

		case '6':
			price_c = price_str[6];
			game_c = game_str[6];
			break;

		case '8':
			return 1;
			break;

		case '9':
			close(count);
			break;

		default:
			break;
		}

		while (true)
		{
			system("cls");

			cout << '[' << game_c << "]..." << price_c << "�~�����Ă�������" << endl;
			cout << "[end]...�A�v���̏I��  [ret]...���i�I���֖߂�" << endl;

			string in;
			cin >> in;

			if (in == "end")
			{
				close(count);
			}
			else if (in == "ret")
			{
				break;
			}

			if (!check_int(in))
			{
				continue;
			}

			if (std::atoi(in.c_str()) >= std::atoi(price_c))
			{
				cout << "�w�����������܂���:" << game_c << endl;
				cout << "�����" << std::atoi(in.c_str()) - std::atoi(price_c) << "�~�ł��B" << endl;
				count += std::atoi(price_c);
				MySleep(5000);
			}
			else
			{
				cout << "���z������܂���B" << endl;
				MySleep(5000);
			}
		}

		price.close();
	}
}

bool check_int(string str)
{
	if (std::all_of(str.cbegin(), str.cend(), isdigit))
	{
		return true;
	}
	return false;
}