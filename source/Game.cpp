#include "Game.h"
#include <iostream>
#include "List.h"
#include <bits/stdc++.h>

Game::Game(int board_size, int row_win, int max_depth) {
  if (size_of_map < 0 || row_win < 0 || size_of_map < row_win || max_depth < 0)
    throw std::invalid_argument("Game constructor error!");
  this->max_depth = max_depth;
  this->size_of_map = board_size;
  this->row_win = row_win;

  field = new int[board_size * board_size];
  for (int i = 0; i < board_size * board_size; ++i) {
    field[i] = 0;
  }
}

int Game::getBoardSize() const {
  return size_of_map;
}

int Game::getRowWin() const {
  return row_win;
}

void Game::setBoardSize(int boardSize) {
  size_of_map = boardSize;
}

void Game::setRowWin(int rowWin) {
  row_win = rowWin;
}

Game::~Game() {
  delete[] field;
}

void Game::print_board() {
  for (int k = 0; k < size_of_map; ++k) {
    std::cout << "----";
  }
  std::cout << "-\n";
  for (int i = 0; i < size_of_map; ++i) {
    std::cout << "|";
    for (int j = 0; j < size_of_map; ++j) {
      std::cout << " ";
      if (field[j * size_of_map + i] == 0) {
        std::cout << " ";
      } else if (field[j * size_of_map + i] == 1) {
        std::cout << "X";
      } else if (field[j * size_of_map + i] == 2) {
        std::cout << "O";
      }
      std::cout << " |";
    }
    std::cout << "\n";
    for (int k = 0; k < size_of_map; ++k) {
      std::cout << "----";
    }
    std::cout << "-\n";
  }
}

void Game::play_tour(int i, int j, bool bot) {
  if (i < 0 || j < 0 || i >= size_of_map || j >= size_of_map || get_element_value(i, j) != 0)
    throw std::invalid_argument("function play_tour in Game class error!");

  if (bot)
    get_element(i, j) = 2; // bot has symbol 2
  else
    get_element(i, j) = 1; // human has symbol 1
}

int &Game::get_element(int i, int j) {
  return field[size_of_map * i + j];
}

int Game::get_element_value(int i, int j) {
  return field[size_of_map * i + j];
}

bool Game::check_horizontal(bool bot) {
  int symbol = bot ? 2 : 1;
  for (int i = 0; i < size_of_map; ++i) {
    int line = 0;
    for (int j = 0; j < size_of_map; j++) {
      if (get_element_value(i, j) == symbol) {
        line++;
      } else if (get_element_value(i, j) != symbol) {
        line = 0;
      } else if (get_element_value(i, j) && size_of_map - j < row_win) {
        break;
      }
      if (line >= row_win) {
        return true;
      }
    }
  }
  return false;
}

bool Game::check_vertical(bool bot) {
  int symbol = bot ? 2 : 1;
  for (int j = 0; j < size_of_map; ++j) {
    int line = 0;
    for (int i = 0; i < size_of_map; i++) {
      if (get_element_value(i, j) == symbol) {
        line++;
      } else if (get_element_value(i, j) != symbol) {
        line = 0;
      } else if (get_element_value(i, j) && size_of_map - j < row_win) {
        break;
      }
      if (line >= row_win) {
        return true;
      }
    }
  }
  return false;
}

bool Game::check_diagonal(bool isBot) {
  int symbol = isBot ? 2 : 1;
  List win;
  for (int i = 0; i < row_win; ++i)
    win.append(symbol);


  for (int i = 0; i < size_of_map - row_win + 1; ++i) {
    List diagonal;
    int x = i;
    int y = 0;

    for (int j = 0; j < size_of_map - i; ++j) {
      diagonal.append(get_element_value(x, y));
      x++;
      y++;
    }
    for (int j = 0; j < diagonal.getSize() - win.getSize() + 1; ++j) {
      // j: j + row_win
      bool tmp = true;
      for (int k = j; k < j + row_win; ++k) {
        if (win[0] != diagonal[k]) {
          tmp = false;
          continue;
        }
      }
      if (tmp) return true;
    }
    diagonal = List();
    x = 0;
    y = i;

    for (int j = 0; j < size_of_map - i; ++j) {
      diagonal.append(get_element_value(x, y));
      x++;
      y++;
    }
    for (int j = 0; j < diagonal.getSize() - win.getSize() + 1; ++j) {
      bool tmp = true;
      for (int k = j; k < j + row_win; ++k) {
        if (win[0] != diagonal[k]) {
          tmp = false;
          continue;
        }
      }
      if (tmp) return true;
    }

    diagonal = List();
    x = size_of_map - 1 - i;
    y = 0;

    for (int j = 0; j < size_of_map - i; ++j) {
      diagonal.append(get_element_value(x, y));
      x++;
      y++;
    }
    for (int j = 0; j < diagonal.getSize() - win.getSize() + 1; ++j) {
      bool tmp = true;
      for (int k = j; k < j + row_win; ++k) {
        if (win[0] != diagonal[k]) {
          tmp = false;
          continue;
        }
      }
      if (tmp) return true;
    }

    diagonal = List();
    x = size_of_map - 1;
    y = 0 + i;

    for (int j = 0; j < size_of_map - i; ++j) {
      diagonal.append(get_element_value(x, y));
      x++;
      y++;
    }
    for (int j = 0; j < diagonal.getSize() - win.getSize() + 1; ++j) {
      bool tmp = true;
      for (int k = j; k < j + row_win; ++k) {
        if (win[0] != diagonal[k]) {
          tmp = false;
          continue;
        }
      }
      if (tmp) return true;
    }
  }
  return false;
}

bool Game::check_game_finish() {
  for (int i = 0; i < size_of_map; ++i) {
    for (int j = 0; j < size_of_map; ++j) {
      if (get_element_value(i, j) == 0)
        return false;
    }
  }
  return true;
}

bool Game::check_win(bool bot) {
  return check_horizontal(bot) || check_vertical(bot) || check_diagonal(bot);
}

void Game::player_tour() {
  int i = 0;
  int j = 0;

  do {
    std::cout << "Podaj wiersz i kolumne: ";
    std::cin >> i >> j;
    i--;
    j--;
  } while (get_element_value(i, j) != 0);
  play_tour(i, j, false);
}

void Game::bot_tour() {
  int move_i = 0;
  int move_j = 0;
  double best_score = INT_MIN;
  for (int i = 0; i < size_of_map; ++i) {
    for (int j = 0; j < size_of_map; ++j) {
      if (get_element_value(i, j) == 0) {
        get_element(i, j) = 2;
        double minimax_score = minimax(true, max_depth, INT_MIN, INT_MAX);
        get_element(i, j) = 0;
        if (minimax_score > best_score) {
          best_score = minimax_score;
          move_i = i;
          move_j = j;
        }
      }
    }
  }
  play_tour(move_i, move_j, true);
  std::cout << "Bot zagrywa ruch: " << move_i + 1 << ", " << move_j + 1 << "\n";
}

double Game::minimax(bool bot, int depth, double alfa, double beta) {

  if (check_win(bot) || check_win(!bot)) {
    if (bot)
      return INT_MAX;
    else
      return INT_MIN;
  }

  if (check_game_finish() || depth == 0) {
    if (bot)
      return calculate();
    else
      return (-1) * calculate();
  }

  double best_score;

  if (bot) {
    bot = false;
    best_score = INT_MAX;
  } else {
    bot = true;
    best_score = INT_MIN;
  }

  int symbol = bot ? 2 : 1;

  for (int i = 0; i < size_of_map; ++i) {
    for (int j = 0; j < size_of_map; ++j) {
      if (get_element_value(i, j) == 0) {
        if (bot) {
          get_element(i, j) = symbol;
          double m = minimax(bot, depth - 1, alfa, beta);
          if (best_score < m)
            best_score = m;
          if (alfa < best_score)
            alfa = best_score;
          get_element(i, j) = 0;
          if (alfa >= beta)
            return best_score;
        } else {
          get_element(i, j) = symbol;
          double m = minimax(bot, depth - 1, alfa, beta);
          if (best_score > m)
            best_score = m;
          if (beta > best_score)
            beta = best_score;
          get_element(i, j) = 0;
          if (alfa >= beta)
            return best_score;
        }
      }
    }
  }
  return best_score;
}

double Game::calculate() {
  double score = 0;
  for (int i = 0; i < size_of_map; ++i) {
    double tmp = 0;
    for (int j = 0; j < size_of_map; ++j) {
      if (get_element_value(i, j) == 2) // bot
      {
        tmp++;
      } else if (get_element_value(i, j) == 0) // empty
      {
        tmp = 0;
        break;
      }
    }
    if (tmp != 0)
      score += pow(10, tmp);
  }

  for (int i = 0; i < size_of_map; ++i) {
    double tmp = 0;
    for (int j = 0; j < size_of_map; ++j) {
      if (get_element_value(j, i) == 2) { // bot
        tmp++;
      } else if (get_element_value(j, i) == 0) {
        tmp = 0;
        break;
      }
    }
    if (tmp != 0)
      score += pow(10, tmp);
  }

  double tmp = 0;
  for (int i = 0; i < size_of_map; ++i) {
    if (get_element_value(i, i) == 2) { // bot
      tmp++;
    } else if (get_element_value(i, i) == 0) {
      tmp = 0;
      break;
    }
  }
  if (tmp != 0)
    score += pow(10, tmp);

  tmp = 0;
  for (int i = 1; i < size_of_map; ++i) {
    if (get_element_value(size_of_map - i, i - 1) == 2) { // bot
      tmp++;
    } else if (get_element_value(size_of_map - i, i - 1) != 2 &&
               get_element_value(size_of_map - i, i - 1) != 0) {
      tmp = 0;
      break;
    }
  }
  if (tmp != 0)
    score += pow(10, tmp);
  return score;
}

