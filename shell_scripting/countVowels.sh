#!/bin/bash 

echo " enter the string "
read string
vowel_count=$(echo "$string" | grep -o -i '[aeiouAEIOU]' | wc -l)
echo "vowel count = $vowel_count"
