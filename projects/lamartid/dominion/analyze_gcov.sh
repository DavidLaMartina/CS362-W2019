#!/bin/bash

PATTERN_1=${1?ERROR: no first pattern provided}
PATTERN_2=${2?ERROR: no second pattern provided}

first_line=$(grep -n "$PATTERN_1" dominion.c.gcov | cut -f1 -d:)
last_line=$(grep -n "$PATTERN_2" dominion.c.gcov | cut -f1 -d:)
num_lines=$(expr $last_line - $first_line)
((last_line--))

head -n$(echo $last_line) dominion.c.gcov | tail -n$num_lines
