#ifndef CONFIG_H
#define CONFIG_H

#include "datatypes.h"

/**
 * @brief Creates and initializes a new configuration structure with default values.
 *
 * This function dynamically allocates memory for a `config` structure and
 * sets its fields to reasonable default values.
 *
 * @return A pointer to the newly created and initialized `config` structure
 */
struct config *config_create(void);

/**
 * @brief Completes the application configuration by resolving the modulation scheme and calculating derived parameters.
 *
 * This function takes a partially populated `config` structure
 * and completes its setup.
 *
 * @param app_config Pointer to the application's configuration structure to be completed.
 * @return 0 on success, -1 on failure
 */
int complete_config(config *app_config);

/**
 * @brief Prints a summary of the application's configuration parameters to the console.
 * @param app_config Pointer to the application's configuration structure.
 */
void get_sumarry_config(config *app_config);

#endif // CONFIG_H