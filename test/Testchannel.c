#include "unity.h"
#include "channel.h"
#include "utils.h"
#include <stdlib.h>
#include "config.h"

void setUp() {}
void tearDown() {}

void awgn_test()
{
    ComplexFloat *iq_samples = (ComplexFloat *)malloc(sizeof(ComplexFloat));
    iq_samples[0].re = -1.0f;
    iq_samples[0].im = 0.0f;
    config *app_config = config_create();
    app_config->EbN0_snr_db = 10.0;
    app_config->num_symbols = 1;

    int awgn = add_awgn(iq_samples, app_config);
    printf("Original IQ: (%.4f, %.4f)\n", -1.0f, 0.0f);
    printf("Noisy IQ: (%.4f, %.4f)\n", iq_samples[0].re, iq_samples[0].im);

    TEST_ASSERT_NOT_EQUAL_FLOAT(-1.0f, iq_samples[0].re);
    TEST_ASSERT_NOT_EQUAL_FLOAT(0.0f, iq_samples[0].im);

    free(iq_samples);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(awgn_test);   
    UNITY_END();
    
    return 0;   
}