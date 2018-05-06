#!/bin/bash
echo Please ensure your file is in the same directory
read -p 'Please enter the file that contains the key: ' filekey
echo
read -p 'Please enter the file that is going to be encrypted/decrypted: ' filedata
echo
read -p 'Decrypt?(y for yes blank if no) ' decrypt
echo
./rc4Test $filekey $filedata $decrypt
