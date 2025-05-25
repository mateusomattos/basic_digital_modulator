#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include "datatypes.h"

/**
 * @brief Defines the speed of light in meters per second.
 */
#define C 299792458.0f 

/**
 * @brief Generates random binary bits (0 or 1) and stores them in an array.
 *
 * @param bits_out Pointer to the unsigned int array where the generated bits will be stored.
 * @param num_bits The total number of bits to generate.
 * @return 0 on success, -1 on failure
 */
int gen_bits(unsigned int *bits_out, int num_bits);

/**
 * @brief Groups an array of bits into decimal unsigned integer symbols.
 *
 * @param bits_in Pointer to the input array of unsigned int (0 or 1 values).
 * @param num_bits The total number of bits in the input array.
 * @param group_size The number of bits per group (i.e., bits per symbol).
 * @param symbols_dec Pointer to a pointer where the address of the dynamically
 * allocated array of decimal symbol values will be stored.
 * @return The number of groups (decimal symbols) generated on success, or `0` on error
 */
size_t group_bits_to_decimal(unsigned int *bits_in, size_t num_bits, unsigned int group_size, unsigned int **symbols_dec);

/**
 * @brief Calculates the average signal power of a sequence of IQ samples.
 *
 * @param iq_samples Pointer to the array of ComplexFloat IQ samples.
 * @param num_samples The total number of IQ samples in the array.
 * @return The calculated average signal power as a float. Returns `0.0f` on failure
 */
float get_signal_power(const ComplexFloat *iq_samples, size_t num_samples);


/**
 * @brief Calculates the minimum and maximum values within an array of floats.
 * @param array Pointer to the constant float array to analyze.
 * @param array_size The number of elements in the `array`.
 * @return A `MinMax` structure containing the minimum and maximum values found.
 */
MinMax get_min_max(const float array[], size_t array_size);

#endif // UTILS_H