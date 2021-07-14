#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// set the number and ahphabet
int N = 26;
string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

bool check_code(string code);

int main(int argc, string argv[])
{
    // check if the user cooperates
    if (argc == 2)
    {
        string code = argv[1];
        if (check_code(code) == true)
        {
            // make user input a key
            string text = get_string("plaintext: ");
            char ciphertext[strlen(text) + 1];
            // encipher
            for (int p = 0 ; p < strlen(text) ; p++)
            {
                if (isupper(text[p]))
                {
                    for (int q = 0 ; q < N ; q++)
                    {
                        if (text[p] == alpha[q])
                        {
                            ciphertext[p] = toupper(argv[1][q]);
                            break;
                        }
                    }
                }
                else if (islower(text[p]))
                {
                    for (int q = 0 ; q < N ; q++)
                    {
                        if (text[p] == tolower(alpha[q]))
                        {
                            ciphertext[p] = tolower(argv[1][q]);
                            break;
                        }
                    }
                }
                else
                {
                    ciphertext[p] = text[p];
                }
            }
            ciphertext[strlen(text)] = '\0';
            printf("ciphertext: %s\n", ciphertext);
            return 0;
        }
        else
        {
            printf("Key must contain 26 characters and cannot be repeated.\n");
            return 1;
        }
    }
    else
    {
        printf("Error. Please provide the correct key.\n");
        return 1;
    }
}

bool check_code(string code)
{
    int check = 0;
    // check the key length
    if (strlen(code) == 26)
    {
        for (int i = 0 ; i < 25 ; i++)
        {
            // check the non-alphabetic characters
            if (isalpha(code[i]))
            {
                for (int j = i + 1 ; j <= 25 ; j ++)
                {
                    // check for repeated characters
                    if (code[i] == code[j])
                    {
                        return false;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
            else
            {
                return false;
            }
            check ++;
        }
    }
    else
    {
        return false;
    }

    // validate and return the result
    if (check == 25)
    {
        return true;
    }
    else
    {
        return false;
    }
}