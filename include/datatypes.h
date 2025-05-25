#ifndef MY_DATATYPES_H
#define MY_DATATYPES_H

#include <stddef.h>

/**
 * @brief Represents a complex number with single-precision floating-point components.
 */
typedef struct ComplexFloat
{
    float re;
    float im;
} ComplexFloat;

/**
 * @brief Describes a specific modulation scheme.
 */
typedef struct Modulations {
    const char *name;
    const ComplexFloat *lut;
    unsigned int bits_per_symbol;
} Modulations;


/**
 * @brief Holds the application's configuration parameters parsed from command-line arguments.
 */
typedef struct config
{
    char *input_file;
    char *modulation_type;
    float sample_rate;
    float EbN0_snr_db;
    float channel_distance_m;
    int sdr_transmit_flag;
    float freq;
    size_t num_bits;
    size_t num_symbols;
    Modulations modulation;

} config;


/**
 * @brief Represents a pair of minimum and maximum floating-point values.
 *
 * This structure is typically used to store the range (min and max) of a set of data points,
 * useful for scaling plots or validating data ranges.
 */
typedef struct MinMax
{
    float min;
    float max;
} MinMax;

#endif // MY_DATATYPES_H