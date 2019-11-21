#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

typedef struct table
{
	char label[10];
	char opcode[10];
	char operand[20];
} table;

int search_opcode(table _table[], int size);
int search_operand(table _table[], int size);

int main(int argc, char* argv[])
{

	if (argc == 2)
	{
		FILE* fp_input, * fp_output;
		table list[100];
		int i = 0, j = 0, k = 0, order;
		char c;

		if ((fp_input = fopen(argv[1], "r")) == NULL)
		{
			printf("파일 불러오기 오류\n");
			return 0;
		}
		while (1)
		{
			c = fgetc(fp_input);
			if (c == '\n')
				c = fgetc(fp_input);
			if (c != ' ')
			{
				fseek(fp_input, -1, SEEK_CUR);

				fscanf(fp_input, "%s", list[i].label);
				i++;

				fscanf(fp_input, "%s", list[j].opcode);
				if (!search_opcode(list, j))
					j++;

				fscanf(fp_input, "%s", list[k].operand);
				if (!strcmp(list[k].operand, list[1].label))
					break;
				if (!search_operand(list, k))
					k++;
			}
			else
			{
				fseek(fp_input, 8, SEEK_CUR);
				fscanf(fp_input, "%s", list[j].opcode);
				if (!search_opcode(list, j))
					j++;
				if (!strcmp(list[j].opcode, "rsub"))
					continue;
				fscanf(fp_input, "%s", list[k].operand);

				if (!search_operand(list, k))
					k++;
			}
		}

	
		if ((fp_output = fopen(argv[2], "w")) == NULL)
		{
			printf("파일 불러오기 오류\n");
			return 0;
		}
		fprintf(fp_output, "======label======\n");

		for (order = 0; order < i; order++)
		{
			fprintf(fp_output, "%s\n", list[order].label);
		}
		fprintf(fp_output, "======opcode======\n");
		for (order = 0; order < j; order++)
		{
			fprintf(fp_output, "%s\n", list[order].opcode);
		}
		fprintf(fp_output, "======operand======\n");
		for (order = 0; order < k; order++)
		{
			fprintf(fp_output, "%s\n", list[order].operand);
		}
		fclose(fp_input);
		fclose(fp_output);
	}
	else
		printf("Segmentation Fault\n");
	return 0;

}


int search_opcode(table _table[], int size)
{

	for (int i = 0; i < size; i++)
	{
		if (!strcmp(_table[size].opcode, _table[i].opcode))
		{
			return 1;
		}
	}
	return 0;
}


int search_operand(table _table[], int size)
{

	for (int i = 0; i < size; i++)
	{
		if (!strcmp(_table[size].operand, _table[i].operand))
		{
			return 1;
		}
	}
	return 0;
}
