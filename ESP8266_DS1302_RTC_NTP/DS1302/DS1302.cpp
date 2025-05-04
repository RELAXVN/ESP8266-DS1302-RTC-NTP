#include "DS1302.h"

#define DS1302_SEC     0x80
#define DS1302_MIN     0x82
#define DS1302_HOUR    0x84
#define DS1302_DATE    0x86
#define DS1302_MONTH   0x88
#define DS1302_YEAR    0x8C
#define DS1302_CTRL    0x8E
#define DS1302_CHARGER 0x90
#define DS1302_CLK_BURST 0xBE

DS1302::DS1302(uint8_t rst, uint8_t dat, uint8_t clk)
  : _rst(rst), _dat(dat), _clk(clk) {
  pinMode(_rst, OUTPUT);
  pinMode(_clk, OUTPUT);
  pinMode(_dat, OUTPUT);
  digitalWrite(_rst, LOW);
  digitalWrite(_clk, LOW);
}

void DS1302::_writeByte(uint8_t value) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(_dat, (value >> i) & 1);
    digitalWrite(_clk, HIGH);
    delayMicroseconds(1);
    digitalWrite(_clk, LOW);
  }
}

uint8_t DS1302::_readByte() {
  uint8_t value = 0;
  pinMode(_dat, INPUT);
  for (int i = 0; i < 8; i++) {
    value |= (digitalRead(_dat) << i);
    digitalWrite(_clk, HIGH);
    delayMicroseconds(1);
    digitalWrite(_clk, LOW);
  }
  pinMode(_dat, OUTPUT);
  return value;
}

void DS1302::_writeRegister(uint8_t reg, uint8_t value) {
  digitalWrite(_rst, HIGH);
  _writeByte(reg);
  _writeByte(value);
  digitalWrite(_rst, LOW);
}

uint8_t DS1302::_readRegister(uint8_t reg) {
  digitalWrite(_rst, HIGH);
  _writeByte(reg | 0x01);
  uint8_t value = _readByte();
  digitalWrite(_rst, LOW);
  return value;
}

void DS1302::halt(bool enable) {
  uint8_t sec = _readRegister(DS1302_SEC);
  if (enable)
    sec |= 0x80;
  else
    sec &= ~0x80;
  _writeRegister(DS1302_SEC, sec);
}

void DS1302::writeProtect(bool enable) {
  _writeRegister(DS1302_CTRL, enable ? 0x80 : 0x00);
}

void DS1302::setTime(int hour, int min, int sec) {
  _writeRegister(DS1302_SEC, _decToBcd(sec));
  _writeRegister(DS1302_MIN, _decToBcd(min));
  _writeRegister(DS1302_HOUR, _decToBcd(hour));
}

void DS1302::setDate(int date, int month, int year) {
  _writeRegister(DS1302_DATE, _decToBcd(date));
  _writeRegister(DS1302_MONTH, _decToBcd(month));
  _writeRegister(DS1302_YEAR, _decToBcd(year % 100));
}

Time DS1302::getTime() {
  Time t;
  t.sec  = _bcdToDec(_readRegister(DS1302_SEC) & 0x7F);
  t.min  = _bcdToDec(_readRegister(DS1302_MIN));
  t.hour = _bcdToDec(_readRegister(DS1302_HOUR));
  t.date = _bcdToDec(_readRegister(DS1302_DATE));
  t.mon  = _bcdToDec(_readRegister(DS1302_MONTH));
  t.year = 2000 + _bcdToDec(_readRegister(DS1302_YEAR));
  return t;
}

uint8_t DS1302::_decToBcd(uint8_t val) {
  return (val / 10 * 16) + (val % 10);
}

uint8_t DS1302::_bcdToDec(uint8_t val) {
  return (val / 16 * 10) + (val % 16);
}