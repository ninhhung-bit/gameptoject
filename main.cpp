/*
1. ban đầu có một mảng 2 chiều 4*4, chứa các số từ 1 đến 4
2. những vị trí 0 là tượng trung cho chỗ trống
3. người chơi sẽ thay thế các vị trí có số 0 bằng các số trong khoảng từ (1 đến 4)
4. yêu cầu là các hàng và các cột có số không trùng lặp , và trong bốn ô kích thước
2*2 ở bốn góc cũng có số không trùng lặp
5. phiên bản hiện tại (4*4), bản khó hơn sẽ là (9*9)
*/


#include <iostream>

using namespace std;

const int SIZE = 4;
int board[SIZE][SIZE] = {
    {1, 0, 0, 4},
    {0, 4, 0, 0},
    {0, 0, 4, 3},
    {4, 0, 0, 1}
};
void printBoard() {

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0)
                cout << ". ";
            else
                cout << board[i][j] << " ";
        }
        cout << endl;
    }
}


bool isValid(int row, int col, int num) {

    for (int i = 0; i < SIZE; i++)
        if (board[row][i] == num) return false;

    for (int i = 0; i < SIZE; i++)
        if (board[i][col] == num) return false;

    int startRow = (row / 2) * 2;
    int startCol = (col / 2) * 2;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            if (board[startRow + i][startCol + j] == num) return false;

    return true;
}

void playerMove()
 {
    int row, col, num;
    cout << "nhap hang (0-3), cot (0-3), so (1-4): ";
    cin >> row >> col >> num;

    if (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == 0)
    {
        if (isValid(row, col, num))
          {
            board[row][col] = num;
          } else
          {
            cout << "so khong hop le"<<endl;
          }
    } else
      {
        cout << "o nay khong the thay doi!"<< endl;
      }
}

bool isGameWon()
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] == 0) return false;
    return true;
}

int main()
{
    while(!isGameWon())
    {
        printBoard();
        playerMove();
    }
    cout<< "Chúc mừng!!"<< endl;
    return 0;
}


