#include <stdio.h>

void tower_of_hanoi(unsigned const numberOfDiscs, char const source, char const auxiliary, char const destination)
{
    static unsigned numberOfSteps = 0;
    if (numberOfDiscs == 1)
    {
        printf("Step %u: %c to %c\n",++numberOfSteps, source, destination);
        return;
    }
    else
    {
        tower_of_hanoi(numberOfDiscs - 1, source, destination, auxiliary);
        tower_of_hanoi(1, source, auxiliary, destination);
        tower_of_hanoi(numberOfDiscs - 1, auxiliary, source, destination);
    }
}