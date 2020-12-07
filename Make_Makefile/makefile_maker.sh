#!/bin/bash

ls -dl ../srcs/*/*.c | echo -n "$(awk  '{print $NF}')" > source_files
./makefile_maker
# rm -rf source_files
