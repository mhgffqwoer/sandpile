#pragma once

#include <string>
#include <vector>
#include <cstddef>

/**
 * @brief Namespace containing command-line argument parsing logic.
 */
namespace Arguments {

/**
 * @brief Class responsible for parsing and storing command-line arguments.
 */
class Arguments {
public:
    /**
     * @brief Default constructor initializing members with default values.
     */
    Arguments();

    /**
     * @brief Gets the input file path.
     * @return String containing the path to the input file.
     */
    std::string GetInputFile() const;

    /**
     * @brief Gets the output directory path.
     * @return String containing the output directory path.
     */
    std::string GetOutputPath() const;

    /**
     * @brief Gets the maximum number of iterations.
     * @return The limit of iterations for the simulation.
     */
    size_t GetMaxIterations() const;

    /**
     * @brief Gets the frequency of image generation.
     * @return Number of iterations between saving snapshots.
     */
    size_t GetFrequency() const;

    /**
     * @brief Parses arguments from standard main() parameters.
     * @param argc Argument count.
     * @param argv Array of argument strings.
     * @return Reference to the current Arguments object.
     */
    Arguments& Parse(const int argc, const char** argv);

    /**
     * @brief Overloaded parser that processes arguments stored in a vector.
     * @param argc Number of elements to process.
     * @param argv Vector of strings containing arguments.
     */
    void Parse(const int argc, const std::vector<std::string>& argv);

private:
    std::string input_file;    ///< Path to the input data file.
    std::string output_path;   ///< Directory for saving output BMP files.
    size_t max_iterations;     ///< Maximum allowed iterations.
    size_t frequency;          ///< Snapshot frequency (0 means only final result).

    /**
     * @brief Checks if a given argument string matches a specific command prefix.
     * @param arg The argument string to check (e.g., "--input=file.txt").
     * @param command The command prefix to look for (e.g., "--input").
     * @return True if the argument starts with the command prefix.
     */
    bool isArg(const std::string& arg, const std::string& command);
};

}  // namespace Arguments