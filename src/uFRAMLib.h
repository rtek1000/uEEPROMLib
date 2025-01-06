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

#ifndef UFRAMLIB

	#define UFRAMLIB
	#include "Arduino.h"

	#define FRAM_ADDR 0x50 // device base address (range 0x50 ~ 0x57)

	#ifndef UFRAMLIB_WIRE
		#if defined(ARDUINO_attiny) || defined(ARDUINO_AVR_ATTINYX4) || defined(ARDUINO_AVR_ATTINYX5) || defined(ARDUINO_AVR_ATTINYX7) || defined(ARDUINO_AVR_ATTINYX8) || defined(ARDUINO_AVR_ATTINYX61) || defined(ARDUINO_AVR_ATTINY43) || defined(ARDUINO_AVR_ATTINY828) || defined(ARDUINO_AVR_ATTINY1634) || defined(ARDUINO_AVR_ATTINYX313)
			#include <TinyWireM.h>                  // I2C Master lib for ATTinys which use USI
			#define UFRAMLIB_WIRE TinyWireM
		#else
			#include <Wire.h>
			#define UFRAMLIB_WIRE Wire
		#endif
	#endif

	// ESP yield function (ESP32 has no need for that on dual core, but it has on single core version)
	#if ARDUINO_ARCH_ESP8266
		/**
		 * \brief ESP8266, yield to don't block ESP functionality.
		 *
		 * When this library is used in other MCUs this is simply removed by the preprocessor
		 */
		#define UFRAMLIB_YIELD yield();
	#else
		#if ARDUINO_ARCH_ESP32
		/**
		 * \brief ESP32, yield to don't block ESP functionality.
		 *
		 * When this library is used in other MCUs this is simply removed by the preprocessor
		 */
			#define UFRAMLIB_YIELD yield();
		#else
			#define UFRAMLIB_YIELD
		#endif
	#endif

	class uFRAMLib {
		public:
			// Constructors
			uFRAMLib();
			uFRAMLib(bool);

			// FRAM read functions
			byte fram_read(unsigned int);

			// FRAM write functions
			bool fram_write(unsigned int address, const byte data);

		private:
		    int _ee_address = 0;

	};

#endif