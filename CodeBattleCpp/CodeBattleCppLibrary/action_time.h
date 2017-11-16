#pragma once

#include <cstdint>

enum class action_time : uint8_t
{
	NONE = 0,
	BEFORE_TURN = 1,
	AFTER_TURN = 2
};
