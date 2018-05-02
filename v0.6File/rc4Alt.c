/*
 * Author:  Benjamin Holleman & Richard Winzenried
 *
 * Used RC4 article on Wikipedia
 * https://en.wikipedia.org/wiki/RC4
 *
 * Used RC4 source code as reference
 * http://cypherpunks.venona.com/archive/1994/09/msg00304.html
 *
 * Used RC4.c by Robin Verton as reference
 * https://gist.github.com/rverton/a44fc8ca67ab9ec32089
 *
 * Used answer from sg7 to fix decryption issues
 * https://stackoverflow.com/questions/6933039/convert-two-ascii-hexadecimal-characters-two-ascii-bytes-in-one-byte
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 256 //2^8

//added
int lengthOfStr;
unsigned char K[N];

//added
unsigned char charToHexDigit(char c) {
    if(c >= 'a')
        return (c - 'a' + 10);
    else
        return (c - '0');
}

unsigned char ascii2HexToByte(unsigned char *ptr) {
    return charToHexDigit(*ptr) * 16 + charToHexDigit(*(ptr+1));
}

int stringToBytes(unsigned char *original, unsigned char *new) {
    int k = 0;
    int strLen = strlen(original);
    int i;
    for(i = 0; i < strLen; i = i + 2)
    {
        new[k] = ascii2HexToByte(&original[i]);
        k++;
    }
    return k;
}


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
    return 0;
}

//Pseudo-random generation algorithm
int PRGA(unsigned char *S, char *plaintext, unsigned char *ciphertext) { 
    unsigned char i = 0;
    unsigned char j = 0;
    int len; 
    size_t n; 
    //added
    unsigned char *decryptedtext = malloc(sizeof(int) * lengthOfStr);

    for(n = 0, len = strlen(plaintext); n < len; n++) {        
        i = (i + 1) % N;
        j = (j + S[i]) % N;
        swap(&S[i], &S[j]);
        unsigned char rnd = S[(S[i] + S[j]) % N]; 
        ciphertext[n] = rnd ^ plaintext[n];
        //added
        decryptedtext[n] = rnd ^ ciphertext[n];
    }
    //added
    int dl;
    int lendl;
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
    printf("\n");
    if(argc < 3) {
        printf("Usage: %s <key> <plaintext> <decrypt(only put here to decrypt)>\n", argv[0]);
        return -1;
    }

    //File reading
    FILE *stream;
    unsigned char *contents;
    int fileSizeA = 0;
    int fileSize = 0;
    
    /*
    stream = fopen(argv[2], "rb");

    fseek(stream, 0L, SEEK_END);
    fileSize = ftell(stream);
    fseek(stream, 0L, SEEK_SET);

    contents = malloc(fileSize);

    size_t size = fread(contents, 1, fileSize, stream);
    contents[size] = 0;

    printf("%s\n", contents);

    fclose(stream);
    */

    stream = fopen(argv[2], "rb");

    while(fgetc(stream) != EOF){
        fileSize++;
    }

    fseek(stream, 0L, SEEK_END);
    fileSize = ftell(stream);
    fseek(stream, 0L, SEEK_SET);

    contents = malloc(fileSize);

    size_t size = fread(contents, 1, fileSize, stream);
    contents[size] = 0;

    printf("%s\n", contents);

    /*
    FILE *a = fopen("abc.txt", "w");
    fwrite(contents, fileSize, 1, a);
    */

    fclose(stream);

    /*
    stream = fopen(argv[2], "rb");
    while(fgetc(stream) != EOF){
        fileSize++;
    }
    contents = malloc(fileSize);
    w
    size_t size = fread(contents, 1, fileSize, stream);
    contents[fileSize] = 0;
    printf("s\n", contents);
    fclose(stream);
    */

/*
    unsigned char *ciphertext = malloc(sizeof(int) * strlen(argv[2]));
    
    //new for convert
    unsigned char *newVal = (malloc(sizeof(int) * (strlen(argv[2]) / 2)));

    //added
    unsigned char S[N];
    unsigned char *plaintext = malloc(sizeof(int) * strlen(argv[2]));

    lengthOfStr = strlen(argv[2]);
    */


    

    unsigned char *ciphertext = malloc(sizeof(int) * fileSize);
    unsigned char *newVal = malloc(sizeof(int) * fileSize);
    unsigned char *plaintext = malloc(sizeof(int) * fileSize);
    unsigned char S[N];
    lengthOfStr = fileSize;

    int printLen;
    int outputStyle;

    if(argc >= 4){
        printLen = fileSize;
        RC4(argv[1], contents, ciphertext, S);
        outputStyle =  1;
    }
    else{
        printLen = fileSize;
        RC4(argv[1], contents, ciphertext, S);
        outputStyle = 0;
    }
    
    size_t i;
    int len;
    printf("Key: %s\n", argv[1]);
    printf("Input Text:  %s\n", argv[2]);
    printf("Output Text: ");
    for(i = 0, len = printLen; i < len; i++) {
        if(outputStyle == 0) {
            printf("%02hhx", ciphertext[i]);
        }
        else if(outputStyle == 1) {
            printf("%c", ciphertext[i]);
        }
    }
    printf("\n");
    printf("%d", len);
    printf("\n");
    
    //Output to file
    //Tweak
    FILE *target;
    target = fopen("encryptedFile.txt", "w");
    fseek(target, 0, SEEK_CUR);
    //fputs(ciphertext, target);
    fwrite(ciphertext, fileSize, 1, target);
    fclose(target);
    
     
    printf("\n");
    return 0;
}
