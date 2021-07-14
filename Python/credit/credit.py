import cs50


# main function
def main():
    # get the number from user
    number = cs50.get_string('Number: ')

    # append the each number to the list and reverse the number list
    re_number_list = []
    for i in number:
        re_number_list.append(i)
    re_number_list.reverse()

    sum_x = 0
    sum_y = 0
    number_product = 0
    tmp_product = []
    final_product = []
    for i in range(1, len(re_number_list), 2):
        number_product = int(re_number_list[i]) * 2
        tmp_product.append(number_product)

    for k in tmp_product:
        if k > 9:
            num_tenth = int(k / 10)
            num_digit = k % 10
            final_product.append(num_tenth)
            final_product.append(num_digit)
        else:
            final_product.append(k)

    # sum of the number’s second-to-last digit
    for n in final_product:
        sum_x += n

    # sum digits that weren’t multiplied by 2
    for j in range(0, len(re_number_list), 2):
        sum_y += int(re_number_list[j])

    number_list = []
    for i in number:
        number_list.append(i)

    start_digit_a = int(number_list[0])
    start_digit_b = int(number_list[0] + number_list[1])

    # validating credit card numbers
    if (sum_x + sum_y) % 10 == 0:
        if start_digit_a == 4 and (len(number) == 13 or len(number) == 16):
            print('VISA')

        elif len(number) == 15 and (start_digit_b == 37 or start_digit_b == 34):
            print('AMEX')

        elif start_digit_a != 4 and len(number) == 16:
            if start_digit_b >= 51 and start_digit_b <= 55:
                print('MASTERCARD')
            else:
                print('INVALID')
        else:
            print('INVALID')

    else:
        print('INVALID')


if __name__ == "__main__":
    main()
