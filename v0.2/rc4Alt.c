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
    int tmp = *a;
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
    //added
    printf("KeyStream: ");
    for(i = 0; i < N; i++) {
        printf("%02hhx", S[i]);
    }
    printf("\n");

    return 0;
}

//Pseudo-random generation algorithm
int PRGA(unsigned char *S, char *plaintext, unsigned char *ciphertext) { 
    int i = 0;
    int j = 0;
    int len; 
    size_t n;   
    for(n = 0, len = strlen(plaintext); n < len; n++) {        
        i = (i + 1) % N;
        j = (j + S[i] + S[j]) % N;
        swap(&S[i], &S[j]);
        int rnd = S[(S[i] + S[j]) % N];
        
        ciphertext[n] = rnd ^ plaintext[n];
    }
    return 0;
}

//Performs encryption process
int RC4(char *key, char *plaintext, unsigned char *ciphertext) {
    unsigned char S[N];
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

    unsigned char *ciphertext = malloc(sizeof(int) * strlen(argv[2]));

    RC4(argv[1], argv[2], ciphertext);

    size_t i;
    int len;
    printf("CypherText: ");
    for(i = 0, len = strlen(argv[2]); i < len; i++) {
        printf("%02hhx", ciphertext[i]);
    }
    printf("\n");
    return 0;
}

