#!/usr/bin/python3
from sys import argv

if __name__ == '__main__':
    num = len(argv)
    if num == 1:
        print("0 arguments")
    elif num == 2:
        print("1 argument:\n1: {:s}".format(argv[1]))
    else:
        print("{:d} arguments:".format(num - 1))
        for i in range(num):
            if i == 0:
                continue
            print("{:d}: {:s}".format(i, argv[i]))

