#include <stdio.h>
#define ull unsigned long long
ull Sbox[16][16] = {
    {0xd6, 0x90, 0xe9, 0xfe, 0xcc, 0xe1, 0x3d, 0xb7, 0x16, 0xb6, 0x14, 0xc2, 0x28, 0xfb, 0x2c, 0x05},
    {0x2b, 0x67, 0x9a, 0x76, 0x2a, 0xbe, 0x04, 0xc3, 0xaa, 0x44, 0x13, 0x26, 0x49, 0x86, 0x06, 0x99},
    {0x9c, 0x42, 0x50, 0xf4, 0x91, 0xef, 0x98, 0x7a, 0x33, 0x54, 0x0b, 0x43, 0xed, 0xcf, 0xac, 0x62},
    {0xe4, 0xb3, 0x1c, 0xa9, 0xc9, 0x08, 0xe8, 0x95, 0x80, 0xdf, 0x94, 0xfa, 0x75, 0x8f, 0x3f, 0xa6},
    {0x47, 0x07, 0xa7, 0xfc, 0xf3, 0x73, 0x17, 0xba, 0x83, 0x59, 0x3c, 0x19, 0xe6, 0x85, 0x4f, 0xa8},
    {0x68, 0x6b, 0x81, 0xb2, 0x71, 0x64, 0xda, 0x8b, 0xf8, 0xeb, 0x0f, 0x4b, 0x70, 0x56, 0x9d, 0x35},
    {0x1e, 0x24, 0x0e, 0x5e, 0x63, 0x58, 0xd1, 0xa2, 0x25, 0x22, 0x7c, 0x3b, 0x01, 0x21, 0x78, 0x87},
    {0xd4, 0x00, 0x46, 0x57, 0x9f, 0xd3, 0x27, 0x52, 0x4c, 0x36, 0x02, 0xe7, 0xa0, 0xc4, 0xc8, 0x9e},
    {0xea, 0xbf, 0x8a, 0xd2, 0x40, 0xc7, 0x38, 0xb5, 0xa3, 0xf7, 0xf2, 0xce, 0xf9, 0x61, 0x15, 0xa1},
    {0xe0, 0xae, 0x5d, 0xa4, 0x9b, 0x34, 0x1a, 0x55, 0xad, 0x93, 0x32, 0x30, 0xf5, 0x8c, 0xb1, 0xe3},
    {0x1d, 0xf6, 0xe2, 0x2e, 0x82, 0x66, 0xca, 0x60, 0xc0, 0x29, 0x23, 0xab, 0x0d, 0x53, 0x4e, 0x6f},
    {0xd5, 0xdb, 0x37, 0x45, 0xde, 0xfd, 0x8e, 0x2f, 0x03, 0xff, 0x6a, 0x72, 0x6d, 0x6c, 0x5b, 0x51},
    {0x8d, 0x1b, 0xaf, 0x92, 0xbb, 0xdd, 0xbc, 0x7f, 0x11, 0xd9, 0x5c, 0x41, 0x1f, 0x10, 0x5a, 0xd8},
    {0x0a, 0xc1, 0x31, 0x88, 0xa5, 0xcd, 0x7b, 0xbd, 0x2d, 0x74, 0xd0, 0x12, 0xb8, 0xe5, 0xb4, 0xb0},
    {0x89, 0x69, 0x97, 0x4a, 0x0c, 0x96, 0x77, 0x7e, 0x65, 0xb9, 0xf1, 0x09, 0xc5, 0x6e, 0xc6, 0x84},
    {0x18, 0xf0, 0x7d, 0xec, 0x3a, 0xdc, 0x4d, 0x20, 0x79, 0xee, 0x5f, 0x3e, 0xd7, 0xcb, 0x39, 0x48}};
ull Ck[32] = {
    0x00070e15L, 0x1c232a31L, 0x383f464dL, 0x545b6269L, 0x70777e85L, 0x8c939aa1L, 0xa8afb6bdL, 0xc4cbd2d9L,
    0xe0e7eef5L, 0xfc030a11L, 0x181f262dL, 0x343b4249L, 0x50575e65L, 0x6c737a81L, 0x888f969dL, 0xa4abb2b9L,
    0xc0c7ced5L, 0xdce3eaf1L, 0xf8ff060dL, 0x141b2229L, 0x30373e45L, 0x4c535a61L, 0x686f767dL, 0x848b9299L,
    0xa0a7aeb5L, 0xbcc3cad1L, 0xd8dfe6edL, 0xf4fb0209L, 0x10171e25L, 0x2c333a41L, 0x484f565dL, 0x646b7279L};
ull Fk[4] = {0xa3b1bac6L, 0x56aa3350L, 0x677d9197L, 0xb27022dcL};
ull RoundKey[32] = {};
ull Coutput[5] = {};
ull Output[1000] = {};
void hex_print(ull input, int num)
{
    int i = 0;
    for (i = 0; i < num; i++)
    {
        if (i % 2 == 0)
        {
            printf("0x");
        }
        ull temp = input >> (4 * (15 - i)) & 0xf;
        printf("%x", temp);
        if ((i - 1) % 2 == 0)
        {
            printf(" ");
        }
    }
}
ull Hextoint(char a)
{
    ull output = 0;
    switch (a)
    {
    case 'a':
        output = 0xaL;
        break;
    case 'b':
        output = 0xbL;
        break;
    case 'c':
        output = 0xcL;
        break;
    case 'd':
        output = 0xdL;
        break;
    case 'e':
        output = 0xeL;
        break;
    case 'f':
        output = 0xfL;
        break;
    default:
        output = a - '0';
        break;
    }
    return output;
}
ull Sub_box(ull input)
{
    int i = 0;
    ull result = 0;
    ull temp;
    ull imp = 0xffL;
    for (i = 0; i < 4; i++)
    {
        temp = input & imp;
        int row = (int)((temp >> 4) & 0xfL);
        int col = (int)((temp)&0xfL);
        input = input >> 8;
        result |= ((Sbox[row][col]) << (8 * i));
    }
    return result;
}
ull LeftShift(ull input, int n)
{
    return ((input << n) & 0xffffffffL) | (input >> (32 - n));
}
ull L(ull input)
{
    ull output = input ^ LeftShift(input, 2) ^ LeftShift(input, 10) ^ LeftShift(input, 18) ^ LeftShift(input, 24);
    return output;
}
ull StrtoHex(char array[], int begin, int len)
{
    int j = 0;
    ull temp = 0;
    int count = len - 1;
    for (j = begin; j < begin + len; j++)
    {
        temp |= Hextoint(array[j]) << (4 * count);
        count--;
    }
    return temp;
}
void KeyExtend(char array[])
{
    int i = 0;
    ull MK[4];
    ull IRK[36];
    int count = 0;
    for (i = 2; i < 27; i = i + 8)
    {
        MK[count] = StrtoHex(array, i, 8);
        IRK[count] = MK[count] ^ Fk[count];
        count++;
    }
    for (i = 0; i < 32; i++)
    {
        ull temp1 = IRK[i + 1] ^ IRK[i + 2] ^ IRK[i + 3] ^ Ck[i];
        ull temp2 = Sub_box(temp1);
        ull temp3 = IRK[i] ^ (temp2 ^ LeftShift(temp2, 13) ^ LeftShift(temp2, 23));
        RoundKey[i] = temp3;
        IRK[i + 4] = temp3;
    }
}
ull F_fun(ull X0, ull X1, ull X2, ull X3, ull rk)
{
    ull temp1 = X1 ^ X2 ^ X3 ^ rk;
    ull temp2 = Sub_box(temp1);
    ull temp3 = X0 ^ (L(temp2));
    return temp3;
}
void SM4_Cipher(ull input[], int mode)
{
    int i = 0;
    ull X[36];
    int count = 0;
    X[0] = (input[0] >> 32) & 0xffffffffL;
    X[1] = (input[0]) & 0xffffffffL;
    X[2] = (input[1] >> 32) & 0xffffffffL;
    X[3] = (input[1]) & 0xffffffffL;
    for (i = 0; i < 32; i++)
    {
        if (mode == 1)
        {
            X[i + 4] = F_fun(X[i], X[i + 1], X[i + 2], X[i + 3], RoundKey[i]);
        }
        else
        {
            X[i + 4] = F_fun(X[i], X[i + 1], X[i + 2], X[i + 3], RoundKey[31 - i]);
        }
    }
    Coutput[0] = X[35] << 32;
    Coutput[0] |= X[34] & 0xffffffffL;
    Coutput[1] = X[33] << 32;
    Coutput[1] |= X[32] & 0xffffffffL;
}
void ECB_Cipher(ull input[],int mode,int flag){
    SM4_Cipher(input, mode);
    Output[flag] = Coutput[0];        //前64bit
    Output[flag + 1] = Coutput[1];    //后64bit
}
void Output_Print(int flag,int num,int mode,int need){
    int i=0;
    ull last = 0;
    if (need == 16 && mode == 0)
    {
        flag -= 2; //解密时可能会补上一行，但这行不是输出的最后一行
    }
    last = Output[flag - 1] & 0xffL;
    if (mode == 1)
    {
        for (i = 0; i < flag; i += 2)
        {
            if (i != 0 && i % 2 == 0)
            {
                printf("\n");
            }
            hex_print(Output[i], 16);
            hex_print(Output[i + 1], 16);
        }
    }
    else
    {
        for (i = 0; i < flag; i += 2)
        {
            if (i != 0 && i % 2 == 0)
            {
                printf("\n");
            }
            if ((i + 2) == flag)
            {
                if (last < 8)
                { 
                    hex_print(Output[i], 16);                        //输出前8个字节
                    hex_print(Output[i + 1], 2 * (8 - last));        //输出后8-last个字节
                }
                else
                {
                    hex_print(Output[i], 2 * (16 - last));
                }
            }
            else
            {
                hex_print(Output[i], 16);
                hex_print(Output[i + 1], 16);
            }
        }
    }
}
int main()
{
    char Key[50];
    int n, mode, num = 0, i = 0, flag = 0;
    scanf("%s", Key);
    scanf("%d", &mode);
    KeyExtend(Key);
    ull input[2] = {};
    ull temp = 0, count = 0;
    ull Memory = 0, move = 7;
    while (scanf("%x", &temp) != EOF)
    {
        num++;
        Memory |= temp << (8 * move);         //八个字节记录一次数据
        move--;
        if (num % 8 == 0)
        {
            move = 7;
            input[count] = Memory;
            Memory = 0;
            count++;
        }
        if (num % 16 == 0)
        {
            count = 0;
            ECB_Cipher(input,mode,flag);
            flag += 2;
        }
    }
    ull need = 16 - (num % 16); //需要填充的分组的字节数
    if (need < 9)
    {
        for (i = 0; i < need; i++)
        {
            Memory |= (need << 8 * i);         //前面已经把输入弄到对应的高位了
        }
        input[count] = Memory;
        ECB_Cipher(input,mode,flag);
        flag += 2;
    }
    else
    {
        for (i = 0; i < need - 8; i++)
        {
            Memory |= (need << 8 * i);
        }
        input[count] = Memory;
        Memory = 0;
        for (i = 0; i < 8; i++)
        {
            Memory |= (need << 8 * i);
        }
        input[count + 1] = Memory;
        ECB_Cipher(input,mode,flag);
        flag += 2;
    }
    Output_Print(flag,num,mode,need);
    return 0;
}
