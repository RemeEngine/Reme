#!/bin/sh

find . \( -name Build -o -name Out \) -prune -o \( -name '*.cpp' -or -name '*.h' -or -name '*.txt' -or -name '.md' \) -print > Reme.files
