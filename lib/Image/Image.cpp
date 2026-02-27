#include "Image.hpp"

namespace Sandpile {

void Image::SetFileSize(Table& table) {
    padding_amount = (8 - (table.Width() % 8)) % 8;
    file_size = kFileHeaderSize + kInfoHeaderSize + kPaletteSize +
        ((table.Width() + padding_amount) * table.Height() + 1) / 2;
}

void Image::SetHeader(Table& table) {
    bmp_file_header[0] = 0x42;
    bmp_file_header[1] = 0x4D;  //  BM signature

    bmp_file_header[2] = static_cast<uint8_t>(file_size & 0xFF);
    bmp_file_header[3] = static_cast<uint8_t>((file_size >> 8) & 0xFF);
    bmp_file_header[4] = static_cast<uint8_t>((file_size >> 16) & 0xFF);
    bmp_file_header[5] = static_cast<uint8_t>((file_size >> 24) & 0xFF);

    // Зарезервированные байты 6-9 уже занулены при инициализации массива {0}

    bmp_file_header[10] = kFileHeaderSize + kInfoHeaderSize + kPaletteSize;
    // Байты 11-13 тоже занулены

    bmp_inf_header[0] = kInfoHeaderSize;
    // Байты 1-3 занулены

    uint32_t width = table.Width();
    bmp_inf_header[4] = static_cast<uint8_t>(width & 0xFF);
    bmp_inf_header[5] = static_cast<uint8_t>((width >> 8) & 0xFF);
    bmp_inf_header[6] = static_cast<uint8_t>((width >> 16) & 0xFF);
    bmp_inf_header[7] = static_cast<uint8_t>((width >> 24) & 0xFF);

    uint32_t height = table.Height();
    bmp_inf_header[8] = static_cast<uint8_t>(height & 0xFF);
    bmp_inf_header[9] = static_cast<uint8_t>((height >> 8) & 0xFF);
    bmp_inf_header[10] = static_cast<uint8_t>((height >> 16) & 0xFF);
    bmp_inf_header[11] = static_cast<uint8_t>((height >> 24) & 0xFF);

    bmp_inf_header[12] = 1; // Planes
    bmp_inf_header[14] = kBitsPerPixel;
    bmp_inf_header[32] = kColorAmount;
}

void Palette::SetPalette() {
    uint8_t* p = palette;
    Color colors[] = { white, green, yellow, purple, black };
    for (int i = 0; i < 5; ++i) {
        p[i * 4] = colors[i].blue;
        p[i * 4 + 1] = colors[i].green;
        p[i * 4 + 2] = colors[i].red;
        p[i * 4 + 3] = 0;
    }
}

void Image::CreateImage(Table& table, const std::string& output_filename) {
    Palette palette_obj;
    SetFileSize(table);
    SetHeader(table);
    palette_obj.SetPalette();

    std::ofstream bmp_file(output_filename, std::ios::out | std::ios::binary);
    if (!bmp_file) return;

    bmp_file.write(reinterpret_cast<char*>(bmp_file_header), kFileHeaderSize);
    bmp_file.write(reinterpret_cast<char*>(bmp_inf_header), kInfoHeaderSize);
    bmp_file.write(reinterpret_cast<char*>(palette_obj.palette), kPaletteSize);

    for (int64_t y = table.Height() - 1; y >= 0; --y) {
        for (int64_t x = 0; x < table.Width() + padding_amount; x += 2) {
            uint8_t left = 0, right = 0;

            if (x < table.Width()) {
                uint64_t val = table.Value(static_cast<uint16_t>(x), static_cast<uint16_t>(y));
                left = (val >= 4) ? 4 : static_cast<uint8_t>(val);
            }
            if (x + 1 < table.Width()) {
                uint64_t val = table.Value(static_cast<uint16_t>(x + 1), static_cast<uint16_t>(y));
                right = (val >= 4) ? 4 : static_cast<uint8_t>(val);
            }

            uint8_t byte = static_cast<uint8_t>((left << 4) | (right & 0x0F));
            bmp_file.put(static_cast<char>(byte));
        }
    }
    bmp_file.close();
}

}  // namespace Sandpile