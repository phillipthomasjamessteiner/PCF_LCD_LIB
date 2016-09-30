// Library for 1602 LCD's through the PCF 8574

#ifndef PCF_LCD_h
#define PCF_LCD_h

#define enOn    B00000100
#define enOff   B00000000
#define BitMaskFst B11110000
#define BitMaskLst B00001111


class PCF_LCD {

    public:

        PCF_LCD();

        void begin(uint8_t address);

        void fSet(uint8_t fontType, uint8_t inc, uint8_t shift);

        void cShift(uint8_t dir);

        void dShift(uint8_t dir);

        void setCursor(uint8_t line, uint8_t character);

        void print(String in);

        void print(uint8_t in);

        void clear();

        void writeDDRAM(uint8_t b);

    private:

        uint8_t address;

        uint8_t ledState;

        uint8_t dLines;

        uint8_t fType;

        uint8_t disState;

        uint8_t curState;
        
        uint8_t blinkState;

        uint8_t incMode;

        uint8_t shiftMode;

        void parWrite(uint8_t b);

        

};

#endif