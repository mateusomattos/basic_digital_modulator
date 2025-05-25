#include "config.h"
#include "modulation.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


struct config *config_create(void)
{
    config *app_config = (config *)malloc(sizeof(struct config));

    if (!app_config)
        return NULL;

    app_config->input_file = "";
    app_config->modulation_type = "BPSK";
    app_config->sample_rate = 1.0e9;
    app_config->EbN0_snr_db = 100.0;
    app_config->channel_distance_m = 0;
    app_config->sdr_transmit_flag = 0;
    app_config->freq = 1.0e9;
    app_config->num_bits = 100;

    return app_config;
}

int complete_config(config *app_config)
{
    for (size_t i = 0; MODULATION_SCHEMES[i].name != NULL; ++i)
    {
        if (!strcmp(app_config->modulation_type, MODULATION_SCHEMES[i].name))
        {
            app_config->modulation = MODULATION_SCHEMES[i];
            break;
        }
    }

    app_config->num_symbols = app_config->num_bits/app_config->modulation.bits_per_symbol;
    return 0;
}

void get_sumarry_config(config *app_config)
{
    printf("\n--- Summary of Parsed Arguments ---\n");
    printf("Input File: %s\n", app_config->input_file);
    printf("Modulation Type: %s\n", app_config->modulation_type);
    printf("Sample Rate: %f Hz\n", app_config->sample_rate);
    printf("Noise SNR: %.2f dB\n", app_config->EbN0_snr_db);
    printf("Channel Distance: %.2f m\n", app_config->channel_distance_m);
    printf("SDR Transmit: %s\n", app_config->sdr_transmit_flag ? "Enabled" : "Disabled");
    printf("Frequncy: %.2f Hz\n", app_config->freq);
    printf("Number of bits: %ld\n", app_config->num_bits);
    printf("-----------------------------------\n\n");
}