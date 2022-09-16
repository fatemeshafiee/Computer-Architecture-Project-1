#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//H:\4\architecture\project2\UIsinglecycle\tests\bfassembeld\test6_Itest.as

char instruction[65537][200];
int instruction_counter = 0;
struct MAP_lable
{

    char* lable;
    int address;

};
int search_on_map_label(struct MAP_lable* symbol_Table, int* symbol_Table_size, char* lable)
{
    for (int j = 0; j < *symbol_Table_size; j++)
    {
        if(strcmp(symbol_Table[j].lable, lable) ==  0)
            return symbol_Table[j].address;

    }
    return -1;
}
char* my_strcat(char* destination, char* source)
{
    strcpy(destination + strlen(destination), source);
    return destination;
}

void fill_instruction()
{
    //C:/Users/KPS/Documents/CApro/test_I.txt
    char path[100] = "";
    printf("\n Enter address of your file: ");
    gets(path);
    FILE* Input = fopen(path, "r");
    if (Input == NULL)
    {
        printf("NOT FOUND!");


        exit(1);
    }

    while (fgets(instruction[(instruction_counter)], 200, Input))
    {
        printf("%s", instruction[(instruction_counter)]);
        instruction[(instruction_counter)][strlen(instruction[(instruction_counter)]) - 1] = '\0';
        (instruction_counter) = (instruction_counter)+1;
    }
    printf("\n");
    printf("%d\n", instruction_counter);

}
void first_scan(struct MAP_lable* symbol_Table, int *symbol_Table_Size)
{
    for (int i = 0; i < instruction_counter; i++)
    {
        if(instruction[i][0] == '\t' || instruction[i][0] ==' ')
            continue;
        int lable_counter = 0;
        //char New_lable[7];
        char * New_lable = (char *)calloc(7, 1);
        while(instruction[i][lable_counter]!='\t' && instruction[i][lable_counter]!=' ')
        {
            char * to_add = (char *)calloc(2, 1);
            to_add[0]= instruction[i][lable_counter];
            my_strcat(New_lable,to_add);
            lable_counter++;
        }
        if(search_on_map_label(symbol_Table,symbol_Table_Size,New_lable) != -1)
        {
            printf("A label has been used more than once \n");
            exit(1);
        }

        else
        {
            symbol_Table[*symbol_Table_Size].lable = New_lable;
            symbol_Table[*symbol_Table_Size].address = i;
            *symbol_Table_Size = *symbol_Table_Size + 1;
        }

    }
}

int convert_string_to_int(char * input)
{
    int t = 0;
    if(input[0]!= '-')
    {
        for ( int  i = strlen(input)-1; i >= 0; i--)
        {
            t += (input[i] - '0')*pow(10,strlen(input)-1-i);
        }
        return t;
    }
    for ( int  i = strlen(input)-1; i > 0; i--)
    {
        t += (input[i] - '0')*pow(10,strlen(input)-1-i);
    }
    t*=-1;
    return t;

}
void Decimal_to_binary(int input,char * binary, int binary_size)
{
    int is_negativ=0;

    if(input<0)
    {
        input *=-1;
        is_negativ=1;
    }
    while (input!=0)
    {
        int remind = input%2;
        input = input/2;
        char * to_be_add= (char *)calloc(2, 1);
        to_be_add[0] = '0'+remind ;
        my_strcat(binary,to_be_add);

    }
    while (strlen(binary) <binary_size)
    {
        char * to_be_add= (char *)calloc(2, 1);
        to_be_add[0] = '0' ;
        my_strcat(binary,to_be_add);
    }
    if((strlen(binary)>binary_size) && binary_size==16)
    {
        printf("the offset size is grater than 16 \n");
        exit(1);
    }

    if(is_negativ)
    {
        int index = 0;
        while (binary[index]!='1')
        {
            index++;
        }
        index++;
        for (int i = index; i < strlen(binary); i++)
        {

            if(binary[i]=='0')
                binary[i]='1';
            else {
                binary[i] = '0';
            }
        }

    }
    strrev(binary);


}
long long int Binary_to_decimal (char * binary_result)
{
    long long int result = 0;
    for (int i = 0 ; i < strlen(binary_result); i++)
    {
        int power = 31 - i;
        if(binary_result[i]=='1')
        {

            result += pow(2,power);
        }

    }
    return result;
}

void I_connector(char * opcode,char * binary_rs, char * binary_rt, char * binary_offset,char * final_binary_result)
{
    //0000opcodersrtoffset
    for (int i = 0;i <4; i++)
    {
        char * to_be_add= (char *)calloc(2, 1);
        to_be_add[0]  = '0';
        my_strcat(final_binary_result,to_be_add);
    }
    my_strcat(final_binary_result,opcode);
    my_strcat(final_binary_result,binary_rs);
    my_strcat(final_binary_result,binary_rt);
    my_strcat(final_binary_result,binary_offset);

}

long long int I_separator(char * opcode, int index,int instruction_number, struct MAP_lable* symbol_Table, int *symbol_Table_Size)
{
    int rt=0,rs=0,offset=0;
    char * rtc= (char *)calloc(5, 1);
    char * rsc= (char *)calloc(5, 1);
    char * offc= (char *)calloc(17, 1);
    char * binary_rt= (char *)calloc(5, 1);
    char * binary_rs= (char *)calloc(5, 1);
    char * binary_offset= (char *)calloc(17, 1);
    char * binary_result= (char *)calloc(34, 1);

    if(!strcmp(opcode,"1000"))
    {
        while (instruction[instruction_number][index]!=',')
        {
            char * to_be_add= (char *)calloc(2, 1);
            to_be_add[0] = instruction[instruction_number][index];
            my_strcat(rtc,to_be_add);
            index++;
        }
        index++;
        char * to_be_add = (char *)calloc(2, 1);
        to_be_add[0] = '0';
        my_strcat(rsc,to_be_add);
        while (instruction[instruction_number][index]!=' '&& instruction[instruction_number][index]!='\t')
        {
            char * to_be_add= (char *)calloc(2, 1);
            to_be_add[0] = instruction[instruction_number][index];
            my_strcat(offc,to_be_add);
            index++;
        }

    }
    else if (!strcmp(opcode,"1100"))
    {
        while (instruction[instruction_number][index]!=',')
        {
            char * to_be_add= (char *)calloc(2, 1);
            to_be_add[0] = instruction[instruction_number][index];
            my_strcat(rtc,to_be_add);
            index++;
        }
        index++;
        while (instruction[instruction_number][index]!=' ' && instruction[instruction_number][index]!='\t')
        {
            char * to_be_add= (char *)calloc(2, 1);
            to_be_add[0] = instruction[instruction_number][index];
            my_strcat(rsc,to_be_add);
            index++;
        }
        char * to_be_add = (char *)calloc(2, 1);
        to_be_add[0] = '0';
        my_strcat(offc,to_be_add);

    }
    else
    {
        while (instruction[instruction_number][index]!=',')
        {
            char * to_be_add= (char *)calloc(2, 1);
            to_be_add[0] = instruction[instruction_number][index];
            my_strcat(rtc,to_be_add);
            index++;
        }
        index++;
        while (instruction[instruction_number][index]!=',')
        {
            char * to_be_add= (char *)calloc(2, 1);
            to_be_add[0] = instruction[instruction_number][index];
            my_strcat(rsc,to_be_add);
            index++;
        }
        index++;
        while (instruction[instruction_number][index]!=' '&& instruction[instruction_number][index]!='\t')
        {
            char * to_be_add= (char *)calloc(2, 1);
            to_be_add[0] = instruction[instruction_number][index];
            my_strcat(offc,to_be_add);
            index++;
        }


    }
    if((offc[0]>='a' && offc[0]<='z') ||(offc[0]>='A' && offc[0]<='Z'))
    {
        if(search_on_map_label(symbol_Table,symbol_Table_Size,offc)== -1)
        {
            printf("Use of undefined label!\n");
            exit(1);
        }
        else
        {
            offset = search_on_map_label(symbol_Table,symbol_Table_Size,offc);
        }
    }
    else
        offset = convert_string_to_int(offc);

    rt = convert_string_to_int(rtc);
    rs = convert_string_to_int(rsc);
    Decimal_to_binary(rt,binary_rt, 4);
    Decimal_to_binary(rs,binary_rs, 4);
    Decimal_to_binary(offset, binary_offset, 16);

    I_connector(opcode,binary_rs,binary_rt,binary_offset,binary_result);
    //    printf("%s\n", binary_result);
    long long int decimal_result = Binary_to_decimal(binary_result);
    return decimal_result;
}

long long int I_type(char * instruct ,int index,int instruction_number, struct MAP_lable* symbol_Table, int *symbol_Table_Size)
{
    long long int decimal_result;
    char * op_code= (char *)calloc(5, 1);
    if (!strcmp(instruct, "addi"))
    {
        op_code="0101";
    }
    else if (!strcmp(instruct, "slti"))
    {
        op_code="0110";
    }
    else if (!strcmp(instruct, "ori"))
    {
        op_code="0111";
    }
    else if (!strcmp(instruct, "lui"))
    {
        op_code="1000";
    }
    else if (!strcmp(instruct, "lw"))
    {
        op_code="1001";
    }
    else if (!strcmp(instruct, "sw"))
    {
        op_code="1010";
    }
    else if (!strcmp(instruct, "beq"))
    {
        op_code="1011";
    }
    else if (!strcmp(instruct, "jalr"))
    {
        op_code="1100";
    }
    //    printf("%s\n", instruct);

    decimal_result = I_separator(op_code,index,instruction_number,symbol_Table,symbol_Table_Size);
    return decimal_result;
}

void R_Connector(char* final_result, char* rt, char* rd, char* rs, char* op_code)
{
    for(int i = 0; i < 4; i++)
    {
        char * add_0 = (char *)calloc(2, 1);
        add_0[0] = '0';
        my_strcat(final_result, add_0);
    }

    //    printf("%s\n", op_code);
    //    printf("rt %s\n", rt);
    //    printf("rs %s\n", rs);
    //    printf("rd %s\n", rd);

    my_strcat(final_result, op_code);
    my_strcat(final_result, rs);
    my_strcat(final_result, rt);
    my_strcat(final_result, rd);

    for(int i = 0; i <= 11; i++)
    {
        char * end_0 = (char *)calloc(2, 1);
        end_0[0] = '0';
        my_strcat(final_result, end_0);
    }
}

long long int R_Separator(char* op_code, int instruction_number, int index)
{
    char* rtc = (char *)calloc(5, 1);
    char* rsc = (char *)calloc(5, 1);
    char* rdc = (char *)calloc(5, 1);
    int which = 0;
    while(instruction[instruction_number][index] != ' ' && instruction[instruction_number][index] != '\t')
    {
        if(instruction[instruction_number][index] == ',')
        {
            index++;
            which++;
        }
        else
        {
            char* to_be_added = (char *)calloc(2, 1);
            to_be_added[0] = instruction[instruction_number][index];
            if(!which)
            {
                my_strcat(rdc, to_be_added);
            }
            else if(which == 2)
            {
                my_strcat(rtc, to_be_added);
            }
            else
            {
                my_strcat(rsc, to_be_added);
            }
            index++;
        }
    }

    char* binary_rt = (char *)calloc(5, 1);
    char* binary_rd = (char *)calloc(5, 1);
    char* binary_rs = (char *)calloc(5, 1);
    char* final_result = (char *)calloc(33, 1);
    int rt = 0, rs = 0, rd = 0;

    rt = convert_string_to_int(rtc);
    rs = convert_string_to_int(rsc);
    rd = convert_string_to_int(rdc);

    Decimal_to_binary(rd, binary_rd, 4);
    Decimal_to_binary(rs, binary_rs, 4);
    Decimal_to_binary(rt, binary_rt, 4);

    R_Connector(final_result, binary_rt, binary_rd, binary_rs, op_code);
    //    printf("%s\n", final_result);
    return Binary_to_decimal(final_result);
}

long long int R_Type(int instruction_number, char* instruct, int index)
{
    long long int decimal_result;
    char * op_code= (char *)calloc(5, 1);

    if (!strcmp(instruct, "add"))
        op_code="0000";

    else if (!strcmp(instruct, "sub"))
        op_code="0001";

    else if (!strcmp(instruct, "or"))
        op_code="0011";

    else if (!strcmp(instruct, "slt"))
        op_code="0010";

    else if (!strcmp(instruct, "nand"))
        op_code="0100";

    decimal_result = R_Separator(op_code, instruction_number, index);
    //    printf("%d\n", decimal_result);
    return decimal_result;
}

void J_Connector(char * final_binary, char * op_code, char * binary_offset)
{
    for(int i = 0; i < 4; i++)
    {
        char * add_0 = (char *)calloc(2, 1);
        add_0[0] = '0';
        my_strcat(final_binary, add_0);
    }

    my_strcat(final_binary, op_code);
    for(int i = 16; i <= 23; i++)
    {
        char * add_1 = (char *)calloc(2, 1);
        add_1[0] = '0';
        my_strcat(final_binary, add_1);
    }
    my_strcat(final_binary, binary_offset);
}

long long int J_Seprator(int instruction_number, char* op_code, int index, struct MAP_lable* symbol_Table, int *symbol_Table_Size)
{
    char * offset_C = (char *)calloc(17, 1);
    int offset_int = 0;
    if(!strcmp(op_code, "1101"))
    {
        while(instruction[instruction_number][index] != ' ' && instruction[instruction_number][index] != '\t')
        {
            char * to_be_added = (char *)calloc(2, 1);
            to_be_added[0] = instruction[instruction_number][index];
            my_strcat(offset_C, to_be_added);
            index++;
        }
        if((offset_C[0]>='a' && offset_C[0]<='z') || (offset_C[0]>='A' && offset_C[0]<='Z'))
        {
            if(search_on_map_label(symbol_Table,symbol_Table_Size,offset_C)== -1)
            {
                printf("Use of undefined label!\n");
                exit(1);
            }
            else
            {
                offset_int = search_on_map_label(symbol_Table,symbol_Table_Size,offset_C);
            }
        }
        else
        {
            offset_int = convert_string_to_int(offset_C);
        }
    }
    else
    {
        offset_int = 0;
    }

    char* binary_offset = (char *)calloc(17, 1);
    Decimal_to_binary(offset_int, binary_offset, 16);
    long long int final_result = 0;
    char* final_binary = (char*)calloc(34, 1);
    J_Connector(final_binary, op_code, binary_offset);
    final_result = Binary_to_decimal(final_binary);
    return final_result;
}

long long int J_Type(int instruction_number, char* instruct, int index, struct MAP_lable* symbol_Table, int *symbol_Table_Size)
{
    char* op_code = (char *)calloc(5, 1);
    long long int decimal_result;
    if(!strcmp(instruct, "halt"))
        //return 234881024;
        op_code = "1110";
    else if(!strcmp(instruct, "j"))
        op_code = "1101";
    //    printf("recognized! \n");
    decimal_result = J_Seprator(instruction_number, op_code, index, symbol_Table, symbol_Table_Size);
    return decimal_result;
}

long long int what_kind(int instruction_number, struct MAP_lable* symbol_Table, int *symbol_Table_Size)
{
    int index=0;
    long long int decimal_result =0;
    char * space= (char *)calloc(2, 1);
    space[0]=' ';
    my_strcat(instruction[instruction_number],space);
    while(instruction[instruction_number][index]!='\t' && instruction[instruction_number][index]!=' ')
    {
        index++;
    }
    while(instruction[instruction_number][index]=='\t' || instruction[instruction_number][index]==' ')
    {
        index++;
    }
    char * instruct= (char *)calloc(5, 1);
    while(instruction[instruction_number][index]!='\t' && instruction[instruction_number][index]!=' ')
    {
        char * to_be_add= (char *)calloc(5, 1);
        to_be_add[0]=instruction[instruction_number][index];
        my_strcat(instruct,to_be_add);
        index++;
    }
    while(instruction[instruction_number][index]=='\t' || instruction[instruction_number][index]==' ')
    {
        index++;
    }



    if (strcmp(instruct, "addi") == 0 || strcmp(instruct, "ori") ==  0
            ||strcmp(instruct, "slti") == 0 || strcmp(instruct, "lui") ==  0
            ||strcmp(instruct, "lw") == 0   || strcmp(instruct, "sw") ==   0
            ||strcmp(instruct, "beq") == 0  || strcmp(instruct, "jalr") == 0)
    {
        decimal_result = I_type(instruct,index,instruction_number,symbol_Table,symbol_Table_Size);
    }

    else if(strcmp(instruct, "add") == 0  || strcmp(instruct, "or") ==  0
            ||strcmp(instruct, "slt") == 0 || strcmp(instruct, "sub") ==  0
            ||strcmp(instruct, "nand") == 0)
    {
        decimal_result = R_Type(instruction_number, instruct, index);
    }

    else if(strcmp(instruct, "j") == 0 || strcmp(instruct, "halt") == 0)
    {
        decimal_result = J_Type(instruction_number, instruct, index, symbol_Table, symbol_Table_Size);
    }

    else if(strcmp(instruct, ".fill") == 0 || strcmp(instruct, ".space") == 0)
    {
        char* front = (char *)calloc(65538, 1);
        while(instruction[instruction_number][index] != ' ' && instruction[instruction_number][index] != '\t')
        {
            char * to_be_added = (char *)calloc(2, 1);
            to_be_added[0]=instruction[instruction_number][index];
            my_strcat(front,to_be_added);
            index++;
        }
        if((front [0] > 47 && front [0] <58) || (front[0] == '-' && (front [1] > 47 && front [1] <58) ) )
            decimal_result = convert_string_to_int(front);
        else
            decimal_result = search_on_map_label(symbol_Table,symbol_Table_Size,front);
    }

    else
    {
        printf("Op_Code Undefined!\n");
        exit(1);
    }

    return decimal_result;
}

int main()
{


    fill_instruction();
    struct MAP_lable* symbol_Table = (struct MAP_lable*)calloc(instruction_counter, sizeof(struct MAP_lable));
    int  symbol_Table_Size = 0;
    first_scan(symbol_Table,&symbol_Table_Size);
    printf("%s\n", "--------------------------------------------------------");
    FILE *output = fopen ("program.mc", "w");
    if (!output)
        perror("fopen");
    for (int i =0; i < instruction_counter;i++)
    {
        printf("%s\n", instruction[i]);
        long long result =what_kind(i,symbol_Table,&symbol_Table_Size);
        fprintf(output, "%lld\n", result);
        printf("%lld\n", result);
        printf("%s\n", "--------------------------------------------------------");
    }


    return 0;
}
