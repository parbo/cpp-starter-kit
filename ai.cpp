#include "ai.h"

#include <random>

namespace monkeymusic {
namespace ai {

web::json::value random_direction() {
  auto moves = std::vector<std::string>{"up", "left", "down", "right"};

  std::random_device rd; // obtain a random number from hardware
  std::mt19937 eng(rd()); // seed the generator
  std::uniform_int_distribution<> distr(0, 3); // define the range

  return web::json::value::string(moves[distr(eng)]);
}

web::json::value move(const web::json::value &current_game_state) {
  // The gameState looks like this:
  //
  // {
  //
  //   layout: [[String]],
  //   remainingTurns: Number,
  //   isGameOver: Boolean,
  //
  //   score: Number,
  //   position: [Number, Number],
  //   inventory: [String],
  //   inventorySize: Number,
  //   buffs: {String: Number}
  // }


  // This is an example of a possible game state:
  //
  // {
  //   layout: [["empty", "monkey"],
  //            ["empty", "song"]],
  //   remainingTurns: 10,
  //   isGameOver: false,
  //
  //   score: 3,
  //   position: [0, 1],
  //   inventory: ["trap"],
  //   buffs: {"speedy": 3}
  // }


  // You control your monkey by sending one of the following commands to the server:
  //
  // {"command": "move", "direction": ("left"|"right"|"up"|"down")}
  // {"command": "use", "item": ("banana"|"trap")}
  // {"command": "idle"}
  // Remember that you can only use items that you have in your inventory!


  // Lets talk positions and directions.
  //
  // X and Y coordinates can be confusing.
  // Which way is up and which way is down?
  //
  // Here is an example explaining how coordinates work in
  // Monkey Music Challenge:
  //
  // {
  //   "layout": [["empty", "monkey"]
  //              ["song",  "empty"]]
  //   "position": [0, 1],
  //   ...
  // }
  //
  // The "position" attribute tells you the location of your monkey
  // in the "layout" matrix. In this example, you're at layout[0][1].


  // Here's an example!
  //
  // If you send {"command": "move", "direction": "down"}
  // to the server, you'll get back:
  //
  // {
  //   "layout": [["empty", "empty"]
  //              ["song",  "monkey"]]
  //   "position": [1, 1]
  // }
  //
  // If you instead send { "command": "move", "direction": "left"}
  // to the server, you'll get back:
  //
  // {
  //   "layout": [["monkey", "empty"]
  //              ["song",   "empty"]]
  //   "position": [0, 0]
  // }


  // Go to <TODO: url> for more info about the rules of Monkey Music Challenge!


  // TODO: You may want to do something smarter here
  web::json::value ret;
  ret[U("command")] = web::json::value::string(U("move"));
  ret[U("direction")] = random_direction();
  return ret;
}

}  // namespace ai
}  // namespace monkeymusic
