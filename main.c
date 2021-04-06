#include <stdio.h>
#define MAX_LINE_LENGTH 100
int main(int argc, char* argv[])
{
	FILE* Input;
	fopen_s(&Input, argv[1], "r");
	FILE* Output;
	fopen_s(&Output,argv[2], "w");
	char* instruction[65537];
	while (fgets(instruction, MAX_LINE_LENGTH, Input))
	{

	}

	int a = 10;

	

	

	return 0;

}