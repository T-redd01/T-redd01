#!/usr/bin/python3
def replace_in_list(my_list, idx, element):
    if idx < 0:
        return my_list
    if idx > (len(my_list) - 1):
        return my_list
    my_list[idx] = element
    return my_list


my_list = [1, 2, 3, 4, 5]
idx = 5
new_element = 9
new_list = replace_in_list(my_list, idx, new_element)

print(new_list)
print(my_list)
