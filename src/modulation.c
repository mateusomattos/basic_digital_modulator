#include "modulation.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>


const ComplexFloat BPSK_LUT[] = {
    {-1.0, 0.}, // 0
    {1.0, 0.0}  // 1
};

const ComplexFloat QPSK_LUT[] = {
    {0.70710678, 0.70710678},  // 00
    {-0.70710678, 0.70710678}, // 01
    {0.70710678, -0.70710678}, // 10
    {-0.70710678, -0.70710678} // 11

};


const ComplexFloat QAM16_LUT[] = {
    {-0.94868329f, -0.94868329f}, // (0000)
    {-0.94868329f, -0.31622777f}, // (0001)
    {-0.31622777f, -0.31622777f}, // (0011)
    {-0.31622777f, -0.94868329f}, // (0010)
    {-0.94868329f,  0.94868329f}, // (0100)
    {-0.94868329f,  0.31622777f}, // (0101)
    {-0.31622777f,  0.31622777f}, // (0111)
    {-0.31622777f,  0.94868329f}, // (0110)
    { 0.31622777f,  0.94868329f}, // (1100)
    { 0.31622777f,  0.31622777f}, // (1101)
    { 0.94868329f,  0.31622777f}, // (1111)
    { 0.94868329f,  0.94868329f}, // (1110)
    { 0.31622777f, -0.94868329f}, // (1000)
    { 0.31622777f, -0.31622777f}, // (1001)
    { 0.94868329f, -0.31622777f}, // (1011)
    { 0.94868329f, -0.94868329f}  // (1010)
};

const Modulations MODULATION_SCHEMES[] = {
    {"BPSK", BPSK_LUT, 1},
    {"QPSK", QPSK_LUT, 2},
    {"16QAM", QAM16_LUT, 4},
    {NULL, NULL, 0}};


size_t generic_modulator(ComplexFloat *iq_samples_out, config *app_config,  unsigned int *bits_in)
{
    if (app_config->num_bits == 0 || bits_in == NULL)
    {
        fprintf(stderr, "Error in bpsk_modulate: Invalid num_bits samples or bits_in.\n");
        return -1;
    }
    unsigned int *out = NULL;
    size_t num_groups;
    num_groups = group_bits_to_decimal(bits_in, app_config->num_bits, app_config->modulation.bits_per_symbol, &out);
    if (!num_groups)
    {
        printf("Error to get the symbols\n");
        return 0;
    }
    for (size_t i = 0; i < num_groups; i++)
    {
        unsigned int symbol = out[i];
        iq_samples_out[i] = app_config->modulation.lut[symbol];
    }

    return num_groups;
}

size_t get_iq_samples(ComplexFloat *iq_samples_out, config *app_config,  unsigned int *bits_in)
{
    return generic_modulator(iq_samples_out, app_config, bits_in);
}