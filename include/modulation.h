#ifndef MODULATION_H
#define MODULATION_H

#include <stddef.h>
#include "datatypes.h"


/**
 * @brief Declares the global array of supported modulation schemes.
 */
extern const Modulations MODULATION_SCHEMES[];

/**
 * @brief Performs the modulation of binary bits into IQ samples based on application configuration.
 *
 * @param iq_samples_out Pointer to the array where the generated ComplexFloat IQ samples will be stored.
 * @param app_config Pointer to the application's configuration structure.
 * @param bits_in Pointer to the input array of unsigned int bits (0s and 1s) to be modulated.
 * @return The total number of bit modulated, or `0` on error
 */
size_t get_iq_samples(ComplexFloat *iq_samples_out, config *app_config,  unsigned int *bits_in);

/**
 * @brief A generic function to modulate binary bits into IQ samples based on a specific modulation scheme.
 *
 * @param bits_in Pointer to the input array of unsigned int bits (0s and 1s).
 * @param num_bits The total number of bits in the input array.
 * @param iq_samples_out Pointer to the array where the generated ComplexFloat IQ samples will be stored.
 * @param modulation A constant `Modulations` structure detailing the specific modulation
 * parameters (e.g., LUT, bits_per_symbol, num_symbols_in_lut).
 * @return The total number of bit modulated, or `0` on error
 */
size_t generic_modulator(unsigned int *bits_in, size_t num_bits, ComplexFloat *iq_samples_out, const Modulations modulation);

#endif // MODULATION_H