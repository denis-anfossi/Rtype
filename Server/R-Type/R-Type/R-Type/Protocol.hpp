#ifndef		_PROTOCOL_HPP_
#define		_PROTOCOL_HPP_

#include <stdint.h>

namespace RTProtocol
{
	#pragma pack(push, 1)

	enum			COMMAND
	{
		CONNECTION = 0,
		RUN_MODE,
		IDENTIFIER,
		GAME_STATE,
		GAME_ACTION,
		GAME_DATA
	};

	struct			Header
	{
		uint8_t		Command;
		int32_t		Size;
	};

	enum			CONNECTION
	{
		LOG_IN = 0,
		LOG_OUT,
		CHECK
	};

	struct			Connection
	{
		uint8_t		StateConnection;
	};

	enum			RUN_MODE
	{
		CREATE = 0,
		JOIN
	};

	struct			RunMode
	{
		uint8_t		Mode;
	};

	enum			IDENTIFIER
	{
		PLAYER_1 = 0,
		PLAYER_2,
		PLAYER_3,
		PLAYER_4,
		NO_PLAY
	};

	struct			Identifier
	{
		uint8_t		Id;
	};

	enum			GAME_STATE
	{
		START = 0,
		END
	};

	struct			GameState
	{
		uint8_t		State;
	};

	enum			GAME_ACTION
	{
		UP = 0,
		DOWN,
		LEFT,
		RIGHT,
		SHOOT
	};

	struct			GameAction
	{
		uint8_t		Action;
	};

	enum			EXTERN_TYPE
	{
		PLAYER = 0,
		MONSTER,
		FIRE
	};

	enum			MONSTER_TYPE
	{
		MONSTER_TYPE1 = 0,
		MONSTER_TYPE2,
	};

	struct			GameData
	{
		uint8_t		ExternType;
		uint8_t		InternType;
		uint8_t		Id;
		int16_t		x;
		int16_t		y;
		uint8_t		alive;
	};
// 0 = mort
// 1 = vivant
	#pragma pack(pop)
}

#endif		/* PROTOCOLP_HPP */