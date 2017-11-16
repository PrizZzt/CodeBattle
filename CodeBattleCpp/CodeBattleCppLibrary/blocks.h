#pragma once

#include <cstdint>

enum class blocks : uint16_t
{
	NONE = ' ',

	BRICK = '#',
	PIT_FILL_1 = '1',
	PIT_FILL_2 = '2',
	PIT_FILL_3 = '3',
	PIT_FILL_4 = '4',
	UNDESTROYABLE_WALL = '☼',

	DRILL_PIT = '*',

	ENEMY_LADDER = 'Q',
	ENEMY_LEFT = '«',
	ENEMY_RIGHT = '»',
	ENEMY_PIPE_LEFT = '<',
	ENEMY_PIPE_RIGHT = '>',
	ENEMY_PIT = 'X',

	GOLD = '$',

	HERO_DIE = 'Ѡ',
	HERO_DRILL_LEFT = 'Я',
	HERO_DRILL_RIGHT = 'R',
	HERO_LADDER = 'Y',
	HERO_LEFT = '◄',
	HERO_RIGHT = '►',
	HERO_FALL_LEFT = ']',
	HERO_FALL_RIGHT = '[',
	HERO_PIPE_LEFT = '{',
	HERO_PIPE_RIGHT = '}',

	OTHER_HERO_DIE = 'Z',
	OTHER_HERO_LEFT = ')',
	OTHER_HERO_RIGHT = '(',
	OTHER_HERO_LADDER = 'U',
	OTHER_HERO_PIPE_LEFT = 'Э',
	OTHER_HERO_PIPE_RIGHT = 'Є',

	LADDER = 'H',
	PIPE = '~'
};
