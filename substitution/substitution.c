#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

int validate(char key[]);

int main(int argc, char *argv[])
{
    // Get a single key
    if (argc != 2)
    {
        printf("Usage: ./substitution [key]\n");
        return 1;
    }
    char key[50];
    strcpy(key, argv[1]);

    // Validation tests (+ uppercase)
    if (validate(key) == 1)
    {
        printf("Key must contain 26 characters\n");
        return 1;
    }

    if (validate(key) == 2)
    {
        printf("Key must only contain alphabetic characters\n");
        return 1;
    }

    if (validate(key) == 3)
    {
        printf("Key must not contain repeated characters\n");
        return 1;
    }

    // Input
    printf("plaintext: ");
    char text[50];
    scanf("%s", text);

    // Encipher
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (islower(text[i]) != 0)
        {
            text[i] = tolower(key[text[i] - 97]);
        }
        else if (isupper(text[i]) != 0)
        {
            text[i] = key[text[i] - 65];
        }
    }

    // Output
    printf("ciphertext: %s\n", text);
}

// Functions
int validate(char key[])
{
    int i = 0;
    int j[26] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    // Length check
    if (strlen(key) != 26)
    {
        return 1;
    }

    // Alphabet check
    while (key[i] != '\0')
    {
        if (isalpha(key[i]) == 0)
        {
            return 2;
        }

        // Uppercase
        key[i] = toupper(key[i]);

        // Repetition check
        if (j[key[i] - 65] == true)
        {
            return 3;
        }
        j[key[i] - 65]++;
        i++;
    }

    // Success!
    return 0;
}