#!/usr/bin/python3
from from_dwnlds import hidden_4
if __name__ == '__main__':
    my_list = []
    for i in dir(hidden_4):
        if i[0] == '_':
            continue
        my_list.append(i)
    my_list = sorted(my_list)
    for i in range(len(my_list)):
        print(my_list[i])

