#!/bin/bash
echo Please ensure your file is in the same directory
read -p 'Enter the key: ' key
echo
read -p 'Please enter a file name: ' filevar
echo
read -p 'Decrypt?(y for yes blank for no) ' decrypt
echo
./rc4Test $key $filevar $decrypt
vim rc4File
