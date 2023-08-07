#!/usr/bin/python3
def print_matrix_integer(matrix=[[]]):
    for i in matrix:
        num = len(i)
        j = 0
        while j < num:
            if j == 0:
                print("{:d}".format(i[j]), end='')
                j += 1
                continue
            print(" {:d}".format(i[j]), end='')
            j += 1
        print()


matrix = [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
]

print_matrix_integer(matrix)
print("--")
print_matrix_integer()

