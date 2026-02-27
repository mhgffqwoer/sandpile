#pragma once

#include <fstream>
#include <vector>
#include <cstdint>
#include "../Table/Table.hpp"

namespace Sandpile {

/** @brief Size of the BMP file header in bytes. */
static constexpr const uint8_t kFileHeaderSize = 14;
/** @brief Size of the BMP info header (DIB header) in bytes. */
static constexpr const uint8_t kInfoHeaderSize = 40;
/** @brief Size of the color palette in bytes. */
static constexpr const uint8_t kPaletteSize = 20;
/** @brief Number of colors used in the 4-bit palette. */
static constexpr const uint8_t kColorAmount = 5;
/** @brief Bits per pixel for the output image. */
static constexpr const uint8_t kBitsPerPixel = 4;

/**
 * @brief Simple RGB color representation.
 */
struct Color {
    uint8_t blue;  ///< Blue color component.
    uint8_t green; ///< Green color component.
    uint8_t red;   ///< Red color component.
};

/**
 * @brief Manages the BMP color palette for sandpile visualization.
 */
struct Palette {
    uint8_t palette[kPaletteSize] {0}; ///< Raw byte array for the BMP palette.

    Color white = { 255, 255, 255 };  ///< Color for 0 grains.
    Color green = { 10, 85, 71 };     ///< Color for 1 grain.
    Color yellow = { 5, 178, 252 };   ///< Color for 2 grains.
    Color purple = { 159, 83, 134 };  ///< Color for 3 grains.
    Color black = { 31, 29, 39 };     ///< Color for 4+ grains (unstable).

    /**
     * @brief Populates the raw palette array with predefined colors.
     */
    void SetPalette();
};

/**
 * @brief Handles BMP image creation and formatting.
 */
struct Image {
    uint8_t bmp_file_header[kFileHeaderSize]{ 0 }; ///< Buffer for the file header.
    uint8_t bmp_inf_header[kInfoHeaderSize]{ 0 };  ///< Buffer for the info header.
    uint32_t file_size;                            ///< Total size of the BMP file.
    uint8_t padding_amount;                        ///< Number of padding bytes per row.

    /**
     * @brief Calculates total file size including headers and padding.
     * @param table Reference to the simulation table to get dimensions.
     */
    void SetFileSize(Table& table);

    /**
     * @brief Prepares BMP headers with metadata (width, height, etc.).
     * @param table Reference to the simulation table.
     */
    void SetHeader(Table& table);

    /**
     * @brief Generates and saves a BMP file from the current table state.
     * @param table Current sandpile grid.
     * @param output_filename Path where the BMP will be saved.
     */
    void CreateImage(Table& table, const std::string& output_filename);
};

}  // namespace Sandpile