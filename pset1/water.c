#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("Minutes: ");
    int mins = get_int();
    int gallons = (mins * 12);
    printf("Gallons: %i\n", gallons);
}