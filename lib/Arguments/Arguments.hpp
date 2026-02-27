#pragma once

#include <string>
#include <cstddef>

namespace Arguments {

class Arguments {
public:
    Arguments();

    std::string GetInputFile() const;
    std::string GetOutputPath() const;
    size_t GetMaxIterations() const;
    size_t GetFrequency() const;

    Arguments& Parse(const int argc, const char** argv);
    void Parse(const int argc, const std::string argv[]);

private:
    std::string input_file;
    std::string output_path;
    size_t max_iterations;
    size_t frequency;

    bool isArg(const std::string& arg, const std::string& command);
};

}  // namespace Arguments