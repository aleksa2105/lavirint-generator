#pragma once
#include <string_view>


enum class GameState {
    running,
    robot_won,
    minotaur_won,
    user_exit
};

inline std::string_view gameStateStr(GameState state) {
    switch (state) {
    case GameState::running: return "RUNNING";
    case GameState::robot_won: return "ROBOT WON";
    case GameState::minotaur_won: return "MINOTAUR WON";
    case GameState::user_exit: return "USER EXIT";
    }
    return "";
}