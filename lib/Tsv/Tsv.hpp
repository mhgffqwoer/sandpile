#pragma once

#include <fstream>
#include <iostream>
#include <cstdint>

namespace Sandpile {

/**
 * @brief Initial coordinate data point from a TSV file.
 */
struct StartCoords {
  uint16_t x;     ///< X coordinate from file.
  uint16_t y;     ///< Y coordinate from file.
  uint64_t value; ///< Initial number of grains.
};

/**
 * @brief Parser and storage for the initial TSV configuration.
 */
class StartArray {
 private:
  /** @brief Offset used to handle potential negative coordinates by shifting them. */
  static const size_t kShiftCoords = INT16_MIN * (-1);

  StartCoords* array;    ///< Dynamic array of loaded coordinate data.
  size_t count_elements; ///< Current number of elements in the array.

  /** @brief Reads the TSV file and stores raw values. */
  void GetValues(const std::string& input_path);

  /** @brief Normalizes coordinates to ensure they fit within a positive grid. */
  void FixCoords();

  // Boundary helper functions
  uint16_t GetMinX() const;
  uint16_t GetMinY() const;
  uint16_t GetMaxX() const;
  uint16_t GetMaxY() const;

 public:
  /**
   * @brief Loads and processes data from a TSV file.
   * @param input_path Path to the file.
   */
  StartArray(const std::string& input_path);

  /** @brief Frees the dynamic array. */
  ~StartArray();

  /** @brief Copy constructor is disabled. */
  StartArray(const StartArray& other) = delete;
  /** @brief Copy assignment is disabled. */
  StartArray& operator=(const StartArray& other) = delete;

  /** @brief Increases the capacity of the coordinate storage. */
  void Increase();

  /** @return Number of valid data points loaded. */
  size_t Size() const;

  /** @brief Array access operator for retrieving data points. */
  StartCoords& operator[](size_t idx);

  /** @return The required grid width based on the data. */
  uint16_t Width() const;

  /** @return The required grid height based on the data. */
  uint16_t Height() const;

  /** @return True if no data points were loaded. */
  bool Empty() const;
};

}  // namespace Sandpile