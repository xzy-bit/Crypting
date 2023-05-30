### Introduction
This directory contains the codes related with **DES Algorithm**.\
des.c is the immplment of the primitive des algorithm.\
ede.c is the immplment of the ede algorithm based on des.
### Details
### des.c
The input contains four lines.\
The first line contains a positive integer $T$ , which represents the number of encryption/decryption times. The same key is used.\
The second line is a hexadecimal string $s$ , starting with `0x`and representing the text, guaranteed $|s|=18$;\
The third line is a hexadecimal string $k$ , starting with `0x`, which is the key, guaranteed $|k|=18$;\
The fourth line is a non-negative integer $op$ , representing the encryption/decryption mode, 1 for encryption, and 0 for decryption.\
The Output is a string beginning with `0x` , representing the result of crypting/decrypting.
##### Input 1
```
39
0x3fc8d0410de97f5e
0xee7bfa825f654293
0
```
##### Output 1
```
0xad0ea0c458594e1e
```
##### Input 2
```
1
0x900eb9584f9321c0
0x84f5ca4805eb1ba3
1
```
##### Output 2
```
0xb144bfab09125c7b
```
### ede.c
The input contains four lines.\
The first line contains a hexadecimal string $s$ , starting with `0x` and representing the text, guaranteed $|s|=18$;\
The second line is a hexadecimal string $k_1$ , which is the first key, guaranteed $|k_1|=18$;\
The third line is a hexadecimal string $k_2$ , which is the second key, guaranteed $|k_2|=18$;\
The fourth line is a non-negative integer $op$ , representing the encryption/decryption mode, 1 for encryption, and 0 for decryption.\
The Output is a string beginning with `0x`, representing the result of crypting/decrypting.
##### Input 1
```
0x78e2025d31d06fde
0xa530af81d46635e4
0xfc6aa9db1d2b1224
1
```
##### Output 1
```
0xf1b98dac6657545c
```
##### Input 2
```
0x618f1b32353b4f35
0xc50f4b2e21282135
0x35becf7d711ee29a
0
```
##### Output 2
```
0xe5388d6e1eda0fad
```



