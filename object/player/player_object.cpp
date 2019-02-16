// Purpose: player object for onlien player
// Date: 2018.12.21
// By: CasinoHe

#include "object/player/player_object.h"


namespace simple_server {
    CPlayerObject::CPlayerObject(std::string &name, std::string &object_id):
        CGameObject(name, object_id) {
    }

    CPlayerObject::~CPlayerObject() {

    }
}
