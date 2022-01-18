#ifndef __EPD_H__
#define __EPD_H__

#include <stdint.h>
#include <stdarg.h>

#include "macros.h"

#define DATA(...) PP_NARG(__VA_ARGS__), __VA_ARGS__

#define DEFAULT_PIN_DC 9
#define DEFAULT_PIN_CS 10
#define DEFAULT_PIN_RST 8
#define DEFAULT_PIN_BUSY 7

enum ColorMode
{
	MODE_MONOCHROME = 0,
	MODE_BLACKWHITE = 1
};

enum MonochromePixelColor
{
	COLOR_BLACK = 0b00,
	COLOR_DARK_GRAY = 0b01,
	COLOR_BRIGHT_GRAY = 0b10,
	COLOR_WHITE = 0b11
};

enum MonochromeChannel
{
	MONOCHROME_CHANNEL_LIGHT_GRAY = 0x24,
	MONOCHROME_CHANNEL_DARK_GRAY = 0x26
};

class EPD
{
public:
	static const unsigned int width = 240;
	static const unsigned int height = 480;

	// Default pinout TODO: Change to real pins
	EPD() : EPD(DEFAULT_PIN_RST, DEFAULT_PIN_DC, DEFAULT_PIN_CS, DEFAULT_PIN_BUSY){
				// Do nothing
			};

	// User defined pinout
	EPD(int pinRST, int pinDC, int pinCS, int pinBUSY);

	// Destructor - disable device
	~EPD();

	// Device supports data / commands
	void sendCommand(uint8_t command);
	void sendData(size_t nbytes, ...);

	// Blocking busy wait
	void readBusy();

	// Clear the screen
	void clear();

	// In case the SoC is too small to hold the entire image in-memory, these functions
	// allow painting the image onto the screen 4-pixels per call (as one byte holds 4 pixel values).
	void displayStartChannel(enum MonochromeChannel channel);
	void displayPixels(enum MonochromePixelColor image[4]);
	void displayFinalize();

	void display(enum MonochromePixelColor *image);

	// Reset screen
	void reset(enum ColorMode mode);

private:
	void loadLUT(const uint8_t *lut, size_t size);

	int RST;
	int DC;
	int CS;
	int BUSY;

	enum ColorMode colorMode;
};

#endif // __EPD_H__