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
  auto task = pplx::create_task([&team_name, &command] {
      web::http::client::http_client client(U("http://competition.monkeymusicchallenge.com/"));
      web::uri_builder builder(U("/game"));
      return client.request(web::http::methods::POST, builder.to_string(), command);
    }).then([=](web::http::http_response response) {
      if (response.status_code() == web::http::status_codes::OK) {
        return response.extract_json();
      }
      std::cout << "Error! We seem to have trouble talking to the server..." << std::endl;
      std::cout << "    The server replied with status code: " << response.status_code() << std::endl;
      // Extract the value so we can print it
      auto body = response.extract_json().get();
      std::cout << "    " << body << std::endl;
      // Return null value
      return pplx::create_task([] { return web::json::value(); });
    });
  return task.get();
}

void run(const std::string &team_name,
         const std::string &api_key,
         const std::string &game_id,
         const std::function<web::json::value(const web::json::value &)> &ai) {
  // Make an initial post to start the game
  web::json::value new_game_command;
  new_game_command[U("command")] = web::json::value::string(U("join game"));
  new_game_command[U("team")] = web::json::value::string(team_name);
  new_game_command[U("apiKey")] = web::json::value::string(api_key);
  new_game_command[U("gameId")] = web::json::value::string(game_id);

  // The server replies with the initial game state
  auto current_game_state = post_to_server(team_name, new_game_command);

  // The current game state tells you if you have any turns left
  while (!current_game_state.is_null() && !current_game_state.at(U("isGameOver")).as_bool()) {
    std::cout << "Remaining turns: " << current_game_state.at(U("remainingTurns")) << std::endl;

    // Use your AI to decide in which direction to move...
    auto next_command = ai(current_game_state);

    // Don't forget to include your teamName, API key and the game ID
    next_command[U("team")] = web::json::value::string(team_name);
    next_command[U("apiKey")] = web::json::value::string(api_key);
    next_command[U("gameId")] = web::json::value::string(game_id);

    // After sending your next move, you'll get the new game state back
    current_game_state = post_to_server(team_name, next_command);
  }

  // If the game is over, our server will tell you how you did
  // Go to http://warmup.monkeymusicchallenge.com/team/<your-team-name> for more details
  std::cout << "Game over." << std::endl;
}

}  // namespace monkeymusic

int main(int argc, char* argv[]) {
  // Don't forget to provide the right command line arguments
  if (argc < 4) {
    std::cout << "Usage: monkeymusic <your-team-name> <your-api-key> <game-id>" << std::endl;
    if (argc < 1) {
      std::cout << "  Missing argument: <your-team-name>" << std::endl;
    }
    if (argc < 2) {
      std::cout << "  Missing argument: <your-api-key>" << std::endl;
    }
    if (argc < 3) {
      std::cout << "  Missing argument: <game-id>" << std::endl;
    }
    return 1;
  }

  // You identify yourselves by your team name
  auto team_name = std::string(argv[1]);
  auto api_key = std::string(argv[2]);
  auto game_id = std::string(argv[3]);

  try {
    monkeymusic::run(team_name, api_key, game_id, monkeymusic::ai::move);
  } catch (const std::exception& ex) {
    std::cout << "Exception thrown: " << ex.what() << std::endl;
    return 1;
  }


  return 0;
}
