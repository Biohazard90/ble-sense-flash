
#include <Arduino.h>

#include "blesenseflash.h"

#include "FlashIAPBlockDevice.h"

void _BLEFlashWriteVar(uint32_t pageAddr, int size, void *data)
{
	Serial.println("Writing to flash...");
	static FlashIAPBlockDevice bd(pageAddr, size);

	bd.init();
	bd.erase(0, size);
	bd.program(data, 0, size);
	bd.deinit();  
}

void _BLEFlashReadVar(uint32_t pageAddr, int size, void *data)
{
	Serial.println("Reading from flash...");
	static FlashIAPBlockDevice bd(pageAddr, size);

	bd.init();
	bd.read(data, 0, size);
	bd.deinit();  
}
