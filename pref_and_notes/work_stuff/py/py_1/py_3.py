#!/usr/bin/python3
for i in range(97, 123):
    if chr(i) in "qe":
        continue
    print("{:s}".format(chr(i)), end='')

