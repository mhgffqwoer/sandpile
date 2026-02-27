#pragma once

#include <iostream>
#include <cstdint>

namespace Sandpile {

/**
 * @brief Structure representing 2D grid coordinates.
 */
struct Coords {
  uint16_t x; ///< Horizontal coordinate.
  uint16_t y; ///< Vertical coordinate.
};

/**
 * @brief A dynamic queue for storing coordinates of unstable cells.
 */
class Queue {
 private:
  Coords* array;   ///< Internal dynamic array.
  size_t capacity; ///< Maximum number of elements before resizing.
  size_t head;     ///< Index of the front element.
  size_t tail;     ///< Index for the next element to be added.

 public:
  /** @brief Constructs an empty queue with initial capacity. */
  Queue();

  /** @brief Destructor to free dynamic memory. */
  ~Queue();

  /** @brief Copy constructor is disabled. */
  Queue(const Queue& other) = delete;

  /** @brief Assignment operator for the queue. */
  Queue& operator=(const Queue& other);

  /**
   * @brief Adds coordinates to the back of the queue.
   * @param coord_x X coordinate.
   * @param coord_y Y coordinate.
   */
  void Push(uint16_t coord_x, uint16_t coord_y);

  /**
   * @brief Removes and returns the front element.
   * @return Coords structure from the front of the queue.
   */
  Coords Pop();

  /** @brief Doubles the capacity of the internal array. */
  void Increase();

  /** @brief Resets the queue to an empty state. */
  void Clear();

  /**
   * @brief Checks if the queue has no elements.
   * @return True if empty, false otherwise.
   */
  bool Empty() const;
};

}  // namespace Sandpile