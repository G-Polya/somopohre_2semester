#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#define  random_range (32758);

char* SubString(char* input, int begin, int end)
{
	char* substring = (char*)malloc(sizeof(char) * (end - begin + 2));
	strncpy(substring, input + begin, end - begin + 1);
	substring[end - begin + 1] = 0;
	return substring;
}

void get_capacity(char* input)
{
	printf("memory storage capacity: %s", SubString(input, 15, 19));
}

int main(int argc, char* argv[])
{
	srand(time(NULL));
	char buffer[255];
	int len = 0;
	int count = 0;
	int location_count = 0;
	int T_count = 0;
	int* locations = (int*)malloc(sizeof(int) * location_count);
	//FILE* objfile = fopen(argv[1], "r");
	FILE* objfile = fopen("source.obj", "r");
	
	while (1)
	{

		fgets(buffer, sizeof(buffer), objfile);
		if (buffer[0] == 'T')
		{
			char* line_length = SubString(buffer, 7, 8);
			count += strtol(line_length, NULL, 16);
			T_count++;
		}
		else if (buffer[0] == 'M')
		{
			char* location = SubString(buffer, 1, 6); // relocation이 일어나야하는 위치
			locations[location_count] = strtol(location,NULL,16);
			printf("%x\n", locations[location_count]);

			location_count++;
		}
		
		len = strlen(buffer);

		if (len == 0)
			break;
		
		buffer[0] = '\0';
	}

	fseek(objfile, 0, SEEK_SET);

	fgets(buffer, sizeof(buffer), objfile);

	get_capacity(buffer);

	int start_addr = (int)rand() % random_range;
	start_addr = 2260;
	printf("memory start address : %d\n", start_addr);
	int end_addr = start_addr + count - 1;
	printf("memory last address : %d\n", end_addr);

	

	// address  instruction
	int address = start_addr; // 초기화

	FILE* after_relocation = fopen("after.txt", "w");

	int all_length = 0;	

	char** lines = (char**)malloc(sizeof(char*) * T_count);
	char** temps = (char**)malloc(sizeof(char*) * T_count);
	int* temps_length = (int*)malloc(sizeof(int) * T_count);
	for (int i = 0; i < T_count; i++)
	{
		lines[i] = fgets(buffer, sizeof(buffer), objfile);
		int line_length = strlen(lines[i]) - 2;
		char* temp = SubString(lines[i], 9, line_length);
		temps_length[i] = strlen(temp);
		temps[i] = temp;
		all_length += temps_length[i];

	}
	
	all_length -= 1;

	printf("%d\n", all_length);
	char* all_instruction = (char*)malloc(sizeof(char));
	all_instruction = SubString(all_instruction, 5, all_length);
	all_instruction[0] = 0;
	for (int i = 0; i < T_count; i++)
	{
		strcat(all_instruction, temps[i]);
	}

	
	printf("%s %c\n\n", all_instruction,all_instruction[all_length]);
	
	
	/*for (int i = 0; i < all_length; i*=6)
	{
		char* instruction = SubString(all_instruction, 0, 5);

		if (i == locations[i])
			_itoa(strtol(SubString(all_instruction, 0, 6), NULL, 16) + start_addr,instruction,5);
		printf("%d %s\n", address, instruction);
		all_instruction = SubString(all_instruction, 6, all_length);
		all_length = strlen(all_instruction) ;
		address += 6;
	}*/

	
		for (int i = 0; i < all_length; i++)
		{
			char* instruction = SubString(all_instruction, 0, 5);
			
		/*	for (int j = 0; j < location_count; j++)
			{	
				if (i == locations[j])
				{
					

					printf("%d", i);
					
				}
				else if (i - 1 == locations[j])
				{
					
					printf("%d", i);
				}
				else if (i - 2 == locations[j])
				{
					;

					printf("%d", i);
				}
			}
		*/

			printf("%d %s\n", address, instruction);
			all_instruction = SubString(all_instruction, 6, all_length);
			all_length = strlen(all_instruction);
			address += 6;
		}
	
	
	/*int location_temp = 1 + 6 + 2 + locations[0];
	fseek(objfile, 0, SEEK_SET);
	fgets(buffer, sizeof(buffer), objfile);
	fseek(objfile, location_temp, SEEK_CUR);
	char* temp_ = fgets(buffer, sizeof(buffer), objfile);
	*/
	free(lines);
	free(temps);
	return 0;
}
