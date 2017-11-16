#include <iostream>
#include <random>

#include "game_client.h"

bool is_block(blocks _block)
{
	return
		_block != blocks::GOLD &&
		_block != blocks::NONE &&
		_block != blocks::LADDER &&
		_block != blocks::PIPE &&
		_block != blocks::PIT_FILL_1 &&
		_block != blocks::PIT_FILL_2 &&
		_block != blocks::PIT_FILL_3 &&
		_block != blocks::PIT_FILL_4 &&
		_block != blocks::DRILL_PIT;
}

void main()
{
	srand(time(0));
	game_client *gc = new game_client("localhost:8080", "a@b.ru", "123");
	gc->Run([&]()
	{
		blocks **map = gc->get_map();
		bool done = false;

		switch (rand() % 5)
		{
		case 0: if (is_block(map[gc->get_player_y() - 1][gc->get_player_x()]) == false) { gc->Up();    done = true; } break;
		case 1: if (is_block(map[gc->get_player_y()][gc->get_player_x() + 1]) == false) { gc->Right(); done = true; } break;
		case 2: if (is_block(map[gc->get_player_y() + 1][gc->get_player_x()]) == false) { gc->Down();  done = true; } break;
		case 3: if (is_block(map[gc->get_player_y()][gc->get_player_x() - 1]) == false) { gc->Left();  done = true; } break;
		case 4: gc->Act(); done = true; break;
		}
		if (done == false)
			gc->Blank();
	});

	getchar();
}
