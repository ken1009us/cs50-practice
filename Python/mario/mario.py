import cs50


def main():
    height = cs50.get_int("Height: ")
    if height <= 8 and height >= 1:
        for i in range(height, 0, -1):
            # create the space
            print(' ' * (i - 1), end="")
            # left half-pyramids, create the hash
            print('#' * (height - i + 1), end="")
            # a gap of size 2
            print('  ', end="")

            # right half-pyramids, create the hash
            print('#' * (height - i + 1))
    else:
        print("The number of height should be an integer which is lower than 9, bigger than 0")
        return(main())


if __name__ == "__main__":
    main()
