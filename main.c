#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//C:/Users/KPS/Documents/CApro/error4.as

#define MAX_LINE_LENGTH 100
char instruction[65537][200];
unsigned long long instruction_counter = 0;

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

char* my_strcat(char* destination, char* source)
{
    strcpy(destination + strlen(destination), source);
    return destination;
}
struct MAP_lable
{

    char* lable;
    int address;

};
int search_on_Map_lable(struct MAP_lable* symbol_Table, int* symbol_Table_size, char* lable)
{
    printf("search_on_Map_lable function\n ");
    if (*symbol_Table_size == 0)
        return -1;
    for (int i = 0; i < *symbol_Table_size; i++)
    {
        if (strcmp(symbol_Table[i].lable, lable) == 0)
        {
            return symbol_Table[i].address;
        }

    }
    return -1;
}

//طبق داک، این کار رو تو اسکن اول داریم انجام میدیم
void first_scan(struct MAP_lable* symbol_Table, int* symbol_Table_Size)
{
    printf("first scan function\n ");
    for (int i = 0; i < instruction_counter; i++)
    {
        if (instruction[i][0] != ' ' && instruction[i][0] != '\t')
        {
            unsigned int j;
            for (j = 0; instruction[i][j] != ' ' && instruction[i][j] != '\t'; j++);
            //char newlable[10] = { 0 };
            char* newlable = (char*)calloc(j + 1, 1);
            for (unsigned int k = 0; k < j; k++)
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
                    symbol_Table[*symbol_Table_Size].lable = newlable;
                    symbol_Table[*symbol_Table_Size].address = i;
                    *symbol_Table_Size = *symbol_Table_Size + 1;


                }
            }
        }
    }
    return;
}

//function to transfer binary to int
void  Decimal_To_Binary(int n, int size, char* binary)
{

    printf("DecimalTo binary function %d\n ", n);
    char rest;
    printf("the binary sent to function : %s\n", binary);
    printf("%d\n", strlen(binary));
    int cnt = 0;
    while (n > 0)
    {
        rest = (char)(n % 2);
        rest += '0';
        char* sent[1];
        sent[0] = rest;
        printf("this is rest in while : %c\n", rest);
        //strcpy(binary + strlen(binary), &rest);
        my_strcat(binary, sent);
        //printf("this is strcat binary with rest : $s\n", binary);
        n /= 2;
        cnt++;
    }
    //printf("this is cnt : %d\n and this is binary after while : %s\n", cnt, binary);
    while (cnt < size)
    {
        my_strcat(binary, "0");
        cnt++;
    }
    if (size == 16 && strlen(binary) > 16)// strlen > size?
    {
        printf("exit \n");
        exit(1);
    }
    printf("binary after size scale %s\n", binary);
    printf(" binary size %d\n", strlen(binary));
    //return strrev(binary);
    char* reversed_bin = (char*)calloc(strlen(binary) + 1, 1);
    printf(" reversed_bin size %d\n", strlen(reversed_bin));
    printf("biin333333333 %s\n", binary);
    for (int k = 0; k < strlen(binary); k++)
    {
        reversed_bin[k] = binary[size - k - 1];
        printf("this is in for : %s\n", reversed_bin);
    }
    printf("outsiude the for: %s\n", reversed_bin);
    for (int k = 0; k < strlen(binary); k++)
    {
        binary[k] = reversed_bin[k];
    }

    printf("biin %s\n", binary);
    free(reversed_bin);


}

unsigned long int Binary_To_Decimal(char* number, int size)
{
    printf("BTOD function\n ");
    unsigned long int n = 0, two = 0;
    for (int i = size - 1; i >= 0; i--)
    {
        n += (pow(2, two) * (number[i] - '0'));
        two++;
    }
    return n;
}

//فعلا برای R_Type
void connector_R(char* op_code, char* rs, char* rt, char* rd, char* total)
{
    printf(" connector_R function\n ");
    int i, j = 0;
    for (i = 31; i > 27; i--)
    {
        my_strcat(total, "0");
    }
    my_strcat(total, op_code);
    my_strcat(total, rs);
    my_strcat(total, rt);
    my_strcat(total, rd);
    for (i = 11; i >= 0; i--)
    {
        my_strcat(total, "0");
    }
}
unsigned long int seprator_R(int j, int i, char* op_code, char* instruct)
{
    printf(" sepra_R function\n ");

    int rd = 0, rs = 0, rt = 0, tenth = 1, tdd = 0;
    my_strcat(instruction[i], " ");
    while (instruction[i][j] != ' ' && instruction[i][j] != '#' && instruction[i][j] != '\t')
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
    char* total = (char*)calloc(32, 1);
    char* binary_rs = (char*)calloc(4, 1);
    char* binary_rt = (char*)calloc(4, 1);
    char* binary_rd = (char*)calloc(4, 1);
    Decimal_To_Binary(rs, 4, binary_rs);
    Decimal_To_Binary(rt, 4, binary_rt);
    Decimal_To_Binary(rd, 4, binary_rd);
    connector_R(op_code, binary_rs, binary_rt, binary_rd, total);
    return Binary_To_Decimal(total, 32);
}

unsigned long int R_Type(char* instruct, int j, int i)
{
    printf(" R-type function\n ");
    // instruction $rd, $rs, $rt
    // in machin code : 0000 op-code rs rt rd
    // j is a index of first space after instruct
    while (instruction[i][j] == ' ' || instruction[i][j] == '\t')
        j++;

    unsigned long int final_result;
    if (!strcmp(instruct, "add"))
    {
        final_result = seprator_R(j, i, "0000", instruct);
    }
    else if (!strcmp(instruct, "sub"))
    {
        final_result = seprator_R(j, i, "0001", instruct);
    }
    else if (!strcmp(instruct, "slt"))
    {
        final_result = seprator_R(j, i, "0010", instruct);
    }
    else if (!strcmp(instruct, "or"))
    {
        final_result = seprator_R(j, i, "0011", instruct);
    }
    else if (!strcmp(instruct, "nand"))
    {
        final_result = seprator_R(j, i, "0100", instruct);
    }
    return final_result;
}

//  I type
void connector_I(char* op_code, char* rs, char* rt, char* imm, char* total)
{
    printf(" connector_I function\n ");
    int i, j = 0;
    printf("this is totla : %s\n", total);
    for (i = 31; i > 27; i--)
    {
        my_strcat(total, "0");
    }
    printf("total after for : $s\n", total);
    printf("this is opcode is connector : %s\n", op_code);
    my_strcat(total, op_code);
    my_strcat(total, rs);
    my_strcat(total, rt);
    my_strcat(total, imm);
    printf("final total : %s\n", total);
}

unsigned long int seprator_I(int j, int i, char* op_code, char* instruct,
    struct MAP_lable* symbol_Table, int* symbol_Table_size)
{
    printf("serator I function\n ");
    int rs = 0, rt = 0, INT_imm = 0, tenth = 1, tdd = 0;

    char* imm = (char*)calloc(100, 1);
    my_strcat(instruction[i], " ");
    if (instruct == "lui")
    {
        while (instruction[i][j] != ' ' && instruction[i][j] != '#' && instruction[i][j] != '\t')
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
                char* a[2];
                a[0] = instruction[i][j];
                my_strcat(imm, a);
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
        while (instruction[i][j] != ' ' && instruction[i][j] != '#' && instruction[i][j] != '\t')
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
                char* a[2];
                a[0] = instruction[i][j];
                my_strcat(imm, a);
            }
            tenth *= 10;
            j++;
        }
        //printf("rt : %d, rs :  %d, imm : %s \n", rt, rs, imm);
        if (strlen(imm) != 0)
        {
            if ((imm[0] >= '0' && imm[0] <= '9'))
            {
                tenth = 1;

                for (int k = 0; k < strlen(imm); k++)
                {
                    INT_imm = INT_imm * tenth;

                    INT_imm += (imm[k] - '0');
                    tenth *= 10;
                }
            }
            else if (imm[0] == '-')
            {
                tenth = 1;

                for (int k = 1; k < strlen(imm); k++)
                {
                    INT_imm = INT_imm * tenth;

                    INT_imm += (imm[k] - '0');
                    tenth *= 10;
                }
                INT_imm *= -1;

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
    char* total = (char*)calloc(32, 1);
    char* binary_rs = (char*)calloc(4, 1);
    // char* binary_rs = "";
    char* binary_rt = (char*)calloc(4, 1);
    char* binary_imm = (char*)calloc(16, 1);

    Decimal_To_Binary(rs, 4, binary_rs);
    //printf("binary_rs %s \n", binary_rs);
    Decimal_To_Binary(rt, 4, binary_rt);
    printf("this is rt : %s\n", binary_rt);
    Decimal_To_Binary(INT_imm, 16, binary_imm);
    printf("this is imm : %s\n", binary_imm);
    printf("this is op-code : %s\n", op_code);
    connector_I(op_code, binary_rs, binary_rt, binary_imm, total);
    return Binary_To_Decimal(total, 32);
}

unsigned long int I_Type(char* instruct, int j, int i,
    struct MAP_lable* symbol_Table, int* symbol_Table_size)
{

    printf("I type function\n ");
    // instruction $rt, $rs, imm
    // machin code : 0000 op_code rs, rt, offset
    while (instruction[i][j] == ' ' || instruction[i][j] == '\t')
        j++;
    unsigned long int final_result;
    if (!strcmp(instruct, "addi"))
    {
        final_result = seprator_I(j, i, "0101", instruct, symbol_Table, symbol_Table_size);
    }
    else if (!strcmp(instruct, "slti"))
    {
        final_result = seprator_I(j, i, "0110", instruct, symbol_Table, symbol_Table_size);
    }
    else if (!strcmp(instruct, "ori"))
    {
        final_result = seprator_I(j, i, "0111", instruct, symbol_Table, symbol_Table_size);
    }
    else if (!strcmp(instruct, "lui"))
    {
        final_result = seprator_I(j, i, "1000", instruct, symbol_Table, symbol_Table_size);
    }
    else if (!strcmp(instruct, "lw"))
    {
        final_result = seprator_I(j, i, "1001", instruct, symbol_Table, symbol_Table_size);
    }
    else if (!strcmp(instruct, "sw"))
    {
        final_result = seprator_I(j, i, "1010", instruct, symbol_Table, symbol_Table_size);
    }
    else if (!strcmp(instruct, "beq"))
    {
        final_result = seprator_I(j, i, "1011", instruct, symbol_Table, symbol_Table_size);
    }
    else if (!strcmp(instruct, "jalr"))
    {
        final_result = seprator_I(j, i, "1100", instruct, symbol_Table, symbol_Table_size);
    }

    return final_result;
}

void connector_J(char* op_code, char* offset, char* total)
{
    printf("j connector\n");
    int i, j = 0;
    for (i = 31; i > 27; i--)
    {
        my_strcat(total, "0");
    }
    my_strcat(total, op_code);
    my_strcat(total, "00000000");
    my_strcat(total, offset);

}

unsigned long int seprator_J(int j, int i, struct MAP_lable* symbol_Table, int* symbol_Table_size)
{
    printf("j seprator\n");
    char* offset = (char*)calloc(100, 1);

    my_strcat(instruction[i], " ");
    while (instruction[i][j] != ' ' && instruction[i][j] != '#' && instruction[i][j] != '\t')
    {
        char* a[2];
        a[0] = instruction[i][j];
        my_strcat(offset, a);
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
    else if (offset[index] == '-')
    {
        for (int k = 1; k < strlen(offset); k++)
        {
            INT_offset = INT_offset * tenth;

            INT_offset += (offset[k] - '0');
            tenth *= 10;
        }
        INT_offset *= -1;
    }
    else
    {
        INT_offset = search_on_Map_lable(symbol_Table, symbol_Table_size, offset);
        if (INT_offset == -1)
        {
            exit(1);
        }
    }
    char* total = (char*)calloc(100, 1);

    char* Offset = (char*)calloc(100, 1);
    Decimal_To_Binary(INT_offset, 16, Offset);

    connector_J("1101", Offset, total);
    return Binary_To_Decimal(total, 32);
}

unsigned long int J_Type(char* instruct, int i, int j,
    struct MAP_lable* symbol_Table, int* symbol_Table_size)
{
    printf("j type\n");
    //هالت هیچی نداره، جی هم یکی  داره.
    if (strcmp(instruct, "halt") == 0)
    {
        return 234881024;
    }
    else
    {
        while (instruction[i][j] == ' ' || instruction[i][j] == '\t')
            j++;
        unsigned long int final_result;
        final_result = seprator_J(j, i, symbol_Table, symbol_Table_size);
        return final_result;
    }
}

unsigned long int directive(int i, int j,
    struct MAP_lable* symbol_Table, int* symbol_Table_size)
{
    printf(" directive function\n ");
    while (instruction[i][j] == ' ' || instruction[i][j] == '\t')
        j++;

    char* what_num = (char*)calloc(100, 1);

    my_strcat(instruction[i], " ");
    while (instruction[i][j] != ' ' && instruction[i][j] != '\t')
    {
        char* a = (char*)calloc(2, 1);
        a[0] = instruction[i][j];
        my_strcat(what_num, a);
        j++;
        free(a);
    }
    unsigned long int what_int = 0;
    int k = 0;
    if ((what_num[0] >= '0' && what_num[0] <= '9') || what_num[0] == '-')
    {
        int tenth = 1, i = 0;
        if (what_num[0] == '-')
            k = 1;
        for (; k < strlen(what_num); k++)
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

unsigned long int What_kind(int i,
    struct MAP_lable* symbol_Table, int* symbol_Table_size)
{
    printf(" What kind \n ");
    //printf("instruction being used : %s \n", instruction[i]);
    int j;
    char* instruct = (char*)calloc(100, 1);
    for (j = 0; instruction[i][j] != ' ' && instruction[i][j] != '\t'; j++); // اگر لیبلی وجود داره، ردش میکنیم
    while (instruction[i][j] == ' ' || instruction[i][j] == '\t')
    {
        //  تا رسیدن به اولین اینستراکشن، اسپیس ها رو هم رد میکنیم
        j++;
    }

    while (instruction[i][j] != ' ' && instruction[i][j] != '\t')
    {
        char* a[2];
        a[0] = instruction[i][j];
        my_strcat(instruct, a);
        j++;
    }
    //  اینجا، اون قسمت اینستراکشن رو توی اینستراکت ریختیم
    // is it true?! //what do you mean?
    // J is now whatever after the instruction. $rd, $rs, %rt
    // so we're gonna send j to the function to use it
    printf("%s\n", "instruct is");
    printf("%s\n", instruct);

    unsigned long int final_result;

    if (strcmp(instruct, "add") == 0 || strcmp(instruct, "sub") == 0 ||
        strcmp(instruct, "slt") == 0 || strcmp(instruct, "or") == 0 ||
        strcmp(instruct, "nand") == 0)
    {
        final_result = R_Type(instruct, j, i);
    }

    else if (strcmp(instruct, "addi") == 0 || strcmp(instruct, "ori") == 0 ||
        strcmp(instruct, "slti") == 0 || strcmp(instruct, "lui") == 0 ||
        strcmp(instruct, "lw") == 0 || strcmp(instruct, "sw") == 0 ||
        strcmp(instruct, "beq") == 0 || strcmp(instruct, "jalr") == 0)
    {
        final_result = I_Type(instruct, j, i, symbol_Table, symbol_Table_size);
    }

    else if (strcmp(instruct, "j") == 0 || strcmp(instruct, "halt") == 0)
    {
        final_result = J_Type(instruct, i, j, symbol_Table, symbol_Table_size);
    }

    else if (strcmp(instruct, ".fill") == 0 || strcmp(instruct, ".space") == 0)
    {
        final_result = directive(i, j, symbol_Table, symbol_Table_size);
    }

    else
        exit(1);
    //خروجی یک به علت آپ کد تعریف نشده.
    return final_result;
}

void write_file(FILE* output,
    struct MAP_lable* symbol_Table, int* symbol_Table_size)
{
    //printf("first of write \n");
    //printf("%d\n", instruction_counter);
    unsigned long int final_result;
    for (int i = 0; i < instruction_counter; i++)
    {
        printf("in the for\n%d\n", i);
        my_strcat(instruction[i], " ");
        final_result = What_kind(i, symbol_Table, symbol_Table_size);
        printf("for the instruction i %d\n", i);
        printf("final result is   %lu\n", final_result);
        printf("------------------------------------------------\n");
        //(final_result, output);
        //fputs("\n", output);
    }
}

void fill_instruction()
{
    //C:/Users/KPS/Documents/CApro/test_I.txt
    char path[100] = "";
    printf("\nenter address of your file: ");
    gets(path);
    FILE* Input = fopen(path, "r");
    if (Input == NULL)
    {
        printf("???");


        exit(1);
    }

    int j = 0;
    int count = 0;

    while (fgets(instruction[(instruction_counter)], 200, Input))
    {
        printf("%s", instruction[(instruction_counter)]);
        instruction[(instruction_counter)][strlen(instruction[(instruction_counter)]) - 1] = '\0';
        (instruction_counter) = (instruction_counter)+1;
    }
    printf("\n");
    printf("%d\n", instruction_counter);

}

int main()
{
    FILE* Input;
    FILE* Output;





    fill_instruction();


    struct MAP_lable* symbol_Table = (struct MAP_lable*)calloc(instruction_counter, sizeof(struct MAP_lable));
    int  symbol_Table_Size = 0;
    first_scan(symbol_Table, &symbol_Table_Size);
    write_file(Output, symbol_Table, &symbol_Table_Size);





    return 0;



}
