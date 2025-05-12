#include "sudoku.h"
#include <algorithm>
#include <random>

// kiểm tra số hợp lệ
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

// điền số để tạo bảng sudoku hoàn chỉnh
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

//tạo bảng hoàn chỉnh
std::vector<std::vector<int>> generateCompleteBoard() {
    std::vector<std::vector<int>> board(4, std::vector<int>(4, 0));
    fillBoard(board, 0, 0);
    return board;
}

//xoá ngẫu nhiên n ô trong bảng
void removeRandomCells(std::vector<std::vector<int>>& board, int numEmpty) {
    std::vector<std::pair<int,int>> positions;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            positions.emplace_back(i, j);
    std::shuffle(positions.begin(), positions.end(), std::mt19937{std::random_device{}()});
    for (int i = 0; i < numEmpty; ++i)
        board[positions[i].first][positions[i].second] = 0;
}

//kiểm tra người chơi đã điền đúng chưa
bool isBoardSolvedCorrectly(const std::vector<std::vector<int>>& board) {
    // Kiểm tra từng hàng
    for (int i = 0; i < 4; ++i) {
        std::vector<int> row_values;
        for (int j = 0; j < 4; ++j) {
            if (std::find(row_values.begin(), row_values.end(), board[i][j]) != row_values.end()) {
                return false; // Trùng lặp trong hàng
            }
            row_values.push_back(board[i][j]);
        }
    }

    // Kiểm tra từng cột
    for (int j = 0; j < 4; ++j) {
        std::vector<int> col_values;
        for (int i = 0; i < 4; ++i) {
            if (std::find(col_values.begin(), col_values.end(), board[i][j]) != col_values.end()) {
                return false; // Trùng lặp trong cột
            }
            col_values.push_back(board[i][j]);
        }
    }

    // Kiểm tra từng tiểu vùng 2x2
    for (int startRow = 0; startRow < 4; startRow += 2) {
        for (int startCol = 0; startCol < 4; startCol += 2) {
            std::vector<int> block_values;
            for (int i = startRow; i < startRow + 2; ++i) {
                for (int j = startCol; j < startCol + 2; ++j) {
                    if (std::find(block_values.begin(), block_values.end(), board[i][j]) != block_values.end()) {
                        return false; // Trùng lặp trong tiểu vùng
                    }
                    block_values.push_back(board[i][j]);
                }
            }
        }
    }

    return true; // Nếu không có trùng lặp ở hàng, cột, tiểu vùng
}
