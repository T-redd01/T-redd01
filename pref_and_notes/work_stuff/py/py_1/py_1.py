#!/usr/bin/python3
import random
number = random.randint(-10000, 10000)
rand_num = 0
if number < 0:
    rand_num = number % -10
else:
    rand_num = number % 10

if rand_num > 5:
    print("The last digit of {:d} is {:d} and is greater than 5".format(number, rand_num))
elif rand_num < 6 and rand_num != 0:
    print("The last digit of {:d} is {:d} and is less than 6".format(number, rand_num))
else:
    print("The last digit of {:d} is {:d} and is 0".format(number , rand_num))

