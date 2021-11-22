#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    int cp = 4;
    cp--;
    int arrplayer[4] = {0, 1, 2, 3};
    int choice[3];
    int j = 0;
    for (int i = 0; i < 4; i++)
    {
        if (cp != arrplayer[i])
        {
            choice[j] = arrplayer[i];
            j++;
        }
    }
    for (int i = 0; i < 3; i++)
    {
        printf("%d\n", choice[i]);
    }
}