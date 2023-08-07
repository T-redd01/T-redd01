#!/usr/bin/python3
def no_c(my_string):
    for i in my_string:
        if i in "Cc":
            continue
        new_str += i
    return str(new_str)


print(no_c("Best School"))
print(no_c("Chicago"))
print(no_c("C is fun!"))

