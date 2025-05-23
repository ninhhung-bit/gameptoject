#include <SDL.h>
#include<iostream>
#include <SDL_ttf.h>
#include <vector>
#include <string>
#include "sudoku.h"
#include "cell.h"
#include "ui.h"

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 500;

SDL_Window* window = nullptr;

std::vector<Cell> gridCells;
std::vector<Cell> numberChoices;
std::vector<std::vector<int>> solution;
std::vector<std::vector<int>> currentBoard;
// tạo bảng hoàn chỉnh, xoá ngẫu nhiên 1 số ô
void initBoard() {
    solution = generateCompleteBoard();
    currentBoard = solution;
    removeRandomCells(currentBoard, 6);

    gridCells.clear();
    int cellSize = 80;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j) {
            Cell cell;
            cell.row = i;
            cell.col = j;
            cell.value = currentBoard[i][j];
            cell.fixed = (cell.value != 0);
            cell.rect = { j * cellSize + 40, i * cellSize + 100, cellSize - 5, cellSize - 5 };
            gridCells.push_back(cell);
        }

    numberChoices.clear();
    for (int i = 1; i <= 4; ++i) {
        Cell ch;
        ch.value = i;
        ch.fixed = true;
        ch.rect = { i * 80 - 50, 20, 50, 50 };
        numberChoices.push_back(ch);
    }
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    if (TTF_Init() == -1) {
        throw std::runtime_error("Fail to initialize SDL_ttf! TTF ERROR: " + std::string(TTF_GetError()));
    }

    window = SDL_CreateWindow("Sudoku 4x4 SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    ::renderer = renderer;

    char* basePath = SDL_GetBasePath();
    SDL_Log("Running from: %s", basePath);
    SDL_free(basePath);
    font = TTF_OpenFont("arial.ttf", 24);

    if (!font) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
    }

    ::font = font;


    if (font == NULL) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        throw std::runtime_error("Failed to load font");
    }


    initBoard();

    bool running = true;
    bool dragging = false;
    int draggingValue = 0;
    SDL_Point mousePos;

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT: running = false; break;

                    // chuột
                case SDL_MOUSEBUTTONDOWN:
                    mousePos.x = e.button.x;
                    mousePos.y = e.button.y;
                    for (auto& ch : numberChoices) {
                        if (SDL_PointInRect(&mousePos, &ch.rect)) {
                            dragging = true;
                            draggingValue = ch.value;
                        }
                    }
                    break;

                case SDL_MOUSEBUTTONUP:
                    if (dragging) {
                        for (auto& cell : gridCells) {
                            if (!cell.fixed && SDL_PointInRect(&mousePos, &cell.rect)) {
                                cell.value = draggingValue;
                                currentBoard[cell.row][cell.col] = draggingValue;
                                break;
                            }
                        }
                        dragging = false;
                        draggingValue = 0;
                    }

                    if (mousePos.y > 440 && mousePos.x > 40 && mousePos.x < 160) {
                        if (isBoardSolvedCorrectly(currentBoard)) SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "you winn!!", ":33 đúng rồi đoáa!", window);
                        else SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Oopps!", "Sai rùi bạn eiii :((", window);
                    }

                    if (mousePos.y > 440 && mousePos.x > 220 && mousePos.x < 360) {
                        initBoard();
                    }

                    break;
                    //con trỏ chuột
                case SDL_MOUSEMOTION:
                    mousePos.x = e.motion.x;
                    mousePos.y = e.motion.y;
                    break;
            }
        }


        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        drawBoard(gridCells, numberChoices, draggingValue, mousePos, dragging);
		


        SDL_Rect checkBtn = { 40, 440, 120, 40 };
        SDL_SetRenderDrawColor(renderer, 200, 255, 200, 255);
        SDL_RenderFillRect(renderer, &checkBtn);
        drawText("Test!", checkBtn, {0, 0, 0});


        SDL_Rect resetBtn = { 220, 440, 120, 40 };
        SDL_SetRenderDrawColor(renderer, 255, 200, 200, 255);
        SDL_RenderFillRect(renderer, &resetBtn);
        drawText("Play again!", resetBtn, {0, 0, 0});

        SDL_RenderPresent(renderer);


        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
