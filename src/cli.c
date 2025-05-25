#include "cli.h"
#include <string.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

int config_setup_from_cli(int argc, char **argv, config *config)
{
    int c;

    while (1)
    {
        static struct option long_options[] = {
            //{"input-file", required_argument, 0, 'i'},
            {"modulation", required_argument, 0, 'm'},
            {"sample-rate", required_argument, 0, 'r'},
            {"EbN0", required_argument, 0, 'n'},
            {"channel-distance", required_argument, 0, 'd'},
            {"freq", required_argument, 0, 'f'},
            {"bits", required_argument, 0, 'b'},
            {"sdr", no_argument, 0, 's'},
            {"help", no_argument, 0, 'h'},
            {0, 0, 0, 0}};

        int option_index = 0;

        c = getopt_long(argc, argv, "i:m:r:f:b:n:d:sh", long_options, &option_index);

        if (c == -1)
            break;

        switch (c)
        {

        case 'm':
            config->modulation_type = strdup(optarg);
            printf("Modulation type: `%s`\n", config->modulation_type);
            break;

        case 'r':
            config->sample_rate = atoi(optarg);
            printf("Sample rate: `%f`\n", config->sample_rate);
            break;

        case 'n':
            config->EbN0_snr_db = atof(optarg);
            printf("EbN0 SNR (dB): `%.2f`\n", config->EbN0_snr_db);
            break;

        case 'd':
            config->channel_distance_m = atof(optarg);
            printf("Distance: `%.2f`\n", config->channel_distance_m);
            break;

        case 's':
            config->sdr_transmit_flag = 1;
            printf("SDR transmit mode enabled.\n");
            break;

        case 'f':
            config->freq = atof(optarg);
            printf("Frequency: `%.2f`\n", config->freq);
            break;

        case 'b':
            config->num_bits = atof(optarg);
            printf("Number of Bits: `%ld`\n", config->num_bits);
            break;

        case 'h':
            print_usage();
            exit(0);

        case '?':
            print_usage();
            break;

        default:
            abort();
        }
    }
    return 0;
}

void print_usage()
{
    fprintf(stderr, "\nUsage: ./simulator --input-file <path> --modulation <type> --sample-rate <rate> [OPTIONS]\n");
    fprintf(stderr, "\nOptions:\n");
    fprintf(stderr, "  -m, --modulation <type>         Modulation type (e.g., BPSK, QPSK, 16QAM) (MANDATORY).\n");
    fprintf(stderr, "  -r, --sample-rate <rate>        Sample rate in Hz (MANDATORY).\n");
    fprintf(stderr, "  -f, --freq <frequency>          Carrier frequency in Hz (MANDATORY).\n");                     // Added --freq
    fprintf(stderr, "  -b, --bits <number>             Number of bits to simulate (MANDATORY if no input file).\n"); // Added --bits
    fprintf(stderr, "  -n, --EbN0 <SNR_dB>             Add AWGN. Optionally specify Eb/N0 SNR in dB (e.g., --EbN0=10.0). If no value, a default will be used.\n");
    fprintf(stderr, "  -d, --channel-distance <m>      Simulate channel loss based on distance in meters. If no value, a default distance will be used.\n");
    fprintf(stderr, "  -s, --sdr                       Enable SDR transmit mode.\n");
    fprintf(stderr, "  -h, --help                      Display this help message.\n");
    fprintf(stderr, "\nExample:\n");
    fprintf(stderr, "  ./simulator -b 1000 -m QPSK -r 100000 -f 2.4e9 --EbN0=15.0 -d 500 -s\n");
    fprintf(stderr, "  ./simulator --bits=10000 --modulation=BPSK --sample-rate=200000 --freq=915e6 --EbN0=10.0\n"); // Example using --bits
}
