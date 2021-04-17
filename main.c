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
int search_on_Map_lable(struct MAP_lable* symbol_Table, int symbol_Table_size, char* lable)
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
void first_scan(struct MAP_lable* symbol_Table, char** instruction,
	int symbol_Table_Size, int instruction_counter)
{
	for (int i = 0; i < instruction_counter; i++)
	{
		if (instruction[i][0] != " ")
		{
			int j;
			for (j = 0; instruction[i][j] != " "; j++);
			//char newlable[10] = { 0 };
			char* newlable = malloc(j * sizeof(char));
			for (int k = 0; k < j; k++)
			{
				newlable[k] = instruction[i][k];
			}
			//srtncpy(newlable, instruction[i], j);
			if (j != 0)
			{
				if (search_on_Map_lable(symbol_Table, symbol_Table_Size, newlable) != (-1))
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
	}
	return;
}

//function to transfer binary to int
char* Decimal_To_Binary(int n, int size)
{
	char binary[] = " ", rest;
	int cnt = 0;
	while (n > 0)
	{
		rest = n % 2;
		strcat_s(binary, strlen(binary), rest);
		n /= 2;
		cnt++;
	}
	while (cnt < size)
	{
		strcat_s(binary, strlen(binary), "0");
		cnt++;
	}
	if (size == 16 && strlen(binary) > 16)
	{
		exit(1);
	}
	//return strrev(binary);
	char* reversed_bin = malloc(strlen(binary) * sizeof(char));

	for (int k = 0; k < strlen(binary); k++)
	{
		reversed_bin[k] = binary[size - k - 1];
	}
	return reversed_bin;


}

unsigned long int Binary_To_Decimal(char* number, int size)
{
	unsigned long int n = 0, two = 0;
	for (int i = size - 1; i >= 0; i--)
	{
		n += (pow(2, two) * (number[i] - '0'));
		two++;
	}
	return n;
}

//فعلا برای R_Type
void connector_R(char* op_code, char* rs, char* rt, char* rd, char * total)
{
	int i, j = 0;
	for (i = 31; i > 27; i--)
	{
		strcat_s(total, strlen(total), '0');
	}
	strcat_s(total, strlen(total), op_code);
	strcat_s(total, strlen(total), rs);
	strcat_s(total, strlen(total), rt);
	strcat_s(total, strlen(total), rd);
	for (i = 11; i >= 0; i--)
	{
		strcat_s(total, strlen(total), "0");
	}
}
unsigned long int seprator_R(char** instruction, int j, int i, char* op_code, char* instruct)
{
	int rd = 0, rs = 0, rt = 0, tenth = 1, tdd = 0;
	strcat_s(instruction[i], strlen(instruction[i]), " ");
	while (instruction[i][j] != " " && instruction[i][j] != '#')
	{
		if (instruction[i][j] == ',')
		{
			tenth = 1;
			tdd++;
		}
		else if (tdd == 0)
		{
			rd = rd * tenth;
			rd += (instruction[i][j] - '0');
		}
		else if (tdd == 1)
		{
			rs = rs * tenth;
			rs += (instruction[i][j] - '0');
		}
		else
		{
			rt = rt * tenth;
			rt += (instruction[i][j] - '0');
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
		val_Register[rd] = ~(val_Register[rs] | val_Register[rt]);
	}
	char* total = "";
	connector_R(op_code, Decimal_To_Binary(rs, 4),
		Decimal_To_Binary(rt, 4), Decimal_To_Binary(rd, 4), total);
	return Binary_To_Decimal(total, 32);
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
		final_result = seprator_R(instruction, j, i, "0000", instruct);
	}
	else if (strcmp(instruct, "sub"))
	{
		final_result = seprator_R(instruction, j, i, "0001", instruct);
	}
	else if (strcmp(instruct, "slt"))
	{
		final_result = seprator_R(instruction, j, i, "0010", instruct);
	}
	else if (strcmp(instruct, "or"))
	{
		final_result = seprator_R(instruction, j, i, "0011", instruct);
	}
	else if (strcmp(instruct, "nand"))
	{
		final_result = seprator_R(instruction, j, i, "0100", instruct);
	}
	return final_result;
}

//  I type
void connector_I(char* op_code, char* rs, char* rt, char* imm, char* total)
{
	int i, j = 0;
	for (i = 31; i > 27; i--)
	{
		strcat_s(total, strlen(total), "0");
	}
	strcat_s(total, strlen(total), op_code);
	strcat_s(total, strlen(total), rs);
	strcat_s(total, strlen(total), rt);
	strcat_s(total, strlen(total), imm);


	return total;
}

unsigned long int seprator_I(char** instruction, int j, int i, char* op_code, char* instruct,
	struct MAP_lable* symbol_Table, int symbol_Table_size)
{

	int rs = 0, rt = 0, INT_imm = 0, tenth = 1, tdd = 0;

	char imm[] = "";
	strcat_s(instruction[i], strlen(instruction[i]), " ");
	if (instruct == "lui")
	{
		while (instruction[i][j] != " " && instruction[i][j] != '#')
		{

			if (instruction[i][j] == ',')
			{
				tenth = 1;
				tdd++;
			}
			else if (tdd == 0)
			{
				rt = rt * tenth;
				rt += (instruction[i][j] - '0');
			}
			else
			{
				strcat_s(imm, strlen(imm), instruction[i][j]);
			}
			tenth *= 10;
			j++;
		}
		if (imm[0] >= '0' && imm[0] <= '9')
		{
			tenth = 1;

			for (int k = 0; k < strlen(imm); k++)
			{
				INT_imm = INT_imm * tenth;

				INT_imm += (imm[k] - '0');
				tenth *= 10;
			}
		}
		else
		{
			INT_imm = search_on_Map_lable(symbol_Table, symbol_Table_size, imm);
			if (INT_imm == -1)
			{
				exit(1);
			}
		}
	}
	else
	{
		while (instruction[i][j] != " " && instruction[i][j] != '#')
		{

			if (instruction[i][j] == ',')
			{
				tenth = 1;
				tdd++;
			}
			else if (tdd == 0)
			{
				rt = rt * tenth;
				rt += (instruction[i][j] - '0');
			}
			else if (tdd == 1)
			{
				rs = rs * tenth;
				rs += (instruction[i][j] - '0');
			}
			else
			{
				strcat_s(imm, strlen(imm), instruction[i][j]);
			}
			tenth *= 10;
			j++;
		}
		if (strlen(imm) != 0)
		{
			if (imm[0] >= '0' && imm[0] <= '9')
			{
				tenth = 1;

				for (int k = 0; k < strlen(imm); k++)
				{
					INT_imm = INT_imm * tenth;

					INT_imm += (imm[k] - '0');
					tenth *= 10;
				}
			}
			else
			{
				INT_imm = search_on_Map_lable(symbol_Table, symbol_Table_size, imm);
				if (INT_imm == -1)
				{
					exit(1);
				}
			}

		}


	}
	char* total = "";
	connector_I(op_code, Decimal_To_Binary(rs, 4), Decimal_To_Binary(rt, 4),
		Decimal_To_Binary(INT_imm, 15), total);
	return Binary_To_Decimal(total, 32);
}

unsigned long int I_Type(char* instruct, char** instruction, int j, int i,
	struct MAP_lable* symbol_Table, int symbol_Table_size)
{
	// instruction $rt, $rs, imm
	// machin code : 0000 op_code rs, rt, offset
	while (instruction[i][j] == " ")
		j++;
	unsigned long int final_result;
	if (strcmp(instruct, "addi"))
	{
		final_result = seprator_I(instruction, j, i, "0101", instruct, symbol_Table, symbol_Table_size);
	}
	else if (strcmp(instruct, "slti"))
	{
		final_result = seprator_I(instruction, j, i, "0110", instruct, symbol_Table, symbol_Table_size);
	}
	else if (strcmp(instruct, "ori"))
	{
		final_result = seprator_I(instruction, j, i, "0111", instruct, symbol_Table, symbol_Table_size);
	}
	else if (strcmp(instruct, "lui"))
	{
		final_result = seprator_I(instruction, j, i, "1000", instruct, symbol_Table, symbol_Table_size);
	}
	else if (strcmp(instruct, "lw"))
	{
		final_result = seprator_I(instruction, j, i, "1001", instruct, symbol_Table, symbol_Table_size);
	}
	else if (strcmp(instruct, "sw"))
	{
		final_result = seprator_I(instruction, j, i, "1010", instruct, symbol_Table, symbol_Table_size);
	}
	else if (strcmp(instruct, "beq"))
	{
		final_result = seprator_I(instruction, j, i, "1011", instruct, symbol_Table, symbol_Table_size);
	}
	else if (strcmp(instruct, "jalr"))
	{
		final_result = seprator_I(instruction, j, i, "1100", instruct, symbol_Table, symbol_Table_size);
	}

	return final_result;
}

void connector_J(char* op_code, char* offset, char* total)
{
	int i, j = 0;
	for (i = 31; i > 27; i--)
	{
		strcat_s(total, strlen(total), '0');
	}
	strcat_s(total, strlen(total), op_code);
	strcat_s(total, strlen(total), "00000000");
	strcat_s(total, strlen(total), offset);
	return total;
}

unsigned long int seprator_J(char** instruction, int j, int i,
	struct MAP_lable* symbol_Table, int symbol_Table_size)
{
	char offset[] = "";
	strcat_s(instruction[i], strlen(instruction[i]), " ");
	while (instruction[i][j] != " " || instruction[i][j] != '#')
	{
		strcat_s(offset, strlen(offset), instruction[i][j]);
		j++;
	}
	int index = 0, INT_offset = 0, tenth = 1;
	if (offset[index] >= '0' && offset[index] <= '9')
	{
		for (int k = 0; k < strlen(offset); k++)
		{
			INT_offset = INT_offset * tenth;

			INT_offset += (offset[k] - '0');
			tenth *= 10;
		}
	}
	else
	{
		INT_offset = search_on_Map_lable(symbol_Table, symbol_Table_size, offset);
		if (INT_offset == -1)
		{
			exit(1);
		}
	}
	char* total = "";
	connector_J("1101", Decimal_To_Binary(INT_offset, 16), total);
	return Binary_To_Decimal(total, 32);
}

unsigned long int J_Type(char** instruction, char* instruct, int i, int j,
	struct MAP_lable* symbol_Table, int symbol_Table_size)
{
	//هالت هیچی نداره، جی هم یکی  داره.
	if (instruct == "halt")
	{
		return 234881024;
	}
	else
	{
		while (instruction[i][j] == " ")
			j++;
		unsigned long int final_result;
		final_result = seprator_J(instruction, j, i, symbol_Table, symbol_Table_size);
		return final_result;
	}
}

unsigned long int directive(char** instruction, int i, int j,
	struct MAP_lable* symbol_Table, int symbol_Table_size)
{
	while (instruction[i][j] == ' ')
		j++;
	char what_num[] = "";
	strcat_s(instruction[i], strlen(instruction[i]), " ");
	while (instruction[i][j] != ' ')
	{
		strcat_s(what_num, strlen(what_num), instruction[i][j]);
		j++;
	}
	unsigned long int what_int = 0;
	if ((what_num[i] >= '0' && what_num[i] <= '9') || what_num == '-')
	{
		int tenth = 1, i = 0;
		if (what_num[0] == '-')
			i = 1;
		for (; i < strlen(what_num); i++)
		{
			what_int = what_int * tenth;
			what_int += (what_num[i] - '0');
			tenth *= 10;
		}
		if (what_num[0] == '-')
			what_int *= -1;
	}
	else
	{
		what_int = search_on_Map_lable(symbol_Table, symbol_Table_size, what_num);
		if (what_int == -1)
		{
			exit(1);
		}
	}
	return what_int;
}

unsigned long int What_kind(char** instruction, int instruction_counter, int i,
	struct MAP_lable* symbol_Table, int symbol_Table_size)
{
	int j;
	char instruct[] = "";
	for (j = 0; instruction[i][j] != " "; j++); // اگر لیبلی وجود داره، ردش میکنیم
	while (instruction[i][j] == " ")
	{
		//  تا رسیدن به اولین اینستراکشن، اسپیس ها رو هم رد میکنیم
		j++;
	}
	while (instruction[i][j] != " ")
	{
		strcat_s(instruct, strlen(instruct), instruction[i][j]);

		j++;
	}
	//  اینجا، اون قسمت اینستراکشن رو توی اینستراکت ریختیم
	// is it true?! //what do you mean?
	// J is now whatever after the instruction. $rd, $rs, %rt
	// so we're gonna send j to the function to use it

	unsigned long int final_result;

	if (strcmp(instruct, "add") || strcmp(instruct, "sub") ||
		strcmp(instruct, "slt") || strcmp(instruct, "or") ||
		strcmp(instruct, "nand"))
	{
		final_result = R_Type(instruct, instruction, j, i);
	}

	else if (strcmp(instruct, "addi") || strcmp(instruct, "ori") ||
		strcmp(instruct, "slti") || strcmp(instruct, "lui") ||
		strcmp(instruct, "lw") || strcmp(instruct, "sw") ||
		strcmp(instruct, "beq") || strcmp(instruct, "jalr"))
	{
		final_result = I_Type(instruct, instruction, j, i, symbol_Table, symbol_Table_size);
	}

	else if (strcmp(instruct, "j") || strcmp(instruct, "halt"))
	{
		final_result = J_Type(instruction, instruct, i, j, symbol_Table, symbol_Table_size);
	}

	else if (strcmp(instruct, ".fill") || strcmp(instruct, ".space"))
	{
		final_result = directive(instruction, i, j, symbol_Table, symbol_Table_size);
	}

	else
		exit(1);
	//خروجی یک به علت آپ کد تعریف نشده.
	return final_result;
}

void write_file(char** instruction, FILE* output, int instruction_counter,
	struct MAP_lable* symbol_Table, int symbol_Table_size)
{ 
	
	unsigned long int final_result;
	for (int i = 0; i < instruction_counter; i++)
	{
	
		final_result = What_kind(instruction, instruction_counter, i, symbol_Table, symbol_Table_size);
		printf("%d\n", final_result);
		//(final_result, output);
		//fputs("\n", output);
	}
}

void fill_instruction(char instruction[][200], int * instruction_counter)
{

	char path[100] = "";
	printf("\nenter address of your file: ");
	gets(path);
	FILE* Input = fopen("H:\\4\\CA_pro_trytorun\\CA_try_line\\test_I.txt", "r");
	if (Input == NULL)
	{
		printf("???");

		exit(1);
	}


	int j = 0;

	int count = 0;

	while (fgets(instruction[(*instruction_counter)], 200, Input))
	{
		printf("%s", instruction[(*instruction_counter)]);
		instruction[(*instruction_counter)][strlen(instruction[(*instruction_counter)]) - 1] = '\0';
		(*instruction_counter)=(*instruction_counter)+1;
	}

}

int main(int argc, char* argv[])
{
	FILE* Input;
	FILE* Output;


	int instruction_counter = 0;
	char* instruction[65537];

	fill_instruction(instruction, &instruction_counter);


	struct MAP_lable* symbol_Table = (struct MAP_lable*)malloc(instruction_counter * sizeof(struct MAP_lable));
	int symbol_Table_Size = 0;

	first_scan(Input, symbol_Table, instruction, symbol_Table_Size);


	write_file(instruction, Output, instruction_counter, symbol_Table, symbol_Table_Size);

	return 0;



}