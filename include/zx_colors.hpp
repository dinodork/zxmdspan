#pragma once

#include <cstdint>

const std::uint8_t INK_BLACK = 0;
const std::uint8_t INK_BLUE = 1;
const std::uint8_t INK_RED = 1 << 1;
const std::uint8_t INK_MAGENTA = INK_RED | INK_BLUE;
const std::uint8_t INK_GREEN = 1 << 2;
const std::uint8_t INK_CYAN = INK_GREEN | INK_BLUE;
const std::uint8_t INK_YELLOW = INK_GREEN | INK_RED;
const std::uint8_t INK_WHITE = INK_GREEN | INK_RED | INK_BLUE;

const std::uint8_t PAPER_BLACK = 0;
const std::uint8_t PAPER_BLUE = 1 << 3;
const std::uint8_t PAPER_RED = 1 << 4;
const std::uint8_t PAPER_MAGENTA = PAPER_RED | PAPER_BLUE;
const std::uint8_t PAPER_GREEN = 1 << 5;
const std::uint8_t PAPER_CYAN = PAPER_GREEN | PAPER_BLUE;
const std::uint8_t PAPER_YELLOW = PAPER_GREEN | PAPER_RED;
const std::uint8_t PAPER_WHITE = PAPER_GREEN | PAPER_RED | PAPER_BLUE;

const std::uint8_t BRIGHT = 1 << 6;
const std::uint8_t FLASH = 1 << 7;
