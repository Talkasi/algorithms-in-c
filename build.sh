#!/bin/bash

gcc -std=c99 -I./Sort -Wall -Werror -Wpedantic Tests/main.c Sort/sort.c -o app.exe -g3