#include <stdio.h>

//Variables
int height;
int j = 1;

void bricks()
{
    for (int i = j - 1; i >= 0; i--)
    {
        printf("#");
    }
}

int main(void)
{
    //Input height
    do
    {
        printf("Height: ");
        scanf("%i", &height);
    }
    while (height < 1 || height > 8);

    //Generating ASCII
    while (height != 0)
    {
        //Draw spaces
        for (int i = height - 1; i != 0; i--)
        {
            printf(" ");
        }

        //Draw bricks
        bricks();

        //Draw gap
        for (int i = 0; i < 2; i++)
        {
            printf(" ");
        }

        //Draw bricks again
        bricks();

        //Start a new row
        printf("\n");
        height--;
        j++;
    }
}