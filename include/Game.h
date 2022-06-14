#pragma once

class Game {
public:
  Game(int board_size, int row_win, int max_depth = 5);
  ~Game();

  int getBoardSize() const;

  int getRowWin() const;

  void setBoardSize(int boardSize);

  void setRowWin(int rowWin);

  void print_board();

  void play_tour(int i, int j, bool bot);

  bool check_win(bool bot);

  void player_tour();

  void bot_tour();

  int get_element_value(int i, int j);

  int &get_element(int i, int j);

  bool check_game_finish();

private:
  int max_depth;
  int size_of_map;
  int row_win;
  int *field;

  bool check_horizontal(bool bot);

  bool check_vertical(bool bot);

  bool check_diagonal(bool bot);

  double minimax(bool bot, int depth, double alfa, double beta);

  double calculate();

};