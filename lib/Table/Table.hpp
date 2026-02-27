#pragma once

#include "../Queue/Queue.hpp"
#include "../Tsv/Tsv.hpp"

namespace Sandpile {

/**
 * @brief Main simulation grid for the Abelian Sandpile Model.
 */
class Table {
 private:
  static const uint8_t kTopUpValue = 50; ///< Constant used for initial grid scaling.
  static const uint8_t kResize = 5;      ///< Margin size added during grid expansion.

  uint8_t** array;   ///< 2D array representing the grid (stores grain counts).
  uint16_t width;    ///< Current width of the grid (X-axis).
  uint16_t height;   ///< Current height of the grid (Y-axis).

  Queue queue_in;    ///< Queue of cells to process in the current iteration.
  Queue queue_out;   ///< Queue of cells that become unstable for the next iteration.
  StartArray start_array; ///< Initial grain data loaded from TSV.

  /** @brief Deallocates the 2D grid memory. */
  void Clear();

  /** @brief Populates the grid with initial grains from the start_array. */
  void TopUp();

  /**
   * @brief Checks if sand has reached the boundaries of the current grid.
   * @return True if a resize is required.
   */
  bool NeedResize() const;

  /** @brief Expands the grid dimensions and migrates existing data. */
  void Resize();

public:
  /**
   * @brief Constructs a table and initializes the simulation from a file.
   * @param input_path Path to the TSV file.
   */
  Table(const std::string& input_path);

  /** @brief Cleans up all dynamic resources. */
  ~Table();

  /** @brief Copying a Table is disabled. */
  Table(const Table& other) = delete;
  /** @brief Copy assignment for Table is disabled. */
  Table& operator=(const Table& other) = delete;

  /**
   * @brief Determines if the sandpile has reached a stable state (no more topples).
   * @return True if stable.
   */
  bool Stable() const;

  /**
   * @brief Executes one full iteration of the toppling process.
   */
  void Iteration();

  /** @return Current grid width. */
  uint16_t Width() const;

  /** @return Current grid height. */
  uint16_t Height() const;

  /**
   * @brief Retrieves the grain count at specific coordinates.
   * @param x X coordinate.
   * @param y Y coordinate.
   * @return Number of grains.
   */
  uint8_t Value(uint16_t x, uint16_t y) const;
};

}  // namespace Sandpile