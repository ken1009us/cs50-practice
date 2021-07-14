import cs50


def main():
    # get input text from user
    text = cs50.get_string("Text: ")
    index = count_letters(text)
    # print the grade
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print("Grade " + str(index))


def count_letters(text):

    alpha_list = []
    count_letters = 0
    count_sentences = 0

    words_list = text.split(' ')
    count_words = len(words_list)

    # count the letters, words and sentences
    for i in text:
        alpha_list.append(i)

    for j in alpha_list:
        if j.isalpha():
            count_letters += 1

        elif j == '.' or j == '?' or j == '!':
            count_sentences += 1

        else:
            continue

    # compute and return level for integer
    L = count_letters / count_words * 100
    S = count_sentences / count_words * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)

    return index


if __name__ == "__main__":
    main()
