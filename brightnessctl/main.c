#include <curses.h>
#include "config.h"
#include <string.h>
#include <stdio.h>
#include <math.h>

int readMaxBrightness();
void writeBrightness(double , int);
int readBrightness();


int main(int argc , char **argv)
{
	if (argc != 1)
	{
		int res = 0;
		if (strcmp(argv[1] , "-value") == 0)
		{
			res = readBrightness()*100 / readMaxBrightness();
		}
		printf("%d\n" , res);
		return res;
	}
	
	initscr();
	noecho();
	curs_set(0);
	cbreak();
	keypad(stdscr , true);
	WINDOW *win;
	int xMax , yMax;
	getmaxyx(stdscr , yMax , xMax);
	win = newwin(yMax , xMax , 0 , 0);
	box(win , 0 , 0);
	refresh();
	wrefresh(win);
	keypad(win , true);

	int maxlight = readMaxBrightness();
	int nowlight = readBrightness();
	double perc = ((double)nowlight) / ((double)maxlight);
	mvwprintw(win , 1 , (xMax / 2) - (strlen("MaxLight:%5d , Now:%5d , percentage:%3.lf%%")/2) , "MaxLight:%5d , Now:%5d , percentage:%3.lf%%" , maxlight , nowlight , perc*100);
	wrefresh(win);

	int c;
	while((c = getch()) != 'q')
	{
		switch (c)
		{
			case KEY_UP:
				perc = perc + 0.05;
				break;
			case KEY_DOWN:
				perc = perc - 0.05;
				break;
			default:
				break;
		}
		if (perc < 0.001)
		{ perc = 0.000; }
		else if (perc > 1)
		{ perc = 1;}
		if (c == KEY_UP || c == KEY_DOWN)
		{
			writeBrightness(perc , maxlight);
		}
		
		maxlight = readMaxBrightness();
		nowlight = readBrightness();
		mvwprintw(win , 1 , (xMax / 2) - (strlen("MaxLight:%5d , Now:%5d , percentage:%3.lf%%")/2) , "MaxLight:%5d , Now:%5d , percentage:%3.lf%%" , maxlight , nowlight , perc*100);
		wrefresh(win);

	}
	
	endwin();

	return 0;
}

// read max birghtness
int readMaxBrightness()
{
	FILE *fp;
	char file_path[100] = {};
	strcpy(file_path , BrightnessPath);
	strcat(file_path , "max_brightness");
	fp = fopen(file_path , "r");
	int maxlight = 0;
	fscanf(fp , "%d" , &maxlight);
	fclose(fp);
	return maxlight;
}

int readBrightness()
{

	FILE *fp;
	char file_path[100] = {};
	strcpy(file_path , BrightnessPath);
	strcat(file_path , "brightness");
	fp = fopen(file_path , "r");
	int light = 0;
	fscanf(fp , "%d" , &light);
	fclose(fp);
	return light;
}


// change brightness by wiriting string into brightnessfile
void writeBrightness(double perc , int max)
{
	int now = perc * max;
	char cmd[100] = {};
	sprintf(cmd , "echo %d > %s%s" , now , BrightnessPath , "brightness");
	system(cmd);
}
