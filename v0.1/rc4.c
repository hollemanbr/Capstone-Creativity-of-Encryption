/* rc4.C 
   This code, outside of main, retrieved from
   http://cypherpunks.venona.com/archive/1994/09/msg00304.html  */
#include "rc4.h"
#include <stdio.h>
#include <string.h>

int main()
{
   rc4_key key;                                             //initialize a key
   
   char state[256];                                //create a key
   printf("Please enter a key: ");                          //prompt
   scanf("%s", state);                                     //input the key (testing)
   printf("\n");                                            //newline after prompt
   //key.state = (unsigned char *)state;                                       //set the key structs state
   int length = 0;
   length = strlen(state);                                  //set the length of the key
   memcpy(key.state,state, 256);
   printf("Your key is %s, length is %d\n", state, length); //print testing
   
   prepare_key(key.state, length, &key);                   //pass the params to prepare_key
   printf("Your key stream is %hhu\n", key.state);               //print testing
   
   char plntxt[50];                                //create a plaintext message
   printf("Please enter a message to encrypt: ");           //prompt
   scanf("%s", plntxt);                                    //input the plaintext message
   printf("\n");                                            //newline after prompt
   printf("Your message to encrypt is %s\n", plntxt);       //print testing
   int plntxtLen = 0;
   plntxtLen = strlen((char*)plntxt);                              //get the message length
   
   rc4(plntxt, plntxtLen, &key);                           //encrypt the things
   return 0;
}




static void swap_byte(unsigned char *a, unsigned char *b);

void prepare_key(unsigned char *key_data_ptr, int key_data_len,
rc4_key *key)
{
    // unsigned char swapByte;
     unsigned char index1;
     unsigned char index2;
     unsigned char* state;
     short counter;     
     
     state = &key->state[0];         
     for(counter = 0; counter < 256; counter++)              
     state[counter] = counter;               
     key->x = 0;     
     key->y = 0;     
     index1 = 0;     
     index2 = 0;             
     for(counter = 0; counter < 256; counter++)      
     {               
          index2 = (key_data_ptr[index1] + state[counter] +
index2) % 256;                
          swap_byte(&state[counter], &state[index2]);            

          index1 = (index1 + 1) % key_data_len;  
     }       
 }
 
 void rc4(unsigned char *buffer_ptr, int buffer_len, rc4_key
*key)
 { 
     unsigned char x;
     unsigned char y;
     unsigned char* state;
     unsigned char xorIndex;
     short counter;              
     
     x = key->x;     
     y = key->y;     
     
     state = &key->state[0];         
     for(counter = 0; counter < buffer_len; counter ++)      
     {               
          x = (x + 1) % 256;                      
          y = (state[x] + y) % 256;               
          swap_byte(&state[x], &state[y]);                        
               
          xorIndex = state[x] + (state[y]) % 256;                 
               
          buffer_ptr[counter] ^= state[xorIndex];         
      }               
      key->x = x;     
      key->y = y;
 }
 
 static void swap_byte(unsigned char *a, unsigned char *b)
 {
     unsigned char swapByte; 
     
     swapByte = *a; 
     *a = *b;      
     *b = swapByte;
 }

