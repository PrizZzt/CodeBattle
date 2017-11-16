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

#include "blocks.h"
#include "action_time.h"

class game_client
{
	blocks **map;
	uint32_t map_size, player_x, player_y;

	easywsclient::WebSocket *web_socket;
	std::string path;

	bool is_running;
	std::thread *work_thread;
	void update_func(std::function<void()> _message_handler);

public:
	game_client(std::string _server, std::string _userEmail, std::string _userPassword = "");
	~game_client();

	void Run(std::function<void()> _message_handler);
	void Up(action_time _action = action_time::NONE)
	{
		web_socket->send(std::string(_action == action_time::BEFORE_TURN ? "ACT," : "") + "UP" + std::string(_action == action_time::AFTER_TURN ? ",ACT" : ""));
	}
	void Down(action_time _action = action_time::NONE)
	{
		web_socket->send(std::string(_action == action_time::BEFORE_TURN ? "ACT," : "") + "DOWN" + std::string(_action == action_time::AFTER_TURN ? ",ACT" : ""));
	}
	void Right(action_time _action = action_time::NONE)
	{
		web_socket->send(std::string(_action == action_time::BEFORE_TURN ? "ACT," : "") + "RIGHT" + std::string(_action == action_time::AFTER_TURN ? ",ACT" : ""));
	}
	void Left(action_time _action = action_time::NONE)
	{
		web_socket->send(std::string(_action == action_time::BEFORE_TURN ? "ACT," : "") + "LEFT" + std::string(_action == action_time::AFTER_TURN ? ",ACT" : ""));
	}
	void Act() { web_socket->send("ACT"); }
	void Blank() { web_socket->send(""); }

	blocks **get_map() { return map; }
	uint32_t get_map_size() { return map_size; }
	uint32_t get_player_x() { return player_x; }
	uint32_t get_player_y() { return player_y; }
};
