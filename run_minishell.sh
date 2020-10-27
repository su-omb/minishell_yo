#!/bin/bash

if [ "$1" == "-c" ];
	then clear
fi

make re
make clean
./minishell


