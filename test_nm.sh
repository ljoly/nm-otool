#!/bin/zsh

GRN="\033[0;32m"
RED="\033[0;31m"
NC="\033[0m"

if [ -f "$nm_fails.txt" ]
    then
    rm nm_fails.txt
fi
for filename in /bin/* /sbin/* /usr/lib/* /usr/bin/* /usr/sbin/*; do
    nm $filename > test_nm &
    ./ft_nm $filename > test_ft_nm &
    wait
    DIFF=$(diff test_nm test_ft_nm)
    if [ "$DIFF" !=  "" ]
        then
        echo "[${RED}ko${NC}] -- $filename"
        echo "$filename" >> nm_fail.txt
        sleep 1
    else
     echo "[${GRN}ok${NC}] -- $filename"
 fi
done
