// Purpose: player object for onlien player
// Date: 2018.12.21
// By: CasinoHe

#pragma once

#ifndef SIMPLE_SERVER_PLAYER_PLAYER_OBJECT_H
#define SIMPLE_SERVER_PLAYER_PLAYER_OBJECT_H

#include "object/game_object.h"

#include <string>

namespace simple_server {
	class CPlayerObject: public CGameObject {

		// Player Object need to be serializable
		SERIALIZE_CLASS_HEAD;

		public:
			CPlayerObject() = delete;
			CPlayerObject(const std::string &name = std::string("Player"), std::string object_id = std::string());
			virtual ~CPlayerObject();

			inline virtual bool is_serializable() {return true;}
	};
}

#endif
