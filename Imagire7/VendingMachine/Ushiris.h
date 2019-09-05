#pragma once

/* 汎用性が高めのものはこっちにまとめます。 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <string>
#include <stdarg.h>
#include <conio.h>
#include <thread>

void clear_buff(void);
char command_set(char *comms, int comm_num);
void print_center(char *string, char *window_mode, int print_sleep_time, int char_sleep_time, ...);
char window_size(char *window);

void clear_buff(void)
{
	while (_kbhit())
	{
		_getch();
	}
}

void MySleep(int ms)
{
	double x;
	for (x = 0; x < ms; x += 0.05)
	{
		if (_kbhit())
		{
			clear_buff();
			ms = ms;
		}
	}
}

char command_set(const char *comms, int comm_num)
{
	int i;
	char comm, check = 0;

	while (1)
	{
		clear_buff();
		comm = _getch();
		for (i = 0; i < comm_num + 1; i++)
		{
			if (comms[i] == comm)
			{
				check = 1;
				break;
			}
		}
		if (check)
		{
			break;
		}
		else {
			printf("\aERROR:It isn't command.\n");
		}
	}

	return comm;
}

void print_center(const char *string, char *window_mode, int print_sleep_time, int char_sleep_time, ...)
{

	int i = 0, j = 0, k = 0, l = 0, string_long[20] = { 0, }, string_height = 0;
	char va_ch[10], va_st[10][20] = { "\0","\0" }, va_in_trans[10][6] = { {'\0'},{'\0'} };
	int va_in[10];
	va_list list;

	va_start(list, char_sleep_time);

	//count string
	while (string[k] != '\0')
	{
		while (string[k] != '\n'&& string[k] != '\0')
		{
			int count = 0;
			if (string[k] == '%')
			{
				if (string[k + 1] == 'd')
				{
					va_in[i] = va_arg(list, int);

					//translate int->char
					int pointer = 0;
					if (va_in[i] >= 10000)
					{
						va_in_trans[i][pointer] = '0' + va_in[i] / 10000;
						string_long[string_height]++;
						pointer++;
					}

					if (va_in[i] >= 1000)
					{
						va_in_trans[i][pointer] = '0' + (va_in[i] / 1000 - (va_in[i] / 10000) * 10);
						string_long[string_height]++;
						pointer++;
					}

					if (va_in[i] >= 100)
					{
						va_in_trans[i][pointer] = '0' + (va_in[i] / 100 - (va_in[i] / 1000) * 10);
						string_long[string_height]++;
						pointer++;
					}

					if (va_in[i] >= 10)
					{
						va_in_trans[i][pointer] = '0' + (va_in[i] / 10 - (va_in[i] / 100) * 10);
						string_long[string_height]++;
						pointer++;
					}

					va_in_trans[i][pointer] = '0' + (va_in[i] - (va_in[i] / 10) * 10);
					i++;
				}
				else if (string[k + 1] == 'c')
				{
					va_ch[j] = va_arg(list, char);
					j++;
				}
				else if (string[k + 1] == 's')
				{
					strcpy_s(va_st[l], 20, va_arg(list, char*));
					for (count = 0; va_st[l][count] != '\0'; count++)
					{
						string_long[string_height]++;
					}
					l++;
				}
			}
			string_long[string_height]++;
			k++;
		}

		if (string[k] == '\0')
		{
			break;
		}
		else
		{
			string_long[string_height]++;
			k++;
			string_height++;
		}
	}

	char window = window_size(&*window_mode);

	//print string
	system("cls");
	int int_ptr = 0, char_ptr = 0, str_ptr = 0;
	k = 0;
	for (i = 0; i < 12 - string_height / 2; i++)
	{
		printf("\n");
	}
	for (j = 0; j <= string_height; j++)
	{
		for (i = 0; i < window - string_long[j] / 2; i++)
		{
			printf(" ");
		}
		for (i = 0; i < string_long[j]; i++)
		{
			int count = 0;
			MySleep(char_sleep_time);
			if (_kbhit())
			{
				_getch();
				char_sleep_time = 0;
			}
			if (string[k] == '%') {
				switch (string[k + 1])
				{
				case 'd':
					while (va_in_trans[int_ptr][count] != '\0')
					{
						printf("%c", va_in_trans[int_ptr][count]);
						count++;
						i++;
						if (_kbhit())
						{
							clear_buff();
							char_sleep_time = 0;
						}
						MySleep(char_sleep_time);
					}
					int_ptr++;
					break;

				case 'c':
					printf("%c", va_ch[char_ptr]);
					char_ptr++;
					break;

				case 's':
					while (va_st[str_ptr][count] != '\0')
					{
						printf("%c", va_st[str_ptr][count]);
						count++;
						i++;
						if (_kbhit())
						{
							clear_buff();
							char_sleep_time = 0;
						}
						MySleep(char_sleep_time);
					}
					str_ptr++;
					break;

				default:
					printf("%c", string[k]);
					break;
				}
				k++;
				i++;
			}
			else
			{
				printf("%c", string[k]);
			}

			k++;
		}
	}
	MySleep(print_sleep_time);

	va_end(list);
	system("cls");
}

char window_size(char *window)
{
	if (*window == 'n')
	{
		return 39;
	}
	else if (*window == 'w')
	{
		return 55;
	}
	printf("Window size...\n[N]...Nomal  [W]...Wide\n");
	printf("もし、この文章がウィンドウの右端で折り返されているなら、Nを選択することをおすすめします。");
	*window = command_set("nw", 2);
	if (*window == 'n')
	{
		return 39;
	}
	else
	{
		return 55;
	}
	return 0;
}
