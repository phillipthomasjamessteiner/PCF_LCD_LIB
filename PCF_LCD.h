// Library for 1602 LCD's through the PCF 8574

#ifndef PCF_LCD_h
#define PCF_LCD_h

class PCF_LCD {

    public:

        void begin(uint8_t address);

        void fSet(uint8_t fontType, uint8_t inc, uint8_t shift);

        void cShift(uint8_t dir);

        void dShift(uint8_t dir);

        void setCursor(uint8_t line, uint8_t character);

        void print(String in);

        void print(uint8_t in);

        void clear();

    private:

        void parWrite(uint8_t b);

        void writeDDRAM(uint8_t data);

}