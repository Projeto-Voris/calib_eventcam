#pragma once
#include <iostream>

namespace terminal {
inline void clear() { std::cout << "\033[2J\033[1;1H" << std::flush; }
inline void green(bool on) { std::cout << (on ? "\033[32m" : "\033[0m"); }
void wait_enter();
} // namespace terminal
