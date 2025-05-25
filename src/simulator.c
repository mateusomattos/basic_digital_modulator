#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "modulation.h"
#include "channel.h"
#include "output.h"
#include "utils.h"
#include "cli.h"
#include "config.h"

int main(int argc, char **argv)
{
    config *app_config = NULL;
    unsigned int *binary_data = NULL;
    struct ComplexFloat *iq_samples = NULL;
    int ret_code = EXIT_SUCCESS;

    app_config = config_create();
    if (!app_config)
    {
        printf("Failed to create config\n");
        ret_code = EXIT_FAILURE;
        goto cleanup;
    }

    if (config_setup_from_cli(argc, argv, app_config))
    {
        printf("Failed to parse the provided command-line arguments\n");
        ret_code = EXIT_FAILURE;
        goto cleanup;
    }

    if (complete_config(app_config))
    {
        printf("Failed to complete config\n");
        ret_code = EXIT_FAILURE;
        goto cleanup;
    }

    get_sumarry_config(app_config);

    iq_samples = (ComplexFloat *)malloc(app_config->num_symbols * sizeof(ComplexFloat));
    binary_data = (unsigned int *)malloc(app_config->num_bits * sizeof(unsigned int));

    if (gen_bits(binary_data, app_config->num_bits))
    {
        printf("Error to generate bits\n");
        ret_code = EXIT_FAILURE;
        goto cleanup;
    }

    if (get_iq_samples(iq_samples, app_config, binary_data) != app_config->num_symbols)
    {
        printf("Error to modulate\n");
        ret_code = EXIT_FAILURE;
        goto cleanup;
    }

    if (add_path_loss(iq_samples, app_config))
    {
        printf("Error to add loss\n");
        ret_code = EXIT_FAILURE;
        goto cleanup;
    }

    if (add_awgn(iq_samples, app_config))
    {
        printf("Error to add awgn\n");
        ret_code = EXIT_FAILURE;
        goto cleanup;
    }

    plot_and_save_png(iq_samples, app_config->num_symbols, "constalation.png");

cleanup:
    if (app_config)
        free(app_config);
    if (binary_data)
        free(binary_data);
    if (iq_samples)
        free(iq_samples);
    return ret_code;
}
