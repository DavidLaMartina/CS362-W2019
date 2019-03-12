#!/bin/bash

FUNCTION=${1?ERROR: no function provided}

line=$(gcov -f -b dominion.c | grep -n $FUNCTION | cut -f1 -d:)
((line += 3))
gcov -f -b dominion.c | head -n$(echo $line) | tail -n4
