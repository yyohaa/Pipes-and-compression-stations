#pragma once
#include <iostream>

class redirect_output_wrapper {
    std::ostream& stream;
    std::streambuf* oldBuffer;

public:
    redirect_output_wrapper(std::ostream& src)
        : stream(src), oldBuffer(src.rdbuf()) {
    }

    void redirect(std::ostream& dest) {
        stream.rdbuf(dest.rdbuf());
    }

    ~redirect_output_wrapper() {
        stream.rdbuf(oldBuffer);
    }
};
