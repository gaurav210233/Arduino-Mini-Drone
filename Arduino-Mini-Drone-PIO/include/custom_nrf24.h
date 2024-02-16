#ifndef CUSTOM_NRF24
#define CUSTOM_NRF24

#define CE 7
#define CSN 10
#define DRONE_ADDRESS "00001"

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>

class CustomNrf24
{
    public:
        CustomNrf24();
        void begin();     // Method to initialize NRF24 communication
        void receive();   // Method to receive data
        void printData(); // Method to print received data

        // Getter methods to access Joystick data
        int getJoy1_X() const { return data.Joy1_X; }
        int getJoy1_Y() const { return data.Joy1_Y; }
        int getJoy2_X() const { return data.Joy2_X; }
        int getJoy2_Y() const { return data.Joy2_Y; }
        byte getJoy1_SW() const { return data.Joy1_SW; }
        byte getJoy2_SW() const { return data.Joy2_SW; }
        byte getToggle1_SW() const { return data.Toggle1_SW; }
        byte getToggle2_SW() const { return data.Toggle2_SW; }
        byte getSW_A() const { return data.SW_A; }
        byte getSW_B() const { return data.SW_B; }
        byte getSW_C() const { return data.SW_C; }
        byte getSW_D() const { return data.SW_D; }
        int getPot1() const { return data.Pot1; }
        int getPot2() const { return data.Pot2; }
        float getDegX() const { return data.degX; }
        float getDegY() const { return data.degY; }


    private:
        RF24 drone_radio;
        const byte address[6] = DRONE_ADDRESS;
        unsigned long currentReceptionTime;
        unsigned long lastReceivedTime;

        struct stick_position 
        {
            int Joy1_X;
            int Joy1_Y;
            int Joy2_X;
            int Joy2_Y;
            byte Joy1_SW;
            byte Joy2_SW;
            byte Toggle1_SW;
            byte Toggle2_SW;
            byte SW_A;
            byte SW_B;
            byte SW_C;
            byte SW_D;
            int Pot1;
            int Pot2;
            float degX;
            float degY;
        } data;

        void dataReset();
};

#endif // CUSTOM_NRF24