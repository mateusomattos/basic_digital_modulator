#ifndef OUTPUT_H
#define OUTPUT_H

#include <stddef.h>
#include "datatypes.h"

/**
 * @brief Plots the IQ samples and saves the constellation diagram as a PNG image.
 *
 * @param iq_samples Pointer to the array of ComplexFloat IQ samples to be plotted.
 * @param num_samples The total number of IQ samples in the `iq_samples` array.
 * @param output_png_filename The desired full path and filename for the output PNG image
 */
void plot_and_save_png(const ComplexFloat *iq_samples, size_t num_samples, const char *output_png_filename);

/**
 * @brief Saves an array of binary bits to a text file.
 *
 * @param file_path The path to the output text file where the bits will be saved.
 * @param bits_in Pointer to the array of unsigned int bits (0 or 1) to save.
 * @param num_bits The number of bits in the array to write to the file.
 * @return 0 on success, -1 on failure
 */
int save_binary_to_file(const char *file_path, const unsigned int *bits_in, size_t num_bits);

#endif // OUTPUT_H