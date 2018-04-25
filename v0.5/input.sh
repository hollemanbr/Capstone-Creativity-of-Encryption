#!/bin/bash
echo Please ensure your file is in the same directory
read -p 'Please enter a file name: ' filevar
cp $filevar $filevar.txt
rc4Test Key $filevar.txt
