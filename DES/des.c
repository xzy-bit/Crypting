#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ull unsigned long long
int IPtable[64] = {58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
                   62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
                   57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
                   61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7};

int IPinverse[64] = {40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
                     38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
                     36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
                     34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25};

int PC_1[56] = {57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18,
                10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36,
                63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22,
                14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4};

int PC_2[48] = {14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10,
                23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2,
                41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
                44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32};

int Etable[48] = {32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9,
                  8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
                  16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
                  24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1};

int movetable[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

ull SPbox[8][64] = {
    {0x808200, 0x0, 0x8000, 0x808202, 0x808002, 0x8202,
     0x2, 0x8000, 0x200, 0x808200, 0x808202, 0x200,
     0x800202, 0x808002, 0x800000, 0x2, 0x202, 0x800200,
     0x800200, 0x8200, 0x8200, 0x808000, 0x808000, 0x800202,
     0x8002, 0x800002, 0x800002, 0x8002, 0x0, 0x202,
     0x8202, 0x800000, 0x8000, 0x808202, 0x2, 0x808000,
     0x808200, 0x800000, 0x800000, 0x200, 0x808002, 0x8000,
     0x8200, 0x800002, 0x200, 0x2, 0x800202, 0x8202,
     0x808202, 0x8002, 0x808000, 0x800202, 0x800002, 0x202,
     0x8202, 0x808200, 0x202, 0x800200, 0x800200, 0x0,
     0x8002, 0x8200, 0x0, 0x808002},

    {0x40084010, 0x40004000, 0x4000, 0x84010, 0x80000, 0x10,
     0x40080010, 0x40004010, 0x40000010, 0x40084010, 0x40084000, 0x40000000,
     0x40004000, 0x80000, 0x10, 0x40080010, 0x84000, 0x80010,
     0x40004010, 0x0, 0x40000000, 0x4000, 0x84010, 0x40080000,
     0x80010, 0x40000010, 0x0, 0x84000, 0x4010, 0x40084000,
     0x40080000, 0x4010, 0x0, 0x84010, 0x40080010, 0x80000,
     0x40004010, 0x40080000, 0x40084000, 0x4000, 0x40080000, 0x40004000,
     0x10, 0x40084010, 0x84010, 0x10, 0x4000, 0x40000000,
     0x4010, 0x40084000, 0x80000, 0x40000010, 0x80010, 0x40004010,
     0x40000010, 0x80010, 0x84000, 0x0, 0x40004000, 0x4010,
     0x40000000, 0x40080010, 0x40084010, 0x84000},

    {0x104, 0x4010100, 0x0, 0x4010004, 0x4000100, 0x0,
     0x10104, 0x4000100, 0x10004, 0x4000004, 0x4000004, 0x10000,
     0x4010104, 0x10004, 0x4010000, 0x104, 0x4000000, 0x4,
     0x4010100, 0x100, 0x10100, 0x4010000, 0x4010004, 0x10104,
     0x4000104, 0x10100, 0x10000, 0x4000104, 0x4, 0x4010104,
     0x100, 0x4000000, 0x4010100, 0x4000000, 0x10004, 0x104,
     0x10000, 0x4010100, 0x4000100, 0x0, 0x100, 0x10004,
     0x4010104, 0x4000100, 0x4000004, 0x100, 0x0, 0x4010004,
     0x4000104, 0x10000, 0x4000000, 0x4010104, 0x4, 0x10104,
     0x10100, 0x4000004, 0x4010000, 0x4000104, 0x104, 0x4010000,
     0x10104, 0x4, 0x4010004, 0x10100},

    {0x80401000, 0x80001040, 0x80001040, 0x40, 0x401040, 0x80400040,
     0x80400000, 0x80001000, 0x0, 0x401000, 0x401000, 0x80401040,
     0x80000040, 0x0, 0x400040, 0x80400000, 0x80000000, 0x1000,
     0x400000, 0x80401000, 0x40, 0x400000, 0x80001000, 0x1040,
     0x80400040, 0x80000000, 0x1040, 0x400040, 0x1000, 0x401040,
     0x80401040, 0x80000040, 0x400040, 0x80400000, 0x401000, 0x80401040,
     0x80000040, 0x0, 0x0, 0x401000, 0x1040, 0x400040,
     0x80400040, 0x80000000, 0x80401000, 0x80001040, 0x80001040, 0x40,
     0x80401040, 0x80000040, 0x80000000, 0x1000, 0x80400000, 0x80001000,
     0x401040, 0x80400040, 0x80001000, 0x1040, 0x400000, 0x80401000,
     0x40, 0x400000, 0x1000, 0x401040},

    {0x80, 0x1040080, 0x1040000, 0x21000080, 0x40000, 0x80,
     0x20000000, 0x1040000, 0x20040080, 0x40000, 0x1000080, 0x20040080,
     0x21000080, 0x21040000, 0x40080, 0x20000000, 0x1000000, 0x20040000,
     0x20040000, 0x0, 0x20000080, 0x21040080, 0x21040080, 0x1000080,
     0x21040000, 0x20000080, 0x0, 0x21000000, 0x1040080, 0x1000000,
     0x21000000, 0x40080, 0x40000, 0x21000080, 0x80, 0x1000000,
     0x20000000, 0x1040000, 0x21000080, 0x20040080, 0x1000080, 0x20000000,
     0x21040000, 0x1040080, 0x20040080, 0x80, 0x1000000, 0x21040000,
     0x21040080, 0x40080, 0x21000000, 0x21040080, 0x1040000, 0x0,
     0x20040000, 0x21000000, 0x40080, 0x1000080, 0x20000080, 0x40000,
     0x0, 0x20040000, 0x1040080, 0x20000080},

    {0x10000008, 0x10200000, 0x2000, 0x10202008, 0x10200000, 0x8,
     0x10202008, 0x200000, 0x10002000, 0x202008, 0x200000, 0x10000008,
     0x200008, 0x10002000, 0x10000000, 0x2008, 0x0, 0x200008,
     0x10002008, 0x2000, 0x202000, 0x10002008, 0x8, 0x10200008,
     0x10200008, 0x0, 0x202008, 0x10202000, 0x2008, 0x202000,
     0x10202000, 0x10000000, 0x10002000, 0x8, 0x10200008, 0x202000,
     0x10202008, 0x200000, 0x2008, 0x10000008, 0x200000, 0x10002000,
     0x10000000, 0x2008, 0x10000008, 0x10202008, 0x202000, 0x10200000,
     0x202008, 0x10202000, 0x0, 0x10200008, 0x8, 0x2000,
     0x10200000, 0x202008, 0x2000, 0x200008, 0x10002008, 0x0,
     0x10202000, 0x10000000, 0x200008, 0x10002008},

    {0x100000, 0x2100001, 0x2000401, 0x0, 0x400, 0x2000401,
     0x100401, 0x2100400, 0x2100401, 0x100000, 0x0, 0x2000001,
     0x1, 0x2000000, 0x2100001, 0x401, 0x2000400, 0x100401,
     0x100001, 0x2000400, 0x2000001, 0x2100000, 0x2100400, 0x100001,
     0x2100000, 0x400, 0x401, 0x2100401, 0x100400, 0x1,
     0x2000000, 0x100400, 0x2000000, 0x100400, 0x100000, 0x2000401,
     0x2000401, 0x2100001, 0x2100001, 0x1, 0x100001, 0x2000000,
     0x2000400, 0x100000, 0x2100400, 0x401, 0x100401, 0x2100400,
     0x401, 0x2000001, 0x2100401, 0x2100000, 0x100400, 0x0,
     0x1, 0x2100401, 0x0, 0x100401, 0x2100000, 0x400,
     0x2000001, 0x2000400, 0x400, 0x100001},

    {0x8000820, 0x800, 0x20000, 0x8020820, 0x8000000, 0x8000820,
     0x20, 0x8000000, 0x20020, 0x8020000, 0x8020820, 0x20800,
     0x8020800, 0x20820, 0x800, 0x20, 0x8020000, 0x8000020,
     0x8000800, 0x820, 0x20800, 0x20020, 0x8020020, 0x8020800,
     0x820, 0x0, 0x0, 0x8020020, 0x8000020, 0x8000800,
     0x20820, 0x20000, 0x20820, 0x20000, 0x8020800, 0x800,
     0x20, 0x8020020, 0x800, 0x20820, 0x8000800, 0x20,
     0x8000020, 0x8020000, 0x8020020, 0x8000000, 0x20000, 0x8000820,
     0x0, 0x8020820, 0x20020, 0x8000020, 0x8020000, 0x8000800,
     0x8000820, 0x0, 0x8020820, 0x20800, 0x20800, 0x820,
     0x820, 0x20020, 0x8000000, 0x8020800}};
ull childKey1[16] = {0};
ull childKey2[16] = {0};
// IP置换
// input表示输入
//将output的第(63-i)位置换为input的第(64-Sub_tab[i])位
ull Sub_IP(ull input)
{
    int i = 0;
    ull output = 0;
    for (i = 0; i < 64; i++)
    {
        output |= (((input) >> (64 - IPtable[i]) & 1) << (63 - i));
    }
    return output;
}
// 16进制输出
void hex_print(ull input)
{
    printf("0x");
    int i = 0;
    for (i = 0; i < 16; i++)
    {
        ull temp = input >> (4 * (15 - i)) & 0xf;
        printf("%x", temp);
    }
}
// IP逆置换
ull Sub_IPinverse(ull input)
{
    int i = 0;
    ull output = 0;
    for (i = 0; i < 64; i++)
    {
        output |= (((input) >> (64 - IPinverse[i]) & 1) << (63 - i));
    }
    return output;
}
// PC_1置换
//输入64bit，输出56bit
ull Sub_PC1(ull input)
{
    int i = 0;
    ull output = 0;
    for (i = 0; i < 56; i++)
    {
        output |= (((input) >> (64 - PC_1[i]) & 1) << (55 - i));
    }
    return output;
}
// PC_2置换
//输入56bit，输出48bit
ull Sub_PC2(ull input)
{
    int i = 0;
    ull output = 0;
    for (i = 0; i < 48; i++)
    {
        output |= (((input) >> (56 - PC_2[i]) & 1) << (47 - i));
    }
    return output;
}
//扩展置换E
//输入32bit，输出48bit
ull Sub_E(ull input)
{
    ull result = 0;
    result = (result << 1) | ((input)&1);
    result = (result << 5) | ((input >> 27) & 0x1f);
    result = (result << 6) | ((input >> 23) & 0x3f);
    result = (result << 6) | ((input >> 19) & 0x3f);
    result = (result << 6) | ((input >> 15) & 0x3f);
    result = (result << 6) | ((input >> 11) & 0x3f);
    result = (result << 6) | ((input >> 7) & 0x3f);
    result = (result << 6) | ((input >> 3) & 0x3f);
    result = (result << 5) | (input & 0x1f);
    result = (result << 1) | ((input >> 31) & 1);
    return result;
}
ull Sub_Sbox(ull input)
{
    int i = 0, num = 0, line = 0, col = 0;
    ull output = 0;
    ull temp = 0;
    ull outputtemp = 0;
    ull imp = 0x3f;
    //从低位到高位
    ull newoutput = 0;
    for (i = 0; i < 8; i++)
    {
        temp = input & imp; //取出最低的6位数字
        input = input >> 6;
        newoutput |= SPbox[7 - i][temp];
    }
    // printf("\n");
    return newoutput;
}
//循环左移
// input表示输入,n表示移位的位数
ull Leftshift(ull input, int n)
{
    return (((input) >> (28 - n)) | ((input << n) & 0xfffffff));
}
//子密钥生成
//输入64bit密钥，一共生成16个子密钥
void Sub_key(ull input,ull childKey[])
{
    ull pc1 = Sub_PC1(input);
    // printf("pc1:%llx ",pc1);
    ull D0 = (pc1)&0xfffffff;           //低28位
    ull C0 = ((pc1) >> 28) & 0xfffffff; //高28位
    // printf("D0:%llx C0:%llx ",D0,C0);
    ull Droll = D0;
    ull Croll = C0;
    ull temp = 0;
    int i = 0;
    for (i = 0; i < 16; i++)
    {
        Droll = Leftshift(Droll, movetable[i]); //低28位
        Croll = Leftshift(Croll, movetable[i]); //高28位
        // printf("Droll:%llx Croll:%llx ", Droll, Croll);
        temp = (Croll << 28) | Droll;
        childKey[i] = Sub_PC2(temp);
        // printf("%llx\n", childKey[i]);
    }
}
// F函数
//输入32bit数据,Keyroll表示轮密钥
ull F_fun(ull input, ull Keyroll)
{
    ull temp = 0;
    ull outputtemp = 0;
    ull output = 0;
    input = Sub_E(input);     //扩展置换E
    temp = input ^ Keyroll;      //异或运算
    outputtemp = Sub_Sbox(temp); // S盒代替
    return outputtemp;
}
// DES加密算法
//输入64bit数据，64bit密钥，mode模式
ull DES(ull input, int mode,ull childKey[])
{
    ull iptemp = Sub_IP(input);           // IP置换
    ull R0 = (iptemp)&0xffffffff;         //低32位
    ull L0 = (iptemp >> 32) & 0xffffffff; //高32位
    ull Rroll = R0;
    ull Lroll = L0;
    ull Rtemp = 0;
    ull Ltemp = 0;
    int i = 0;
    for (i = 0; i < 16; i++)
    {
        if (mode == 1)
        {
            Ltemp = Rroll;
            Rtemp = Lroll ^ F_fun(Rroll, childKey[i]);
            Lroll = Ltemp;
            Rroll = Rtemp;
        }
        else
        {
            Ltemp = Rroll;
            Rtemp = Lroll ^ F_fun(Rroll, childKey[15 - i]);
            Lroll = Ltemp;
            Rroll = Rtemp;
        }
        /*printf("R:");
        hex_print(Rroll);
        printf(" ");
        printf("L:");
        hex_print(Lroll);
        printf("\n");*/
    }
    ull outtemp = (Rroll << 32) | Lroll;
    //hex_print(outtemp);
    //printf("\n");
    ull output = Sub_IPinverse(outtemp);
    return output;
}
int main()
{
    int n, mode;
    ull input, key;
    scanf("%d%llx%llx%d", &n, &input, &key, &mode);
    Sub_key(key,childKey1);
    ull temp, output;
    int i = 0;
    for (i = 0; i < n; i++)
    {
        if (i == 0)
        {
            temp = DES(input, mode,childKey1);
        }
        else
        {
            temp = DES(temp, mode,childKey1);
        }
    }
    output = temp;
    hex_print(output);
    return 0;
}
