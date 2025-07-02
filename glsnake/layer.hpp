#include <cstdint>
#include <limits>

#ifndef LAYER_HPP
#define LAYER_HPP
enum class Layer: std::uint8_t {
	TOP = 0,
	MAIN = 1,
	BOTTOM = std::numeric_limits<std::uint8_t>::max()
};
#endif