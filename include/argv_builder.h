#pragma once
#include <string>
#include <vector>

/// Builds a C-style (argc, argv) pair for SDK entry points that expect command-line arguments.
/// The builder must outlive the pointers returned by argv().
class ArgvBuilder {
public:
    explicit ArgvBuilder(const std::string &program) { data_.push_back(program); }

    ArgvBuilder &add(const std::string &flag) {
        data_.push_back(flag);
        return *this;
    }
    ArgvBuilder &add(const std::string &flag, const std::string &value) {
        data_.push_back(flag);
        data_.push_back(value);
        return *this;
    }
    ArgvBuilder &add(const std::string &flag, int value) { return add(flag, std::to_string(value)); }

    int argc() const { return static_cast<int>(data_.size()); }

    char **argv() {
        ptrs_.clear();
        for (auto &s : data_)
            ptrs_.push_back(s.data());
        ptrs_.push_back(nullptr);
        return ptrs_.data();
    }

private:
    std::vector<std::string> data_;
    std::vector<char *> ptrs_;
};
