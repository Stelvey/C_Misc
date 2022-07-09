// Libraries (commenting just to pass style50 at this point)
#include <stdio.h>
#include <ctype.h>
#include <math.h>

// Prototypes
int count_letters(char text[]);
int count_words(char text[]);
int count_sentences(char text[]);

int main(void)
{
    // Input & its analyzation
    printf("Text: ");
    char text[300];
    fgets(text, 300, stdin);
    float letters = count_letters(text);
    float words = count_words(text);
    float sentences = count_sentences(text);

    // Calculations
    float l = letters / words * 100;
    float s = sentences / words * 100;
    int index = round(0.0588 * l - 0.296 * s - 15.8);

    // Output
    if (letters == 0 || words == 1 || sentences == 0)
    {
        printf("Please, type a proper sentence!\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

// Counting letters
int count_letters(char text[])
{
    int j = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]))
        {
            j++;
        }
    }
    return j;
}

// Counting words
int count_words(char text[])
{
    int j = 1;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ')
        {
            j++;
        }
    }
    return j;
}

// Counting sentences
int count_sentences(char text[])
{
    int j = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            j++;
        }
    }
    return j;
}