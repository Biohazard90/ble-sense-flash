
#include <Arduino.h>

constexpr int kFlashBlockSize = 4096;

#define ROUND_UP(val, block_size) ((((val) + ((block_size) - 1)) / (block_size)) * (block_size))
#define BLEFLASH_BLOCK_SIZE(x) \
	ROUND_UP((x), kFlashBlockSize)

#define BLEFLASH_DECLARE_VARIABLE(name, pageSize) \
	alignas(kFlashBlockSize) const uint8_t name[(pageSize)]

#define BLEFLASH_DECLARE_ACCESS(type, accessName, varName, offset) \
	type *(accessName) = (type*)(((uint8_t*)&(varName)) + offset)

extern void _BLEFlashWriteVar(uint32_t pageAddr, int size, void *data);

#define BLEFLASH_WRITE(name, pageSize, data) \
	_BLEFlashWriteVar(reinterpret_cast<uint32_t>(name), (pageSize), (data))

extern void _BLEFlashReadVar(uint32_t pageAddr, int size, void *data);

#define BLEFLASH_READ(name, pageSize, data) \
	_BLEFlashReadVar(reinterpret_cast<uint32_t>(name), (pageSize), (data))
