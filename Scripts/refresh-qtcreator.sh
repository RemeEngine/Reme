#!/bin/sh

find . \( -name Build -o -name Out -o -name Libraries \) -prune -o \( -name '*.cpp' -or -name '*.h' \) -print > Reme.files
