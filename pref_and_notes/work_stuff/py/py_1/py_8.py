#!/usr/bin/python3
def uppercase(str):
    new_str = ''
    low_char = "abcdefghijklmnopqrstuvwxyz"
    for i in str:
        if i in low_char:
            new_str += chr(ord(i) - 32)
            continue
        new_str += i
    print("{:s}".format(new_str))

