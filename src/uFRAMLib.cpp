/**
 * \mainpage
 * \brief I2C FRAM library. (Based on model FM24CL16 [RANTRON] and ESP32)
 * @version 1.0.0
 *
 * This library controls I2C specific FRAM and is not compatible with regular 24Cxx EEPROM.
 *
 * Based on uEEPROMLib Library:
 * @see <a href="https://github.com/Naguissa/uEEPROMLib">https://github.com/Naguissa/uEEPROMLib</a>
 * @see <a href="https://www.foroelectro.net/librerias-arduino-ide-f29/ueepromlib-arduino-libreria-simple-y-eficaz-para-e-t225.html">https://www.foroelectro.net/librerias-arduino-ide-f29/ueepromlib-arduino-libreria-simple-y-eficaz-para-e-t225.html</a>
 * @see <a href="mailto:naguissa@foroelectro.net">naguissa@foroelectro.net</a>
 * @see <a href="https://github.com/Naguissa/uRTCLib">https://github.com/Naguissa/uRTCLib</a>
 */

#include "Arduino.h"
	#ifndef UFRAMLIB_WIRE
		#if defined(ARDUINO_attiny) || defined(ARDUINO_AVR_ATTINYX4) || defined(ARDUINO_AVR_ATTINYX5) || defined(ARDUINO_AVR_ATTINYX7) || defined(ARDUINO_AVR_ATTINYX8) || defined(ARDUINO_AVR_ATTINYX61) || defined(ARDUINO_AVR_ATTINY43) || defined(ARDUINO_AVR_ATTINY828) || defined(ARDUINO_AVR_ATTINY1634) || defined(ARDUINO_AVR_ATTINYX313)
			#include <TinyWireM.h>                  // I2C Master lib for ATTinys which use USI
			#define UFRAMLIB_WIRE TinyWireM
		#else
			#include <Wire.h>
			#define UFRAMLIB_WIRE Wire
		#endif
	#endif
#include "uFRAMLib.h"

/**
 * \brief Constructor
 */
uFRAMLib::uFRAMLib() { }

/**
 * \brief Constructor
 *
 * @param foo: false
 */
uFRAMLib::uFRAMLib(bool foo) {
}

/**
 * \brief Read one byte
 *
 * @param address Address inside FRAM to read from
 * @return read byte
 */
byte uFRAMLib::fram_read(unsigned int address) {
	UFRAMLIB_YIELD
	byte rdata = 0xFF;
	int _fram_address = FRAM_ADDR + ((address >> 8) & 0x7);

	UFRAMLIB_WIRE.beginTransmission(_fram_address);
	UFRAMLIB_WIRE.write((int)(address & 0xFF)); // LSB
	if (UFRAMLIB_WIRE.endTransmission() == 0) {
		UFRAMLIB_WIRE.requestFrom(_fram_address, 1);
		if(UFRAMLIB_WIRE.available()) {
			rdata = (byte) UFRAMLIB_WIRE.read();
		}
	}
	UFRAMLIB_YIELD
	return rdata;
}

/**
 * \brief Write one byte to FRAM
 *
 * @param address Address inside FRAM to write to
 * @param data byte to write
 * @return true if successful
 */
bool uFRAMLib::fram_write(unsigned int address, const byte data) {
	int _fram_address = FRAM_ADDR + ((address >> 8) & 0x7);

	UFRAMLIB_YIELD
	UFRAMLIB_WIRE.beginTransmission(_fram_address);
	UFRAMLIB_WIRE.write((int)(address & 0xFF)); // LSB
	UFRAMLIB_WIRE.write(data);
	UFRAMLIB_YIELD
	return UFRAMLIB_WIRE.endTransmission() == 0;
}
