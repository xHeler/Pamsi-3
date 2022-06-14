#include <iostream>
#include "Game.h"

int main()
{
  Game board(3, 3);
  board.print_board();
  do {
    board.player_tour();
    board.print_board();
    board.bot_tour();
    board.print_board();
  } while (!board.check_win(false) and !board.check_win(true) && !board.check_game_finish());

  if (board.check_win(false)) {
    std::cout << "Wygrywa gracz! \n";
    return 0;
  } else if (board.check_win(true)) {
    std::cout << "Wygrywa bot! \n";
    return 0;
  } else if (board.check_game_finish()) {
    std::cout << "Mamy remis! \n";
    return 0;
  }
}

