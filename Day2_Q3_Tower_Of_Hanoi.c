#include <stdio.h>

void towerOfHanoi(int n, char from_rod, char aux_rod, char to_rod, int newCall)
{
    static unsigned step = 0;
    if (newCall)
        step = 0;
    if (n == 1)
    {
        printf("Step %u: %c to %c\n", ++step, from_rod, to_rod);
        return;
    }
    towerOfHanoi(n - 1, from_rod, to_rod, aux_rod, 0);
    towerOfHanoi(1, from_rod, aux_rod, to_rod, 0);
    towerOfHanoi(n - 1, aux_rod, from_rod, to_rod, 0);
}
int main()
{
    int i, testCases, n;
    printf("Enter the number of disks: ");
    scanf("%d", &n);
    towerOfHanoi(n, 'A', 'B', 'C', 1); // A, B and C are names of rods
    return 0;
}
