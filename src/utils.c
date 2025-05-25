#include "utils.h"
#include "output.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

size_t group_bits_to_decimal(unsigned int *bits_in, size_t num_bits,
                             unsigned int group_size, unsigned int **symbols_dec)
{

    if (bits_in == NULL || symbols_dec == NULL || group_size == 0)
    {
        fprintf(stderr, "Error: Invalid arguments (bits_in, symbols_dec cannot be NULL, group_size cannot be 0).\n");
        return 0;
    }

    if (num_bits % group_size != 0)
    {
        fprintf(stderr, "Error: Total number of bits (%zu) is not a multiple of group size (%u).\n", num_bits, group_size);
        return 0;
    }

    size_t num_groups = num_bits / group_size;
    *symbols_dec = (unsigned int *)malloc(num_groups * sizeof(unsigned int));
    if (*symbols_dec == NULL)
    {
        fprintf(stderr, "Error: Failed to allocate memory for decimal symbols.\n");
        return 0;
    }

    for (size_t i = 0; i < num_groups; ++i)
    {
        unsigned int current_decimal_value = 0;
        size_t group_start_index = i * group_size;
        for (unsigned int j = 0; j < group_size; ++j)
        {
            current_decimal_value = (current_decimal_value << 1) | bits_in[group_start_index + j];
        }
        (*symbols_dec)[i] = current_decimal_value;
    }

    return num_groups;
}

int gen_bits(unsigned int *binary_array, int num_bits)
{
    if (binary_array == NULL || num_bits == 0)
    {
        fprintf(stderr, "Error: Invalid arguments (binary_array cannot be NULL, num_bits cannot be 0).\n");
        return -1;
    }

    srand((unsigned int)time(NULL));
    for (int i = 0; i < num_bits; i++)
    {
        binary_array[i] = rand() % 2;
    }

    save_binary_to_file("data/generated_bits.txt", binary_array, num_bits);
    return 0;
}

float get_signal_power(const ComplexFloat *iq_samples, size_t num_samples)
{
    if (iq_samples == NULL || num_samples == 0)
    {
        fprintf(stderr, "Error: Invalid arguments (iq_samples cannot be NULL, num_samples cannot be 0).\n");
        return 0.0f;
    }
    double sum_of_squares = 0.0;

    if (iq_samples == NULL || num_samples == 0)
    {
        return 0.0f;
    }

    for (size_t i = 0; i < num_samples; i++)
    {
        sum_of_squares += pow(iq_samples[i].re, 2);
        sum_of_squares += pow(iq_samples[i].im, 2);
    }

    return (float)(sum_of_squares / num_samples);
}

MinMax get_min_max(const float array[], size_t array_size)
{
    MinMax min_max_values; 

    min_max_values.min = array[0];
    min_max_values.max = array[0];    
    for (size_t i = 1; i < array_size; i++)
    {
        if (array[i] > min_max_values.max)
        {
            min_max_values.max = array[i];
        }
        if (array[i] < min_max_values.min)
        {
            min_max_values.min = array[i];
        }
    }

    return min_max_values;
}