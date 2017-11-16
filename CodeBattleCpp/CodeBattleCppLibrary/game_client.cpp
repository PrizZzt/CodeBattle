#include "game_client.h"

#include <iostream>

game_client::game_client(std::string _server, std::string _userEmail, std::string _userPassword)
{
	map = nullptr;
	map_size = 0;

	path = "ws://" + _server + "/codenjoy-contest/ws?user=" + _userEmail + (_userPassword.empty() ? "" : "&pwd=" + _userPassword);

	is_running = false;
}

game_client::~game_client()
{
	is_running = false;
	work_thread->join();
}

void game_client::Run(std::function<void()> _message_handler)
{
	is_running = true;
	work_thread = new std::thread(&game_client::update_func, this, _message_handler);
}

void game_client::update_func(std::function<void()> _message_handler)
{
#ifdef _WIN32
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
		throw new std::exception("WSAStartup Failed.\n");
#endif

	web_socket = easywsclient::WebSocket::from_url(path);
	if (web_socket == nullptr)is_running = false;
	while (is_running)
	{
		web_socket->poll();
		web_socket->dispatch([&](const std::string &message)
		{
			int size_needed = MultiByteToWideChar(CP_UTF8, 0, &message[0], (int)message.size(), NULL, 0);
			std::wstring wmessage(size_needed, 0);
			MultiByteToWideChar(CP_UTF8, 0, &message[0], (int)message.size(), &wmessage[0], size_needed);

			uint32_t size = sqrt(wmessage.size() - 6);
			if (map_size != size)
			{
				if (map_size != 0)
				{
					for (uint32_t j = 0; j < map_size; j++)
						delete[] map[j];
					delete[] map;
				}
				map_size = size;

				map = new blocks*[map_size];
				for (uint32_t j = 0; j < map_size; j++)
				{
					map[j] = new blocks[map_size];
					for (uint32_t i = 0; i < map_size; i++)
					{
						map[j][i] = blocks::NONE;
					}
				}
			}

			uint32_t chr = 6;
			for (uint32_t j = 0; j < map_size; j++)
			{
				for (uint32_t i = 0; i < map_size; i++)
				{
					map[j][i] = (blocks)wmessage[chr];
					chr++;

					if (
						map[j][i] == blocks::HERO_DIE ||
						map[j][i] == blocks::HERO_DRILL_LEFT ||
						map[j][i] == blocks::HERO_DRILL_RIGHT ||
						map[j][i] == blocks::HERO_LADDER ||
						map[j][i] == blocks::HERO_LEFT ||
						map[j][i] == blocks::HERO_RIGHT ||
						map[j][i] == blocks::HERO_FALL_LEFT ||
						map[j][i] == blocks::HERO_FALL_RIGHT ||
						map[j][i] == blocks::HERO_PIPE_LEFT ||
						map[j][i] == blocks::HERO_PIPE_RIGHT
						)
					{
						player_x = i;
						player_y = j;
					}
				}
			}

			_message_handler();
		});
	}
	if (web_socket)web_socket->close();

#ifdef _WIN32
	WSACleanup();
#endif
}
