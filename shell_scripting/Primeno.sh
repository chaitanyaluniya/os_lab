#!/bin/bash

echo "enter the no"
read num


is_prime() {
    local n=$1
    if [ "$n" -lt 2 ]; then
        echo "Not a prime number"
        return
    fi
    for ((i=2; i*i<=n; i++)); do
        if [ $((n % i)) -eq 0 ]; then
            echo "Not a prime number"
            return
        fi
    done
    echo "Prime number"
}

prime_result=$(is_prime "$num")
echo "Prime check result: $prime_result"

