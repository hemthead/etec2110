# Name: John Reed
# Class.Section: etec2110-01 Systems Programming
# Lab_Part: 2_II C Language Performance & the Collatz Conjecture

import time

def collatz_length(number: int):
    len = 0

    if number <= 0: return -1

    while (number != 1):
        if number % 2 == 0:
            number = number // 2
        else:
            number = 3*number + 1

        len += 1

    return len

def collatz_print_sequence(number: int):
    if number <= 0:
        print(f'Error: {number} <= 0, the Collatz Conjecture only applies to positive integers.')
        return

    print(f'{number}: {number}', end="")
    while (number != 1):
        if number % 2 == 0:
            number = number // 2
        else:
            number = 3*number + 1

        print(f', {number}', end="")

    print("")

def main():
    time_start = time.monotonic()

    max_len = 0
    longest_num = 0

    for i in range(1, 1000000+1):
        i_len = collatz_length(i)
        if i_len > max_len:
            max_len = i_len
            longest_num = i

    collatz_print_sequence(longest_num)

    time_taken = time.monotonic() - time_start 

    print(f'time taken: {time_taken}')

if __name__ == "__main__":
    main()
