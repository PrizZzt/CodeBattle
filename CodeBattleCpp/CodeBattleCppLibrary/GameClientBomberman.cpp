#include "GameClientBomberman.h"

#include <iostream>

GameClientBomberman::GameClientBomberman()
{
	map = nullptr;
	map_size = 0;

	is_running = false;
}

GameClientBomberman::~GameClientBomberman()
{
	is_running = false;
	work_thread->join();
}

void GameClientBomberman::Run(std::string _path, std::function<void()> _message_handler)
{
	message_handler = _message_handler;

	is_running = true;
	work_thread = new std::thread(&GameClientBomberman::update_func, this, _path);
}

void GameClientBomberman::update_func(std::string _path)
{
#ifdef _WIN32
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
		throw new std::exception("WSAStartup Failed.\n");
#endif

	web_socket = easywsclient::WebSocket::from_url(_path);
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

				map = new BombermanBlocks*[map_size];
				for (uint32_t j = 0; j < map_size; j++)
				{
					map[j] = new BombermanBlocks[map_size];
					for (uint32_t i = 0; i < map_size; i++)
					{
						map[j][i] = BombermanBlocks::Unknown;
					}
				}
			}

			uint32_t chr = 6;
			for (uint32_t j = 0; j < map_size; j++)
			{
				for (uint32_t i = 0; i < map_size; i++)
				{
					map[j][i] = (BombermanBlocks)wmessage[chr];
					chr++;

					if (map[j][i] == BombermanBlocks::Bomberman || map[j][i] == BombermanBlocks::BombBomberman || map[j][i] == BombermanBlocks::DeadBomberman)
					{
						player_x = i;
						player_y = j;
					}
				}
			}

			this->message_handler();
		});
	}
	if (web_socket)web_socket->close();

#ifdef _WIN32
	WSACleanup();
#endif
}
