/*
 * Author: Benjamin Holleman
 *
 * Used RC4.c by Robin Verton as reference
 * https://gist.github.com/rverton/a44fc8ca67ab9ec32089 
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 256 //2^8

//Swap bytes
void swap(unsigned char *a, unsigned char *b) {
    unsigned char tmp = *a;
    *a = *b;
    *b = tmp;
}

//Key scheduling algorithm
int KSA(char *key, unsigned char *S) {
    int len = strlen(key);
    int j = 0;
    
    int x;
    for(x = 0; x < N; x++) {
        S[x] = x;
    }

    int i;
    for(i = 0; i < N; i++) {
        j = (j + S[i] + key[i % len]) % N;
        swap(&S[i], &S[j]);
    }
    /*
    //added
    printf("KeyStream: ");
    for(i = 0; i < N; i++) {
        printf("%02hhx", S[i]);
    }
    printf("\n");
    */
    return 0;
}

//Pseudo-random generation algorithm
int PRGA(unsigned char *S, char *plaintext, unsigned char *ciphertext) { 
    unsigned char i = 0;
    unsigned char j = 0;
    int len; 
    size_t n;   
    for(n = 0, len = strlen(plaintext); n < len; n++) {        
        i = (i + 1) % N;
        j = (j + S[i]) % N;
        swap(&S[i], &S[j]);
        unsigned char rnd = S[(S[i] + S[j]) % N]; 
        ciphertext[n] = rnd ^ plaintext[n];
    }
    return 0;
}

//Performs encryption process
int RC4(char *key, char *plaintext, unsigned char *ciphertext, unsigned char *S) {
   //unsigned char S[N];
    KSA(key, S);
    PRGA(S, plaintext, ciphertext);
    return 0;
}

//Main function
int main(int argc, char *argv[]) {
    if(argc < 3) {
        printf("Usage: %s <key> <plaintext>", argv[0]);
        return -1;
    }
    //Concatinate arguments if more than one word.
    /*
    if(argc > 3) {
        int l;
        for(l = 0, l <= argc, l++){
            
        }
        printf("argv[2]: %s \n", argv[2]);
        printf("argv[3]: %s \n", argv[3]);
        printf("argv[4]: %s \n", argv[4]);
    }
    */
    unsigned char *ciphertext = malloc(sizeof(int) * strlen(argv[2]));

    //added
    unsigned char S[N];
    unsigned char *plaintext = malloc(sizeof(int) * strlen(argv[2]));

    RC4(argv[1], argv[2], ciphertext, S);

    size_t i;
    int len;
    printf("Key: %s\n", argv[1]);
    printf("PlainText: %s\n", argv[2]);
    printf("CypherText: ");
    for(i = 0, len = strlen(argv[2]); i < len; i++) {
        printf("%02hhx", ciphertext[i]);
    }
    printf("\n");
    /*
    //added
    printf("Decrypted : ");
    int a = 0;
    int b = 0;
    int leng;
    size_t n;
    for(n = 0, leng = strlen(ciphertext); n < leng; n++)
    {
        a = (a + 1) % N;
        b = (b + S[a] + S[b]) % N;
        swap(&S[a], &S[b]);
        int rnd = S[(S[a] + S[b]) % N];

         plaintext[n] = rnd ^ ciphertext[n];
    }
    for(i = 0, len = strlen(argv[2]); i < len; i++) {
        printf("%02hhx", argv[2]);
    }
    printf("\n");
    */
    return 0;
}

