#!/bin/bash

# Function to perform Quick Sort
quick_sort() {
    local arr=("$@")  # Store function arguments as an array
    local left=() right=() pivot

    # Base case: if array has 0 or 1 elements, return it as sorted
    if [ ${#arr[@]} -le 1 ]; then
        echo "${arr[@]}"
        return
    fi

    # Choosing the pivot (first element)
    pivot=${arr[0]}

    # Partitioning: Separate elements into left (smaller) and right (larger)
    for element in "${arr[@]:1}"; do
        if [ "$element" -le "$pivot" ]; then
            left+=("$element")
        else
            right+=("$element")
        fi
    done

    # Recursively sort left and right partitions and merge the results
    echo "$(quick_sort "${left[@]}") $pivot $(quick_sort "${right[@]}")"
}

# Taking user input
echo "Enter space-separated numbers:"
read -a numbers

# Call Quick Sort
sorted_numbers=$(quick_sort "${numbers[@]}")

# Display sorted array
echo "Sorted array: $sorted_numbers"

