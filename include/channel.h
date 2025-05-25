#ifndef CHANNEL_H
#define CHANNEL_H

#include "datatypes.h"
#include <stddef.h>

/**
 * @brief Adds Additive White Gaussian Noise (AWGN) to IQ samples based on configuration.
 *
 * This function simulates the addition of noise to the signal, a common effect in
 * communication channels. Noise is added based on the Eb/N0 value and total number
 * of bits specified within the application configuration.
 * TODO: create a normal distribution for the noise!
 *
 * @param iq_samples Pointer to the array of ComplexFloat IQ samples to which noise will be added.
 * @param app_config Pointer to the application's configuration structure. 
 * @return 0 on success, -1 on failure (e.g., null pointer for `iq_samples` or `app_config`, or invalid `num_iq_samples`).
 */
int add_awgn(ComplexFloat *iq_samples, config *app_config);

/**
 * @brief Applies Free-Space Path Loss (FSPL) attenuation to IQ samples based on configuration.
 *
 * This function attenuates the amplitude of IQ samples based on the channel distance
 * and carrier frequency specified in the application configuration, using the Free-Space
 * Path Loss model.
 *
 * @param iq_samples Pointer to the array of ComplexFloat IQ samples to be attenuated.
 * @param app_config Pointer to the application's configuration structure.
 * @return 0 on success, -1 on failure (e.g., null pointer for `iq_samples` or `app_config`,
 * invalid `num_iq_samples`, or non-positive distance/frequency).
 */
int add_path_loss(ComplexFloat *iq_samples, config *app_config);

#endif // CHANNEL_H