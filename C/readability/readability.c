#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int Count_letters(string sentences);

int main(void)
{
    // Get input text from user
    string s = get_string("Text: ");
    int level = Count_letters(s);

    // Print the grade
    if (level < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (level > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        int mid_level = round(level);
        printf("Grade %i\n", mid_level);
    }
}

int Count_letters(string sentences)
{
    int count_letters = 0;
    int count_words = 1;
    int count_sentences = 0;

    // Count the letters, words and sentences
    for (int i = 0, n = strlen(sentences) ; i < n ; i++)
    {
        if (isalpha(sentences[i]))
        {
            count_letters ++;
        }
        else if (isspace(sentences[i]))
        {
            count_words ++;
        }
        else if (sentences[i] == '.' || sentences[i] == '!' || sentences[i] == '?')
        {
            count_sentences ++;
        }
    }

    // Compute and return level for integer
    double AVG_letters = ((float)count_letters / (float)count_words) * 100;
    double AVG_sentences = ((float)count_sentences / (float)count_words) * 100;
    double index = 0.0588 * AVG_letters - 0.296 * AVG_sentences - 15.8;
    int level = round(index);
    return level;
}
