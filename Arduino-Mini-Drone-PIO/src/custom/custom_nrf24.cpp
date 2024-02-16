#include "custom_nrf24.h"

CustomNrf24::CustomNrf24() : drone_radio(CE, CSN) {}

void CustomNrf24::dataReset()
{
    data.Joy1_X = 512;
    data.Joy1_Y = 512;
    data.Joy2_X = 512;
    data.Joy2_Y = 512;
    data.Joy1_SW = 1;
    data.Joy2_SW = 1;
    data.Toggle1_SW =1;
    data.Toggle2_SW =1;
    data.SW_A = 1;
    data.SW_B = 1;
    data.SW_C = 1;
    data.SW_D = 1;
    data.Pot1 = 0;
    data.Pot2 = 0;
    data.degX = 0;
    data.degY = 0;
}

void CustomNrf24::begin()
{
    drone_radio.begin();
    drone_radio.openReadingPipe(0, address);
    drone_radio.setPALevel(RF24_PA_MIN);
    drone_radio.startListening();
    dataReset();
}

void CustomNrf24::receive()
{
    // check if there is received data
    if(drone_radio.available())
    {
        drone_radio.read(&data, sizeof(stick_position));
        lastReceivedTime = millis();
    }

    // Disconnected if more than 1 second since last data received.
    // Move all switch positions to neutral
    currentReceptionTime = millis();
    if( currentReceptionTime - lastReceivedTime > 1000)
    {
        dataReset();
    }
}

void CustomNrf24::printData()
{
    // Show all switch positions on serial monitor
    Serial.print("Joy1-X: ");
    Serial.print(data.Joy1_X);
    Serial.print(" Joy1-Y: ");
    Serial.print(data.Joy1_Y);
    Serial.print(" Joy2-X: ");
    Serial.print(data.Joy2_X);
    Serial.print(" Joy2-Y: ");
    Serial.print(data.Joy2_Y);
    Serial.print(" Joy1_SW: ");
    Serial.print(data.Joy1_SW);
    Serial.print(" Joy2_SW: ");
    Serial.print(data.Joy2_SW);
    Serial.print(" Pot1: ");
    Serial.print(data.Pot1);
    Serial.print(" Pot2: ");
    Serial.print(data.Pot2);
    Serial.print(" Toggle1: ");
    Serial.print(data.Toggle1_SW);
    Serial.print(" Toggle2: ");
    Serial.print(data.Toggle2_SW);
    Serial.print(" SW_A: ");
    Serial.print(data.SW_A);
    Serial.print(" SW_B: ");
    Serial.print(data.SW_B);
    Serial.print(" SW_C: ");
    Serial.print(data.SW_C);
    Serial.print(" SW_D: ");
    Serial.print(data.SW_D);
    Serial.print(" X_angle: ");
    Serial.print(data.degX);
    Serial.print(" Y_angle: ");
    Serial.println(data.degY);
}