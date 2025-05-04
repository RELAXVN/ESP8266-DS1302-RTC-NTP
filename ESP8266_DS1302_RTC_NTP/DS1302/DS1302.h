#ifndef DS1302_H
#define DS1302_H

#include <Arduino.h>

struct Time {
  int sec;
  int min;
  int hour;
  int date;
  int mon;
  int year;
};

class DS1302 {
public:
  DS1302(uint8_t rst, uint8_t dat, uint8_t clk);
  void setTime(int hour, int min, int sec);
  void setDate(int date, int month, int year);
  Time getTime();
  void halt(bool enable);
  void writeProtect(bool enable);

private:
  uint8_t _rst, _dat, _clk;
  void _writeByte(uint8_t value);
  uint8_t _readByte();
  void _writeRegister(uint8_t reg, uint8_t value);
  uint8_t _readRegister(uint8_t reg);
  uint8_t _decToBcd(uint8_t val);
  uint8_t _bcdToDec(uint8_t val);
};

#endif