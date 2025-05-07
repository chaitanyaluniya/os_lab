#!/bin/bash

# Taking input from the user
echo  "Enter base: "
read base
echo  "Enter exponent: "
read exponent

# Calculating power using 'bc' command (since bash doesn't support floating-point arithmetic directly)
result=$(echo "$base ^ $exponent" | bc)

# Displaying the result
echo "Result: $result"

