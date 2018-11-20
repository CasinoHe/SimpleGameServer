// Purpose: base class of all game object, abstract class
// Date: 2018.11.15
// By: CasinoHe

#include "object/game_object.h"

namespace simple_server {
	CGameObject::CGameObject() noexcept {
	}

	unsigned int CGameObject::generate_id() {
		return 1;
	}
}
