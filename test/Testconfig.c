#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "config.h"
#include "unity.h"
#include "modulation.h"

void setUp() {}
void tearDown() {}

void test_config_create(void)
{
    printf("--- Running test_config_create ---\n");

    config *test_app_config = config_create();
    TEST_ASSERT_NOT_NULL(test_app_config);
    printf("  - Config pointer is not NULL.\n");
    printf("  - Verifying default values...\n");

    TEST_ASSERT_EQUAL_STRING("", test_app_config->input_file);
    printf("    - input_file is correct.\n");

    TEST_ASSERT_EQUAL_STRING("BPSK", test_app_config->modulation_type);
    printf("    - modulation_type is correct.\n");

    TEST_ASSERT_EQUAL_INT(1.0e9, test_app_config->sample_rate);
    printf("    - sample_rate is correct.\n");

    TEST_ASSERT_EQUAL_FLOAT(100.0f, test_app_config->EbN0_snr_db);
    printf("    - noise_snr_db is correct.\n");

    TEST_ASSERT_EQUAL_FLOAT(0.0f, test_app_config->channel_distance_m);
    printf("    - channel_distance_m is correct.\n");

    TEST_ASSERT_EQUAL_INT(0, test_app_config->sdr_transmit_flag);
    printf("    - sdr_transmit_flag is correct.\n");

    free(test_app_config);

}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_config_create);   
    UNITY_END();
    return 0;
}