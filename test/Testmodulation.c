#include "unity.h"
#include "modulation.h"
#include "utils.h"
#include "config.h"
#include <stdlib.h>

void setUp() {}
void tearDown() {}

void bpsk_modulator_test()
{
    config *app_config = config_create();
    app_config->modulation_type = "BPSK";
    app_config->num_bits = 2;
    complete_config(app_config);

    ComplexFloat *iq_samples = NULL;

    iq_samples = (ComplexFloat *)malloc(app_config->num_bits * sizeof(ComplexFloat));
    unsigned int bits[] = {0, 1};


    TEST_ASSERT_NOT_NULL(iq_samples);    

    size_t num_symbols =  get_iq_samples(iq_samples, app_config, bits);
    TEST_ASSERT_EQUAL_INT(app_config->num_symbols, num_symbols);

    printf("First bit:\n");
    TEST_ASSERT_EQUAL_FLOAT(-1.0f, iq_samples[0].re);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, iq_samples[0].im);

    printf("Second bit:\n");
    TEST_ASSERT_EQUAL_FLOAT(1.0f, iq_samples[1].re);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, iq_samples[1].im);

    free(iq_samples);
}

void qpsk_modulator_test()
{
    config *app_config = config_create();
    app_config->modulation_type = "QPSK";
    app_config->num_bits = 8;
    complete_config(app_config);

    ComplexFloat *iq_samples = NULL;
    iq_samples = (ComplexFloat *)malloc(app_config->num_bits * sizeof(ComplexFloat));
    TEST_ASSERT_NOT_NULL(iq_samples); 

    unsigned int bits[] = {0, 1, 1, 0, 0, 0, 1, 1}; //symbols: 1, 2, 0, 3


    size_t num_symbols =  get_iq_samples(iq_samples, app_config, bits);
    TEST_ASSERT_EQUAL_INT(app_config->num_symbols, num_symbols);

    printf("1# symbol:\n");
    TEST_ASSERT_EQUAL_FLOAT(-0.70710678, iq_samples[0].re);
    TEST_ASSERT_EQUAL_FLOAT(0.70710678, iq_samples[0].im);

    printf("2# symbol:\n");
    TEST_ASSERT_EQUAL_FLOAT(0.70710678, iq_samples[1].re);
    TEST_ASSERT_EQUAL_FLOAT(-0.70710678, iq_samples[1].im);
    
    printf("3# symbol:\n");
    TEST_ASSERT_EQUAL_FLOAT(0.70710678, iq_samples[2].re);
    TEST_ASSERT_EQUAL_FLOAT(0.70710678, iq_samples[2].im);

    printf("4# symbol:\n");
    TEST_ASSERT_EQUAL_FLOAT(-0.70710678, iq_samples[3].re);
    TEST_ASSERT_EQUAL_FLOAT(-0.70710678, iq_samples[3].im);

    free(iq_samples);
}

void qam16_modulator_test()
{
    //TODO
}

int main(void)
{
    UNITY_BEGIN();
    
    RUN_TEST(bpsk_modulator_test);
    RUN_TEST(qpsk_modulator_test);
    //RUN_TEST(qam16_modulator_test);
    
    UNITY_END();
    
    return 0;   
}