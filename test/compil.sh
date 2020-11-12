#!/bin/bash

flag="-Werror -Wall -Wextra"
leaks="-fsanitize=address -g3"
# libft="-L../../../libft_extended/ -lftx -I-L../../../libft_extended/libft"

gcc $1 -L../../../libft_extended/ -lftx $flag $leaks
if [ $? = 0 ]
then 
    echo "$1 compilé sous a.out 🔥 nous lançons l'éxécutable : "
    ./a.out
else
    echo le compilation de $1 a échouée 🐵
fi