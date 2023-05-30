import java.util.Scanner;

public class AES192 {
    static int[][] Sbox = {
            {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
            {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
            {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
            {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
            {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
            {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
            {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
            {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
            {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
            {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
            {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
            {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
            {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
            {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
            {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
            {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}
    };
    static int[][] Sboxinverse = {
            {0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb},
            {0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb},
            {0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e},
            {0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25},
            {0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92},
            {0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84},
            {0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06},
            {0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b},
            {0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73},
            {0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e},
            {0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b},
            {0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4},
            {0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f},
            {0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef},
            {0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61},
            {0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d}
    };
    static long[] Rcon = {0X00000000l, 0x01000000L, 0x02000000L, 0x04000000L, 0x08000000L, 0x10000000L, 0x20000000L, 0x40000000L, 0x80000000L, 0x1b000000L, 0x36000000L};
    static long[] word = new long[70];  //字的总数为Nb*(Nr+1)
    static long[] dword = new long[70];
    static int[][] W = new int[4][70]; //将轮密钥存储起来
    static int[][] DW = new int[4][70];

    //Add
    /*public static int add(int a,int b){
        return a^b;
    }*/
    //Mul mod x^4+1=10001=0x11
    public static int mul(int a, int b) {
        int ans = 0;
        while (b > 0) {
            if ((b & 0x01) == 0x01) {
                ans ^= a;
            }
            a <<= 1;
            if ((a & 0x100) == 0x100) {
                a ^= 0x11b;
            }
            a &= 0xff;
            b >>= 1;
        }
        return ans;
    }

    public static void StrtoBytes(String input, int[][] state) {
        String[] strarray = new String[20];
        for (int j = 0; j < 34; j += 2) {
            strarray[j / 2] = input.substring(j, j + 2);        //将字符串按照字节分割
        }
        //包括0x
        for (int i = 1; i < 17; i++) {
            int index = i - 1;          //注意大小端
            int row = index % 4;
            int col = index / 4;
            state[row][col] = Integer.parseInt(strarray[i], 16);
        }
    }

    //Sbox
    public static void SubBytes(int[][] state) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                int temp = state[i][j];
                int col = state[i][j] & 0xf;
                int row = (state[i][j] >> 4) & 0xf;
                state[i][j] = Sbox[row][col];
            }
        }

        /*System.out.print("SubBytes:");
        StateHexPrint(state);
        System.out.print(" ");*/

    }

    //Sboxinverse
    public static void SubBytesInverse(int[][] state) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                int temp = state[i][j];
                int col = state[i][j] & 0xf;
                int row = (state[i][j] >> 4) & 0xf;
                state[i][j] = Sboxinverse[row][col];
            }
        }
        /*System.out.print("SubBytesInverse:");
        StateHexPrint(state);
        System.out.print(" ");*/
    }

    //ShiftRows
    public static void ShiftRows(int[][] state) {
        int[][] memory = new int[4][4];
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                memory[i][j] = state[i][(j + i) % 4];
            }
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                state[i][j] = memory[i][j];
            }
        }
        /*System.out.print("ShiftRows:");
        StateHexPrint(state);
        System.out.print(" ");*/
    }

    //ShifrRowsInverse
    public static void ShiftRowsInverse(int[][] state) {
        int[][] memory = new int[4][4];
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                memory[i][(j + i) % 4] = state[i][j];
            }
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                state[i][j] = memory[i][j];
            }
        }
        /*System.out.print("ShiftRowsInverse:");
        StateHexPrint(state);
        System.out.print(" ");*/
    }

    public static void MixColumn(int[][] state) {
        int[][] memory = new int[4][4];
        int[][] martix = {{2, 3, 1, 1}, {1, 2, 3, 1}, {1, 1, 2, 3}, {3, 1, 1, 2}};
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 4; i++) {
                int result = 0;
                for (int k = 0; k < 4; k++) {
                    int temp = mul(martix[i][k], state[k][j]);
                    result ^= temp;
                }
                memory[i][j] = result;
            }
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                state[i][j] = memory[i][j];
            }
        }
        /*System.out.print("MixColumn:");
        StateHexPrint(state);
        System.out.print(" ");*/
    }

    //MixColumnInverse
    public static void MixColumnInverse(int[][] state) {
        int[][] memory = new int[4][4];
        int[][] martix = {{0x0e, 0x0b, 0x0d, 0x09}, {0x09, 0x0e, 0x0b, 0x0d}, {0x0d, 0x09, 0x0e, 0x0b}, {0x0b, 0x0d, 0x09, 0x0e}};
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 4; i++) {
                int result = 0;
                for (int k = 0; k < 4; k++) {
                    int temp = mul(martix[i][k], state[k][j]);
                    result ^= temp;
                }
                memory[i][j] = result;
            }
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                state[i][j] = memory[i][j];
            }
        }

        /*System.out.print("MixColumnInverse:");
        StateHexPrint(state);
        System.out.print(" ");*/
    }

    //Key表示输入的初始密钥，w表示存储的数组,Nk表示输入密钥是多少字
    public static void KeyExpansion(String Key, long w[], int Nk,int Nr) {
        String[] strarray = new String[40];
        int num = Nk*8+2;
        for (int j = 0; j < num; j += 2) {
            strarray[j / 2] = Key.substring(j, j + 2);        //将字符串按照字节分割
        }
        long[] key = new long[Nk*4];
        //将Key转化为字节数组存储起来
        for (int i = 1; i < Nk*4+1; i++) {
            key[i - 1] = Integer.parseInt(strarray[i], 16);
        }
        long temp;
        for (int i = 0; i < Nk; i++) {
            w[i] = (key[4 * i] << 24) | (key[4 * i + 1] << 16) | (key[4 * i + 2] << 8) | (key[4 * i + 3]);

            /*System.out.print("word:");
            Hexprint((int)(w[i]&0xffffffffL));
            System.out.print(" ");*/
        }
        for (int i = Nk; i < 4*(Nr+1); i++) {
            temp = w[i - 1];

            /*System.out.print("\ntemp:");
            Hexprint((int)(temp&0xffffffffL));
            System.out.print(" ");*/

            if (i % Nk == 0) {
                temp = SubWord(RotWord(temp)) ^ Rcon[i / Nk];
            } else if (Nk > 6 && i % Nk == 4) {
                temp = SubWord(temp);
            }

            /*System.out.print("Xor:");
            Hexprint((int)(temp&0xffffffffL));
            System.out.print(" ");*/

            w[i] = w[i - Nk] ^ temp;

            /*System.out.print("w[i-Nk]:");
            Hexprint((int)(w[i-Nk]&0xffffffffL));
            System.out.print(" ");
            System.out.print("w[i]:");
            Hexprint((int)(w[i]&0xffffffffL));
            System.out.print("\n");*/
        }
    }

    public static void GetDW(int Nr) {
        int[][] martix = {{0x0e, 0x0b, 0x0d, 0x09}, {0x09, 0x0e, 0x0b, 0x0d}, {0x0d, 0x09, 0x0e, 0x0b}, {0x0b, 0x0d, 0x09, 0x0e}};
        for (int i = 0; i < 4*(Nr+1); i++) {
            dword[i] = word[i];
        }
        for (int i = 4; i < 4*Nr; i++) {
            long output = 0;
            int[] memory = {(int) ((dword[i] & 0xff000000) >> 24), (int) ((dword[i] & 0xff0000) >> 16), (int) ((dword[i] & 0xff00) >> 8), (int) (dword[i] & 0xff)};
            for (int line = 0; line < 4; line++) {
                long result = 0;
                for (int j = 0; j < 4; j++) {
                    int temp = mul(martix[line][j], memory[j]);
                    result = result ^ (long) temp;
                }
                output |= (result << (3 - line) * 8) & 0xffffffff;
            }
            dword[i] = output;
        }

    }

    public static long RotWord(long input) {
        long high = (input << 8) & 0xffffffffL;
        long low = (input >> 24) & 0xff;
        long temp = high | low;

        /*System.out.print("RotWord():");
        Hexprint((int)(temp&0xffffffffL));
        System.out.print(" ");*/

        return temp;
    }

    public static long SubWord(long input) {
        long imp = 0xff;
        long result = 0;
        for (int i = 0; i < 4; i++) {
            int temp = (int) (input & imp); //取低八位
            input = input >> 8;
            int col = temp & 0xf;
            int row = (temp >> 4) & 0xf;
            long num = (long) Sbox[row][col];
            result |= (num << (8 * i)) & 0xffffffffL;
        }

        /*System.out.print("SubWord():");
        Hexprint((int)(result&0xffffffffL));
        System.out.print(" ");*/

        return result;
    }

    //将word作为字节数组存储起来
    public static void MemoryWord(long[] w, int num) {
        for (int i = 0; i < num; i++) {
            W[0][i] = (int) (w[i] >> 24 & 0xff);
            W[1][i] = (int) (w[i] >> 16 & 0xff);
            W[2][i] = (int) (w[i] >> 8 & 0xff);
            W[3][i] = (int) (w[i] & 0xff);
        }
    }

    //将dword作为字节数组存储起来
    public static void MemoryDWord(long[] w, int num) {
        for (int i = 0; i < num; i++) {
            DW[0][i] = (int) (w[i] >> 24 & 0xff);
            DW[1][i] = (int) (w[i] >> 16 & 0xff);
            DW[2][i] = (int) (w[i] >> 8 & 0xff);
            DW[3][i] = (int) (w[i] & 0xff);
        }
    }

    //轮密钥加 round表示轮数
    public static void AddRoundKey(int[][] state, int round) {
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 4; i++) {
                state[i][j] = state[i][j] ^ W[i][round * 4 + j];
            }
        }
        //System.out.print("\n");
    }

    public static void AESCipher(int[][] state,int Nr) {

        /*System.out.print("Start:");
        StateHexPrint(state);
        System.out.print(" ");*/

        AddRoundKey(state, 0);
        //AES-128共10轮
        for (int i = 1; i < Nr; i++) {

            /*System.out.print("Start:");
            StateHexPrint(state);
            System.out.print(" ");*/

            SubBytes(state);
            ShiftRows(state);
            MixColumn(state);
            AddRoundKey(state, i);
        }
        SubBytes(state);
        ShiftRows(state);
        AddRoundKey(state, Nr);
    }

    public static void AddRoundKeyInverse(int[][] state, int round) {
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 4; i++) {
                state[i][j] = state[i][j] ^ DW[i][round * 4 + j];
            }
        }
        //System.out.print("\n");
    }

    public static void AESInverseCipher(int[][] state,int Nr) {
        GetDW(Nr);
        int num=4*(Nr+1);
        MemoryDWord(dword, num);
        AddRoundKeyInverse(state, Nr);
        for (int i=Nr-1; i > 0; i--) {
            SubBytesInverse(state);
            ShiftRowsInverse(state);
            MixColumnInverse(state);
            AddRoundKeyInverse(state, i);
        }
        SubBytesInverse(state);
        ShiftRowsInverse(state);
        AddRoundKeyInverse(state, 0);
    }

    public static void StateHexPrint(int[][] output) {
        System.out.print("0x");
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 4; i++) {
                Hexprint(output[i][j]);
            }
        }
    }

    public static void Hexprint(int input) {
        if (Integer.toHexString(input).length() == 1) {
            System.out.print("0" + Integer.toHexString(input));
        } else {
            System.out.print(Integer.toHexString(input));
        }
    }

    public static void AES(int[][] state, int mode, int n,int  Nr) {
        if (mode == 1) {
            for (int i = 0; i < n; i++) {
                AESCipher(state,Nr);
            }
        } else {
            for (int i = 0; i < n; i++) {
                AESInverseCipher(state,Nr);
            }
        }
    }

    public static void main(String argvs[]) {
        int[][] state = new int[4][4];
        Scanner scan = new Scanner(System.in);
        int len = scan.nextInt();
        //int len=256;
        int Nr=0,Nk=0;
        int n = scan.nextInt();
        //int n=1;
        String input = scan.next();
        //String input = new String("0x3243f6a8885a308d313198a2e0370734");
        String Key = scan.next();
        //String Key = new String("0x603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4");
        int mode = scan.nextInt();
        //int mode = 1;
        if(len==128){
            Nk=4;
            Nr=10;
        }else if(len==192){
            Nk=6;
            Nr=12;
        }else if(len==256){
            Nk=8;
            Nr=14;
        }
        KeyExpansion(Key, word, Nk,Nr);
        MemoryWord(word, 4*(Nr+1));
        StrtoBytes(input, state);
        AES(state, mode, n,Nr);
        StateHexPrint(state);
        /*int[][] ShiftInversetest={{0xd4,0xe0,0xb8,0x1e},{0xbf,0xb4,0x41,0x27},{0x5d,0x52,0x11,0x98},{0x30,0xae,0xf1,0xe5}};
        ShiftRowsInverse(ShiftInversetest);
        int[][] MixInversetest={{0x04,0xe0,0x48,0x28},{0x66,0xcb,0xf8,0x06},{0x81,0x19,0xd3,0x26},{0xe5,0x9a,0x7a,0x4c}};
        MixColumnInverse(MixInversetest);*/
    }
}
