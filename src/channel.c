#include "channel.h"
#include "utils.h"
#include "boxmuller.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>


int add_awgn(ComplexFloat *iq_samples, config *app_config)
{
    if (iq_samples == NULL || app_config->num_symbols == 0)
    {
        fprintf(stderr, "Error in add_awgn: Invalid IQ samples or app_config->num_symbols.\n");
        return -1;
    }

    float gamma = pow(10, app_config->EbN0_snr_db / 10);
    float sig_power = get_signal_power(iq_samples, app_config->num_symbols);
    float N0 = sig_power / gamma;
    float noise_im = 0.0;
    float noise_re = 0.0;
    for (size_t i = 0; i < app_config->num_symbols; i++)
    {
        //noise_im = sqrt(N0 / 2) * ((double)rand() / (double)RAND_MAX);
        //noise_re = sqrt(N0 / 2) * ((double)rand() / (double)RAND_MAX);
        noise_im = sqrt(N0 / 2) * box_muller(0, 1); //Generate random number from a normal distribution (mean = 0, std = 1)
        noise_re = sqrt(N0 / 2) * box_muller(0, 1);

        iq_samples[i].re += noise_re;
        iq_samples[i].im += noise_im;
    }
    return 0;
}

int add_path_loss(ComplexFloat *iq_samples, config *app_config)
{
    if (iq_samples == NULL || app_config->num_symbols == 0)
    {
        fprintf(stderr, "Error in add_path_loss: Invalid IQ samples or app_config->num_symbols.\n");
        return -1;
    }

    if (app_config->freq <= 0.0f)
    {
        fprintf(stderr, "Error in add_path_loss: Distance and carrier frequency must be positive.\n");
        return -1;
    }
    if (app_config->channel_distance_m == 0)
    {
        return 0;
    }
    float path_loss_db = 20.0f * log10f(app_config->channel_distance_m) + 20.0f * log10f(app_config->freq) + 20.0f * log10f(4.0f * M_PI / C);
    float attenuation_factor = powf(10.0f, -path_loss_db / 20.0f);

    for (size_t i = 0; i < app_config->num_symbols; ++i)
    {
        iq_samples[i].re *= attenuation_factor;
        iq_samples[i].im *= attenuation_factor;
    }
    return 0;
}