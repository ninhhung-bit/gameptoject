/*
1. ban đầu có một mảng 2 chiều 4*4, chứa các số từ 1 đến 4
2. những vị trí 0 là tượng trung cho chỗ trống
3. người chơi sẽ thay thế các vị trí có số 0 bằng các số trong khoảng từ (1 đến 4)
4. yêu cầu là các hàng và các cột có số không trùng lặp , và trong bốn ô kích thước
2*2 ở bốn góc cũng có số không trùng lặp
5. phiên bản hiện tại (4*4), bản khó hơn sẽ là (9*9)
*/


#include <iostream>
#include<cstdlib>
#include<algorithm>
#include<ctime>

using namespace std;

const int SIZE = 4;
int baseBoard[SIZE][SIZE] = {
    {1, 2, 3, 4},
    {3, 4, 1, 2},
    {2, 1, 4, 3},
    {4, 3, 2, 1}
};
int fullBoard[4][4];
int board[4][4];

void ngaunhienBoard( int board[4][4]){

    for(int i=0;i<4;i+=2){
        if(rand()%2) swap(board[i],board[i+1]);
    }

    for (int j = 0; j < 4; j += 2) {
        if (rand() % 2) {
            for (int i = 0; i < 4; i++) {
                swap(board[i][j], board[i][j+1]);
            }
        }
    }
    int map[5]={0,1,2,3,4};
    random_shuffle(map+1,map+5);
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++)
        {
            board[i][j]= map[board[i][j]];
        }
    }
}

void anchuso( int src[4][4], int dst[4][4], int blanks=6){

    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            dst[i][j]=src[i][j];
        }
    }

    while (blanks>0){
        int r=rand()% 4;
        int c=rand()% 4;
        if(dst[r][c] !=0 ){
            dst[r][c]=0;
            blanks--;
        }
    }
}

void printBoard() {
    system("cls");

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
    cout << "nhap hang (1-4), cot (1-4), so (1-4): ";
    cin >> row >> col >> num;

    if (row >= 1 && row < SIZE+1 && col >= 1 && col < SIZE+1 && board[row-1][col-1] == 0)
    {
        if (isValid(row-1, col-1, num))
          {
            board[row-1][col-1] = num;
          } else{
            cout << "so khong hop le"<<endl;

          }
    } else{
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
    srand(time (0));

    memcpy(fullBoard, baseBoard, sizeof(baseBoard));
    ngaunhienBoard(fullBoard);
    anchuso(fullBoard, board,6);

    while(!isGameWon())
    {
        printBoard();
        playerMove();

    }
    cout<< "Chuc mungg bann!!"<<endl;
    return 0;
}


