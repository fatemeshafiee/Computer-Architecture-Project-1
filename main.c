#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 100

//16 رجیستر داریم
// مقدار رجیستر اول همیشه صفر است.
// رجیسترها سی و دو بیتی هستند
//فعلا نمیدونم بهتره استرینگ باشن یا اینت باشن پس از هردو تعریفشون میکنم.

// char* char_Register[16]; 
//فکر میکنم این نوع نوشتن درست نیست چون ما برای هر رجیستر 32 بیت میخوایم

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
int search_on_Map_lable(struct MAP_lable* symbol_Table , int symbol_Table_size, char * lable)
{
	for (int i = 0; i < symbol_Table_size; i++)
	{
		if (symbol_Table[i].lable == lable)
		{
			return symbol_Table[i].address;
		}

	}
	return -1;
}

//طبق داک، این کار رو تو اسکن اول داریم انجام میدیم
void first_scan(struct MAP_lable* symbol_Table , char ** instruction , 
	int symbol_Table_Size ,int instruction_counter)
{
	for (int i = 0; i < instruction_counter; i++)
	{
		if (instruction[i][0] != " ")
		{
			int j;
			for ( j = 0; instruction[i][j] != " "; j++);
			char newlable[10] = { 0 };
			srtncpy(newlable, instruction[i], j);
			if (search_on_Map_lable(symbol_Table, symbol_Table_Size, newlable)!=(-1))
			{
				exit(1);
			}
			else 
			{
				symbol_Table[symbol_Table_Size].lable = newlable;
				symbol_Table[symbol_Table_Size].address = i;
				symbol_Table_Size++;

			}
			
			
		}
	}
	return;
}
void What_kind(char ** instruction, int instruction_counter)
{
	for (int i = 0; i < instruction_counter; i++)
	{
		int j;
		char instruct [5];
		int instruct_size = 0;
		for (j = 0; instruction[i][j] != " "; j++); // اگر لیبلی وجود داره، ردش میکنیم
		while (instruction[i][j] == " ")	
		{
			//  تا رسیدن به اولین اینستراکشن، اسپیس ها رو هم رد میکنیم
			j++;
		}
		while (instruction[i][j] != " ")
		{
			instruct[instruct_size] = instruction[i][j];
			instruct_size++;
			j++;
		} 
		//  اینجا، اون قسمت اینستراکشن رو توی اینستراکت ریختیم

	}
}

int main(int argc, char* argv[])
{
	FILE* Input;
	fopen_s(&Input, argv[1], "r");
	FILE* Output;
	fopen_s(&Output,argv[2], "w");
	char* instruction[65537] = {0};
	int instruction_counter = 0;
	while (fgets(instruction[instruction_counter], MAX_LINE_LENGTH, Input))
	{
		instruction[instruction_counter][strlen(instruction_counter) - 1] = '\0';
		instruction_counter++;
	}

	struct MAP_lable* symbol_Table = (struct MAP_lable*)malloc(instruction_counter * sizeof(struct MAP_lable));
	int symbol_Table_Size = 0;
	
	first_scan(Input, symbol_Table, instruction, symbol_Table_Size);


	return 0;

}