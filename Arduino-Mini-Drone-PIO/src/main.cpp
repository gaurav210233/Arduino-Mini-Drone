#define TEST_ENABLED 0

#if TEST_ENABLED
  #define TEST_NRF24_ENABLED 1
  #define TEST_MPU9250_ENABLED 1
  // #define TEST_CMOTORS_ENABLED 0
#endif


#include <Arduino.h>
#include "custom_nrf24.h"
#include "custom_mpu9250.h"

CustomNrf24 nrf;

void setup()
{
  Serial.begin(115200);
  #if TEST_ENABLED
    #if TEST_NRF24_ENABLED
      nrf.begin();
    #endif
  #endif 
}

void loop()
{
  #if TEST_ENABLED
    test();
  #endif
}

#if TEST_ENABLED
  void test()
  {
    #if TEST_NRF24_ENABLED
      testNrf24();
    #endif

    #if TEST_MPU9250_ENABLED

    #endif
  }
#endif

#if TEST_NRF24_ENABLED
  void testNrf24()
  {
    nrf.receive();
    nrf.printData();
    delay(100); // Adjust delay as needed
  }
#endif