#!/bin/bash

echo " enter element "
read -a arr

echo " element to be searched "
read ele

for (( i=0;i<${#arr[@]};i++ )); do
if (( arr[i] == ele )); then
echo " ele found at index $i "
break
else
echo " not found "
break
fi
done
