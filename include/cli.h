#ifndef CLI_H
#define CLI_H


#include "datatypes.h"

/**
 * @brief Parses command-line arguments and populates the application configuration.
 *
 * This function utilizes the `getopt_long` utility to parse command-line options
 * provided by the user. 
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of strings representing the command-line arguments.
 * @param config Pointer to the `config` structure that will be populated with
 * the parsed argument values.
 * @return 0 on successful parsing and configuration.
 */
int config_setup_from_cli(int argc, char **argv, config *config);

/**
 * @brief Prints the command-line usage instructions to stderr.
 *
 * This function displays a detailed help message
 */
void print_usage();

#endif // CLI_H