#define FULL_DMA_BUFFER
#include "I2SClocklessLedDriver.h"
#define ledsperstrip 256
#define numstrips 16
//here we have 3 colors per pixel
//uint8_t leds[numstrips*ledsperstrip*3];
//this one below is same as the one above
uint8_t leds[numstrips*ledsperstrip*3];

int pins[16]={0,2,4,5,12,13,14,15,16,18,19,21,22,23,25,26};

I2SClocklessLedDriver driver;
void setup() {
    Serial.begin(115200);
    
    driver.initled((uint8_t*)leds,pins,numstrips,ledsperstrip,ORDER_GRB);
    driver.setBrightness(10);
    driver.showPixelsFromBuffer(LOOP); //start displaying in  loop what ever is in the DMA buffer
    
}

int off=0;
void loop() {
    for(int j=0;j<numstrips;j++)
    {
        
        for(int i=0;i<ledsperstrip;i++)
        {
            
           driver.setPixelinBuffer((i+off)%256+ledsperstrip*j,255-i,i,((128-i)+255)%255);
            
        }
    }
    off++;
    if(off==500)
    {
      Serial.println("we stop the display loop");
      driver.stopDisplayLoop();
    }
    if(off==1500)
    {
      Serial.println("we restart the display loop");
      driver.showPixelsFromBuffer(LOOP);
    }
}