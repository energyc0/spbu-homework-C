#include <stdio.h>

void count_numbers_freq(int freq[28])
{
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            for (int k = 0; k < 10; k++)
                freq[i + j + k]++;
}

int count_combinations(int freq[28])
{
    int res = 0;
    for (int i = 0; i < 28; i++)
        res += freq[i] * freq[i];
    return res;
}

int main(void) 
{
    int freq[28] = {0};
    count_numbers_freq(freq);
    printf("%d\n", count_combinations(freq));
    return 0;
}