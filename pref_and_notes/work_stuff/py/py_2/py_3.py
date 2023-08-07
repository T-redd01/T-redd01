#!/usr/bin/python3
from sys import argv
if __name__ == '__main__':
    num = 0
    for i in range(len(argv)):
        if i == 0:
            continue
        num += int(argv[i])
    print(num)

