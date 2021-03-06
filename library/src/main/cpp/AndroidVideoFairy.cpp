#include <string.h>
#include "AndroidVideoFairy.hpp"

// ファミコンのパレットテーブル (16bit color)
static const unsigned short _nesRgb565[64] = {
        0x7BCF, 0x2016, 0x2817, 0x6094, 0x990F, 0xB086, 0xA180, 0x7A00, 0x4AC0, 0x3B40, 0x3B60,
        0x3308, 0x3290, 0x0000, 0x0000, 0x0000, 0xB596, 0x431F, 0x421F, 0x921E, 0xDA18, 0xDA0C,
        0xE280, 0xC380, 0x8C40, 0x5500, 0x4D42, 0x4D0D, 0x4498, 0x0000, 0x0000, 0x0000, 0xFFFF,
        0x651F, 0x541F, 0xA39F, 0xF31F, 0xFB16, 0xFBC6, 0xFD00, 0xEE84, 0x9F40, 0x7788, 0x7712,
        0x669C, 0x7BCF, 0x0000, 0x0000, 0xFFFF, 0x969F, 0xA5DF, 0xC59F, 0xE59F, 0xFDDD, 0xFE57,
        0xFED4, 0xFF92, 0xCF90, 0xA794, 0xA7F9, 0xA7FE, 0xA514, 0x0000, 0x0000};

AndroidVideoFairy::AndroidVideoFairy() {
    memset(bitmap565, 0, sizeof(bitmap565));
    skip = false;
}

AndroidVideoFairy::~AndroidVideoFairy() {
}

void AndroidVideoFairy::dispatchRendering(const uint8_t (&nesBuffer)[screenHeight][screenWidth],
                                          const uint8_t paletteMask) {
    if (!skip) {
        int ptr = 0;
        for (int y = 0; y < screenHeight; y++) {
            for (int x = 0; x < screenWidth; x++) {
                bitmap565[ptr++] = _nesRgb565[nesBuffer[y][x] & paletteMask];
            }
        }
    }
    render = true;
}
