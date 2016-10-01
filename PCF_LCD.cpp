// Library for 1602 LCD's through the PCF 8574

#include "Arduino.h"
#include "PCF_LCD.h"
#include "Wire.h"

PCF_LCD::PCF_LCD() {

};

void PCF_LCD::begin(uint8_t address) {
    this->address = address;

    parWrite(B00100100); // Initiate 4 bit mode

    delayMicroseconds(40);

    parWrite(B00100100); // Function Set 1st 4 bits
    parWrite(B00000100 | ((this->dLines)<<7) | ((this->fType)<<6)); // Function Set 2nd 4 bits

    delayMicroseconds(40);

    parWrite(B00000100); // Display Control 1st 4 bits
    parWrite(B10000100 | ((this->disState)<<6) | ((this->curState)<<5) | ((this->blinkState)<<4)); // Display Control 2nd 4 bits

    delayMicroseconds(40);

    parWrite(B00000100); // Display Clear 1st 4 bits
    parWrite(B00010100); // Display Clear 2nd 4 bits

    delay(2); // Wait longer for display clear function

    parWrite(B00000100); // Entry Mode 1st 4 bits
    parWrite(B00000100 | ((this->incMode)<<5) | ((this->shiftMode)<<4)); // Entry Mode 2nd 4 bits

};

void PCF_LCD::fSet(uint8_t dLines, uint8_t fType, uint8_t disState, uint8_t curState, uint8_t blinkState, uint8_t incMode, uint8_t shiftMode, bool cl) {

    this->dLines = dLines;
    this->fType = fType;
    this->disState = disState;
    this->curState = curState;
    this->blinkState = blinkState;
    this->incMode = incMode;
    this->shiftMode = shiftMode;

    parWrite(B00100100); // Function Set 1st 4 bits
    parWrite(B00000100 | (dLines<<7) | (fType<<6)); // Function Set 2nd 4 bits

    delayMicroseconds(40);

    parWrite(B00000100); // Display Control 1st 4 bits
    parWrite(B10000100 | (disState<<6) | (curState<<5) | (blinkState<<4)); // Display Control 2nd 4 bits

    delayMicroseconds(40);

    if (cl == true) {
        parWrite(B00000100); // Display Clear 1st 4 bits
        parWrite(B00010100); // Display Clear 2nd 4 bits

        delay(2); // Wait longer for display clear function
    }

    parWrite(B00000100); // Entry Mode 1st 4 bits
    parWrite(B00000100 | (incMode<<5) | (shiftMode<<4)); // Entry Mode 2nd 4 bits

};

void PCF_LCD::dShift(uint8_t cMv, uint8_t dSh) {
    
    switch(cMv) {
        case 0:
            switch(dSh) {
                case 0:
                    parWrite(B00010100);
                    parWrite(B00000100);
                    break;
                case 1:
                    parWrite(B00010100);
                    parWrite(B01000100);
                    break;
            }
            break;
        case 1:
            switch(dSh) {
                case 0:
                    parWrite(B00010100);
                    parWrite(B10000100);
                    break;
                case 1:
                    parWrite(B00010100);
                    parWrite(B11000100);
                    break;
            }
            break;
    }

    delayMicroseconds(40);

};

void PCF_LCD::setCursor(uint8_t line, uint8_t character) {

    uint8_t a;
    a = character + (40*(line-1)); // Convert to 1602 DDRAM address in DEC

    parWrite((a&BitMaskFst) | B10000100);
    parWrite(((a&BitMaskLst)<<4) | B00000100);

};

void PCF_LCD::print(String in) {

    uint8_t L = in.length();
    char str[L];
    in.toCharArray(str, L+1);
    for (uint8_t z = 0; z < L; z++) {
        writeDDRAM(str[z]);
    }

};

void PCF_LCD::print(uint8_t in) {

    writeDDRAM(in);

};

void PCF_LCD::clear() {

    parWrite(B00000100);
    parWrite(B00010100);

};

void PCF_LCD::writeDDRAM(uint8_t b) {
    delay(1);

    parWrite((b & BitMaskFst) | B00000101); // First 4 bits
    parWrite(((b & BitMaskLst)<<4) | B00000101); // Last 4 bits

};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Private functions

void PCF_LCD::parWrite(uint8_t b) {

    delayMicroseconds(4);

    Wire.begin(this->address);
    Wire.write(enOn | ((this->ledState)<<3));
    Wire.write(b | ((this->ledState)<<3));
    Wire.write(enOff | ((this->ledState)<<3));
    Wire.endTransmission(true);

};

