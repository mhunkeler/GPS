uint16_t getForce(void)
{
    #ifdef active_adc_test
    readADC();
    return fuerzas_m[indexCardF++];
    #else
    return readADC();
    #endif
}

void init_ForceApi(void)
{
    Force_Init();
}

void ApiForce_OFF(void)
{
    Force_OFF();
}
