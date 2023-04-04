#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int readVolume()
{
	char ch[5] = {}; 
	FILE *cmd;
	cmd = popen("amixer get Master | grep -Eo '[0-9]{1,3}%'" , "r");
	fgets(ch , 4 , cmd);
	fclose(cmd);
	int res = 0;
	for(int i = 0 ; i < 5 ; i++)
	{
		if (ch[i] == '%')
		{
			ch[i] = '\0';
			break;
		}
	}

	res = atoi(ch);
	return res;
}


int main(int argc , char **argv)
{
	int nowvolume = 0;
	int change = 0;
	nowvolume = readVolume();
	if (argc == 3)
	{
		if (strcmp(argv[1] , "-") == 0)
		{
			change = -1 * atoi(argv[2]);
		}
		else if (strcmp(argv[1] , "+") == 0)
		{
			change = 1 * atoi(argv[2]);
		}

		nowvolume += change;
		if (nowvolume < 0)
		{
			nowvolume = 0;
		}
		else if (nowvolume > 100)
		{
			nowvolume = 100;
		}
		char cmd[50] = {};
		sprintf(cmd , "amixer set -c 0 Master %d%%" , nowvolume);
		system(cmd);
	}
	else if (argc == 1)
	{
		printf("%d\n" , nowvolume);
	}
	else if (argc == 2)
	{
		if (strcmp(argv[1],"-slstatus") == 0)
		{
			switch(nowvolume / 33)
			{
				case 0:
					if (nowvolume != 0)
					{printf(" ");}
					else{printf("󰝟 ");}
					break;
				case 1:
					printf("󰕾 ");
					break;
				case 3:
				case 2:
					printf(" ");
					break;
				default:
					break;
			}
		}
	}

		printf("%3d" , nowvolume);
	return 0;
}
