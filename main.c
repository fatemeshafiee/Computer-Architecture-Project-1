#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 100

//16 رجیستر داریم
// مقدار رجیستر اول همیشه صفر است.
// رجیسترها سی و دو بیتی هستند
//فعلا نمیدونم بهتره استرینگ باشن یا اینت باشن پس از هردو تعریفشون میکنم.

char* char_Register[16];
unsigned long int int_Register[16];

//یک سری برچسب داریم که باید سری اول، تشخیص بدیمشون
// بعد بریزیمشون تو
// symbol table
// به همراه آدرسشون
struct MAP_lable
{
	char* lable;
	int address;
};


symbol_Table = (struct MAP_lable*)malloc();

//طبق داک، این کار رو تو اسکن اول داریم انجام میدیم
void first_scan(FILE* filePointer)
{

}

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

	return 0;

}