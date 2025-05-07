#!/bin/bash

#!/bin/bash

# Read array input from user
echo "Enter elements of the array separated by space: "
read -a arr  # Read input as an array

# Declare an associative array to track unique elements
declare -A seen
unique=()

# Loop through array elements
for element in "${arr[@]}"; do
    if [[ -z "${seen[$element]}" ]]; then  # If element is not seen before
        unique+=("$element")  # Add to unique array
        seen[$element]=1  # Mark as seen
    fi
done

# Print the unique elements
echo "Array after removing duplicates: ${unique[@]}"

