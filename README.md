Small library to use Arduino Nano 33 BLE Sense flash memory for basic state persistence.

Based on: https://github.com/petewarden/arduino_nano_ble_write_flash

# Declaring flash memory for storage

```
#include "blesenseflash.h"

struct MySettings
{
	int myInteger;
	char myString[32];
} writeSettings;

constexpr int mySettingsFlashSize = BLEFLASH_BLOCK_SIZE(sizeof(struct MySettings));
BLEFLASH_DECLARE_VARIABLE(flashSettings, mySettingsFlashSize) = { 42, "default" };
BLEFLASH_DECLARE_ACCESS(MySettings, readSettings, flashSettings, 0);
```

# Reading values from flash

```
Serial.println(String("My last value: ") + String(readSettings->myInteger));
```

# Storing values to flash

```
// Increment last values by one
writeSettings.myInteger = readSettings->myInteger + 1;

 // Allocate full page in RAM for writing to flash
uint8_t *data = (uint8_t*)malloc(flashBlockSize);
for (int s = 0; s < sizeof(struct MySettings); ++s)
{
	data[s] = ((uint8_t*)&writeSettings)[s];
}
BLEFLASH_WRITE(flashSettings, mySettingsFlashSize, data);
free(data);
```
