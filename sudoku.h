#ifndef SUDOKU_H_INCLUDED
#define SUDOKU_H_INCLUDED

#pragma once
#include <vector>

std::vector<std::vector<int>> generateCompleteBoard();
void removeRandomCells(std::vector<std::vector<int>>& board, int numEmpty);
bool isBoardSolvedCorrectly(const std::vector<std::vector<int>>& board);

#endif // SUDOKU_H_INCLUDED
