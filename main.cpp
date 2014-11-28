// stdlib stuff
#include <iostream>

// casablanca
#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <pplx/pplxtasks.h>

// our own stuff
#include "ai.h"

namespace monkeymusic {

web::json::value post_to_server(const std::string &team_name,
                                const web::json::value &command) {
  auto task = pplx::create_task([&team_name] {
      web::http::client::http_client client(U("http://warmup.monkeymusicchallenge.com/"));
      web::uri_builder builder(U("/team"));
      builder.append_path(team_name);
      return client.request(web::http::methods::POST, builder.to_string());
    }).then([=](web::http::http_response response) {
        if (response.status_code() == web::http::status_codes::OK) {
        return response.extract_json();
      }
      return pplx::create_task([] { return web::json::value(); });
    });
  return task.get();
}

void run(const std::string &team_name,
         const std::string &api_key,
         const std::function<web::json::value(const web::json::value &)> &ai) {
  // Make an initial post to start the game
  web::json::value new_game_command;
  new_game_command[U("command")] = web::json::value::string(U("new game"));
  new_game_command[U("apiKey")] = web::json::value::string(api_key);

  // The server replies with the initial game state
  auto current_game_state = post_to_server(team_name, new_game_command);

  // The current game state tells you if you have any turns left
  while (current_game_state.at(U("turns")).as_integer() > 0) {
    std::cout << "Remaining turns: " << current_game_state.at(U("turns")) << std::endl;

    // Use your AI to decide in which direction to move...
    auto next_move_direction = ai(current_game_state);

    // ...and send a new move command to the server
    web::json::value next_move_command;
    next_move_command[U("command")] = web::json::value::string(U("move"));
    next_move_command[U("direction")] = next_move_direction;
    next_move_command[U("apiKey")] = web::json::value::string(api_key);

    // After sending your next move, you'll get the new game state back
    current_game_state = post_to_server(team_name, next_move_command);
  }

  // If the game is over, our server will tell you how you did
  // Go to http://warmup.monkeymusicchallenge.com/team/<your-team-name> for more details
  std::cout << "Game over." << std::endl;
  std::cout << "  " << current_game_state[U("message")] << std::endl;
}

}  // namespace monkeymusic

int main(int argc, char* argv[]) {
  // Don't forget to provide the right command line arguments
  if (argc < 3) {
    std::cout << "Usage: monkeymusic <your-team-name> <your-api-key>" << std::endl;
    if (argc < 1) {
      std::cout << "  Missing argument: <your-team-name>" << std::endl;
    }
    if (argc < 2) {
      std::cout << "  Missing argument: <your-api-key>" << std::endl;
    }
    return 1;
  }

  // You identify yourselves by your team name
  auto team_name = std::string(argv[1]);
  auto api_key = std::string(argv[2]);

  try {
    monkeymusic::run(team_name, api_key, monkeymusic::ai::move);
  } catch (const std::exception& ex) {
    std::cout << "Exception thrown: " << ex.what() << std::endl;
    return 1;
  }


  return 0;
}
