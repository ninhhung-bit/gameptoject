#include "sudoku.h"
#include <algorithm>
#include <random>

bool isValid(const std::vector<std::vector<int>>& board, int row, int col, int num) {
    for (int i = 0; i < 4; ++i) {
        if (board[row][i] == num || board[i][col] == num)
            return false;
    }
    int startRow = row / 2 * 2, startCol = col / 2 * 2;
    for (int i = startRow; i < startRow + 2; ++i)
        for (int j = startCol; j < startCol + 2; ++j)
            if (board[i][j] == num)
                return false;
    return true;
}

bool fillBoard(std::vector<std::vector<int>>& board, int row, int col) {
    if (row == 4) return true;
    int nextRow = (col == 3) ? row + 1 : row;
    int nextCol = (col + 1) % 4;
    std::vector<int> nums = {1,2,3,4};
    std::shuffle(nums.begin(), nums.end(), std::mt19937{std::random_device{}()});
    for (int num : nums) {
        if (isValid(board, row, col, num)) {
            board[row][col] = num;
            if (fillBoard(board, nextRow, nextCol)) return true;
            board[row][col] = 0;
        }
    }
    return false;
}

std::vector<std::vector<int>> generateCompleteBoard() {
    std::vector<std::vector<int>> board(4, std::vector<int>(4, 0));
    fillBoard(board, 0, 0);
    return board;
}

void removeRandomCells(std::vector<std::vector<int>>& board, int numEmpty) {
    std::vector<std::pair<int,int>> positions;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            positions.emplace_back(i, j);
    std::shuffle(positions.begin(), positions.end(), std::mt19937{std::random_device{}()});
    for (int i = 0; i < numEmpty; ++i)
        board[positions[i].first][positions[i].second] = 0;
}

bool isBoardSolvedCorrectly(const std::vector<std::vector<int>>& board) {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (board[i][j] == 0 || !isValid(board, i, j, board[i][j]))
                return false;
    return true;
}
