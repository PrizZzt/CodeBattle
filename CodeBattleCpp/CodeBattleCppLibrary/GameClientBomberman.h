#pragma once

#include <string>
#include <thread>
#include "easywsclient\easywsclient.hpp"
#ifdef _WIN32
#pragma comment( lib, "ws2_32" )
#include <WinSock2.h>
#endif
#include <assert.h>
#include <stdio.h>
#include <string>
#include <memory>

#include "BombermanBlocks.h"

class GameClientBomberman
{
	BombermanBlocks **map;
	uint32_t map_size, player_x, player_y;

	easywsclient::WebSocket *web_socket;
	std::function<void()> message_handler;

	bool is_running;
	std::thread *work_thread;
	void update_func(std::string _path);

public:
	GameClientBomberman();
	~GameClientBomberman();

	void Run(std::string _path, std::function<void()> _message_handler);
	void Up() { web_socket->send("UP"); }
	void Down() { web_socket->send("DOWN"); }
	void Right() { web_socket->send("RIGHT"); }
	void Left() { web_socket->send("LEFT"); }
	void Act() { web_socket->send("ACT"); }
	void Blank() { web_socket->send(""); }

	BombermanBlocks **get_map() { return map; }
	uint32_t get_map_size() { return map_size; }
	uint32_t get_player_x() { return player_x; }
	uint32_t get_player_y() { return player_y; }
};
