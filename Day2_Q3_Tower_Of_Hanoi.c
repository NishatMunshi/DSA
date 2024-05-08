#include <stdio.h>

void towerOfHanoi(int _numberOfDiscs, char const _source, char const _auxiliary, char const _destination)
{
    static unsigned step = 0;
    if (_numberOfDiscs == 1)
    {
        printf("Step %u: %c to %c\n", ++step, _source, _destination);
        return;
    }
    towerOfHanoi(_numberOfDiscs - 1, _source, _destination, _auxiliary);
    towerOfHanoi(1, _source, _auxiliary, _destination);
    towerOfHanoi(_numberOfDiscs - 1, _auxiliary, _source, _destination);
}
int main()
{
    printf("Enter the number of disks: ");
    int numberOFDiscs;
    scanf("%d", &numberOFDiscs);
    towerOfHanoi(numberOFDiscs, 'A', 'B', 'C'); // A, B and C are names of rods

    return 0;
}
