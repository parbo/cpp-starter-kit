#pragma once

#include <cpprest/json.h>

namespace monkeymusic {
namespace ai {

web::json::value move(const web::json::value &current_game_state);

}  // namespace ai
}  // namespace monkeymusic
