#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LINE_LENGTH 100

//16 رجیستر داریم
// مقدار رجیستر اول همیشه صفر است.
// رجیسترها سی و دو بیتی هستند
//فعلا نمیدونم بهتره استرینگ باشن یا اینت باشن پس از هردو تعریفشون میکنم.

// char* char_Register[16]; 
//فکر میکنم این نوع نوشتن درست نیست چون ما برای هر رجیستر 32 بیت میخوایم

unsigned long int val_Register[16];


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

//function to transfer binary to int
char * Decimal_To_Binary(int n)
{
	char binary[] = " ", rest;
	int cnt = 0;
	while (n > 0)
	{
		rest = n % 2;
		strcat(binary, rest);
		n /= 2;
		cnt++;
	}
	while (cnt < 4)
	{
		strcat(binary, "0");
		cnt++;
	}
	return strrev(binary);
}
//فعلا برای R_Type
char* connector_R(char* op_code, char* rs, char* rt, char* rd)
{
	char total[] = "";
	int i, j = 0;
	for (i = 31; i > 27; i--)
	{
		strcat(total, '0');
	}
	strcat(total, op_code);
	strcat(total, rs);
	strcat(total, rt);
	strcat(total, rd);
	for (i = 1; i >= 0; i--)
	{
		strcat(total, "0");
	}

	return strrev(total);
}

unsigned long int Binary_To_Decimal(char* number, int size)
{
	unsigned long int n = 0, two = 0;
	for (int i = size -1; i >= 0; i--)
	{
		n += (pow(2, two) * (number[i]-'0'));
		two++;
	}
	return n;
}

//seprate rd, rs, rt
// for R_Type (for now)
unsigned long int seprator_R(char ** instruction, int j, int i, char* op_code, char * instruct)
{
	int rd = 0, rs = 0, rt = 0, tenth = 1, tdd = 0;
	strcat(instruction[i], " ");
	while (instruction[i][j] != " " || instruction[i][j] != '#')
	{
		if (instruction[i][j] == ',')
		{
			tenth = 1;
			tdd++;
		}
		else if (tdd == 0)
		{
			rd += (tenth * (instruction[i][j] - '0'));
		}
		else if (tdd == 1)
		{
			rs += (tenth * (instruction[i][j] - '0'));
		}
		else
		{
			rt += (tenth * (instruction[i][j] - '0'));
		}
		tenth *= 10;
		j++;
	}
	
	// hint : we should update register rd!
	if (strcmp(instruct, "add"))
	{
		val_Register[rd] = val_Register[rs] + val_Register[rt];
	}
	else if (strcmp(instruct, "sub"))
	{
		val_Register[rd] = val_Register[rs] - val_Register[rt];
	}
	else if (strcmp(instruct, "slt"))
	{
		val_Register[rd] = val_Register[rs] < val_Register[rt]; 
	}
	else if (strcmp(instruct, "or"))
	{
		val_Register[rd] = val_Register[rs] | val_Register[rt];
	}
	else if (strcmp(instruct, "nand"))
	{
		val_Register[rd] = ~(val_Register[rs] & val_Register[rt]);
	}
	return Binary_To_Decimal(connector_R(op_code, Decimal_To_Binary(rs),
	Decimal_To_Binary(rt), Decimal_To_Binary(rd)), 32);
}

unsigned long int R_Type(char* instruct, char** instruction, int j, int i)
{
	// instruction $rd, $rs, $rt
	// in machin code : 0000 op-code rs rt rd
	// j is a index of first space after instruct
	while (instruction[i][j] == " ")
		j++;

	unsigned long int final_result;
	if (strcmp(instruct, "add"))
	{
		final_result = seprator_R(instruction, j, i, "0000");
	}
	else if (strcmp(instruct, "sub"))
	{
		final_result = seprator_R(instruction, j, i, "0001");
	}
	else if (strcmp(instruct, "slt"))
	{
		final_result = seprator_R(instruction, j, i, "0010");
	}
	else if (strcmp(instruct, "or"))
	{
		final_result = seprator_R(instruction, j, i, "0011");
	}
	else if (strcmp(instruct, "nand"))
	{
		final_result = seprator_R(instruction, j, i, "0100");
	}
	return final_result;
}

unsigned long int I_Type(char* instruct, char** instruction, int j, int i)
{
	// instruction $rt, $rs, imm
	// machin code : 0000 op_code rs, rt, offset
	while (instruction[i][j] == " ")
		j++;



}

void What_kind(char ** instruction, int instruction_counter)
{
	for (int i = 0; i < instruction_counter; i++)
	{
		int j;
		char instruct []="";
		for (j = 0; instruction[i][j] != " "; j++); // اگر لیبلی وجود داره، ردش میکنیم
		while (instruction[i][j] == " ")	
		{
			//  تا رسیدن به اولین اینستراکشن، اسپیس ها رو هم رد میکنیم
			j++;
		}
		while (instruction[i][j] != " ")
		{
			strcat(instruct, instruction[i][j]);
			
			j++;
		} 
		//  اینجا، اون قسمت اینستراکشن رو توی اینستراکت ریختیم
		// is it true?! //what do you mean?
		// J is now whatever after the instruction. $rd, $rs, %rt
		// so we're gonna send j to the function to use it
		if (strcmp(instruct, "add") || strcmp(instruct, "sub") ||
			strcmp(instruct, "slt") || strcmp(instruct, "or")  ||
			strcmp(instruct, "nand"))
		{
			R_Type(instruct, instruction,  j,  i);
		}
		else if (strcmp(instruct, "addi") || strcmp(instruct, "ori") ||
			     strcmp(instruct, "slti") || strcmp(instruct, "lui") ||
			     strcmp(instruct, "lw")   || strcmp(instruct, "sw")  ||
			     strcmp(instruct, "beq") || strcmp(instruct, "jalr"))
		{
			 
		}
		else
		{

		}

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