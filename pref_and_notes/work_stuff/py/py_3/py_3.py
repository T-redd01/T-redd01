#!/usr/bin/python3
def print_reversed_list_integer(my_list=[]):
    i = (len(my_list) - 1)
    while (i != -1):
        print("{:d}".format(my_list[i]))
        i -= 1


my_list = [1, 2, 3, 4, 5]
print_reversed_list_integer(my_list)

