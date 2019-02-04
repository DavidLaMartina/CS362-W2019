#!/bin/bash

line=$(gcov dominion.c -f -b -c | grep -n shuffle | cut -f1 -d:)
((line += 3))
gcov dominion.c -f -b -c | head -n$(echo $line) | tail -n4
