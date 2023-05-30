### Introduction
This directory contains the codes related with **AES Algorithm**.\
aes128.java / aes.java is the immplment of the AES-128/AES-192/AES-256 algorithm.
### Details
### aes128.c
The input contains four lines.\
The first line contains a positive integer $T$ , which represents the number of encryption/decryption times. The same key is used.\
The second line is a hexadecimal string $s$ , starting with `0x`and representing the text, guaranteed $|s|=34$;\
The third line is a hexadecimal string $k$ , starting with `0x`, which is the key, guaranteed $|k|=34$;\
The fourth line is a non-negative integer $op$ , representing the encryption/decryption mode, 1 for encryption, and 0 for decryption.\
The Output is a string beginning with `0x` , representing the result of crypting/decrypting.
##### Input 1
```
39
0x0ee863a353b646b8a8d105517804b12b
0xf7dad038fb3dc0ab58bb9987ce4aa0f3
0
```
##### Output 1
```
0xad4b2698b827a6ffd5115686bf562134
```
##### Input 2
```
1
0x12dd11bb363e4f010b8f4da1d0e2ad18
0x905cd980666fee1bc97df9c195933cfd
1
```
##### Output 2
```
0x9b99cb1c2493d9ebd3a3c3270c2b28c4
```
### aes.c
The input contains five lines.\
The first line is a positive integer $len$ from the collection ${192,256}$ , representing the lenth of the key. 
The second line contains a positive integer $T$ , which represents the number of encryption/decryption times. The same key is used.\
The third line is a hexadecimal string $s$ , starting with `0x`and representing the text, guaranteed $|s|=34$;\
The fourth line is a hexadecimal string $k$ , starting with `0x`, which is the key, guaranteed $|k|$ from collection ${50,66}$;\
The fifth line is a non-negative integer $op$ , representing the encryption/decryption mode, 1 for encryption, and 0 for decryption.
##### Input 1
```
192
39
0xc142a1e4acb27192f0e36869d2b5b9f8
0xebf353bd5a61d35084c0664197daf0a555d3c9990681171d
0
```
##### Output 1
```
0xb0620b4b0b35fa6f4aaf1c2e7b52be72
```
##### Input 2
```
192
1
0x9781be5aa814088ca649afe586bd6c62
0x21d7d2a82a95fa5a0c690cc04a1d7a0c604a2fd7c9fc1231
1
```
##### Output 2
```
0x476d4bde27714471f7502fa4b16ab470
```



