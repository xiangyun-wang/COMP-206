#!/bin/bash

exec 2>/dev/null

if [[ ! -f 'cipher.c' ]] ; then         # find if there is cipher.c
    echo "Error: cipher.c not found!"
    exit 1
fi

gcc -o cipher cipher.c      # compile using gcc

if [[ ! -f 'cipher' ]] ; then           # find if there is cipher
    echo "Error: cipher.c cannot be built!"
    exit 1
fi

# normal test case 1
echo "==========START OF TESTS=========="
echo "==========Normal Test Case 1=========="
echo "Test case 1: key = 8, Option = -e, Input = THISISASECRETMESSAGE"
output=$(./cipher -e 8 THISISASECRETMESSAGE)
ex_code=$?
echo "Expected Output: TEHMSITSSEAIRGSCEAES"
echo "Expected Exit Code: 0"
echo Student Output: $output
echo Student Exit Code: $ex_code

# normal test case 2
echo "==========Normal Test Case 2=========="
echo "Test case 2: key = 3, Option = -e, Input = THISISASECRETMESSAGE"
output=$(./cipher -e 3 THISISASECRETMESSAGE)
ex_code=$?
echo "Expected Output: TIETSHSSSCEMSAEIAREG"
echo "Expected Exit Code: 0"
echo Student Output: $output
echo Student Exit Code: $ex_code

# normal test case 3
echo "==========Normal Test Case 3 (empty input)=========="
echo "Test case 3: key = 3, Option = -e, Input = "
output=$(./cipher -e 3 "")
ex_code=$?
echo "Expected Output: "
echo "Expected Exit Code: 0"
echo Student Output: $output
echo Student Exit Code: $ex_code

# normal test case 4 (with option -d)
echo "==========Normal Test Case 4 (with option -d)=========="
echo "Test case 4: key = 3, Option = -d, Input = THISISASECRETMESSAGE"
output=$(./cipher -d 3 THISISASECRETMESSAGE)
ex_code=$?
echo "Expected Output: "
echo "Expected Exit Code: 0"
echo Student Output: $output
echo Student Exit Code: $ex_code

# Usage test
echo "==========Usage Test Case=========="
echo "Test case 5:  Number of inputs not correct (./cipher)"
output=$(./cipher)
ex_code=$?
echo "Expected Output: Usage : ./cipher [-e|-d] <key> <MESSAGE>"
echo "Expected Exit Code: 1"
echo Student Output: $output
echo Student Exit Code: $ex_code

# invalid key test case
echo "==========Invalid Key Test Case=========="
echo "Test case 6: key = 4.r, Option = -e, Input = HELLOTHERE"
output=$(./cipher -e 4.r HELLOTHERE)
ex_code=$?
echo "Expected Output: Error 4.r is not a valid key"
echo "Expected Exit Code: 1"
echo Student Output: $output
echo Student Exit Code: $ex_code

# invalid option test case
echo "==========Invalid Option Test Case 1=========="
echo "Test case 7: key = 5, Option = -k, Input = HELLOTHERE"
output=$(./cipher -k 5 HELLOTHERE)
ex_code=$?
echo "Expected Output: Error -k is not a valid option"
echo "Expected Exit Code: 1"
echo Student Output: $output
echo Student Exit Code: $ex_code

echo "==========END OF ALL TESTS=========="

rm cipher
