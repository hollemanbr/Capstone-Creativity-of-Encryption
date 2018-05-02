#!/bin/bash
echo RC4 Plaintext Encryption\n
read -p 'Please enter a key: ' key
echo 
read -p 'Please enter a word or phrase: ' filevar
echo
read -p 'Is this decryption (y for yes or leave blank if no)' decrypt
echo
./rc4Test $key $filevar $decrypt
