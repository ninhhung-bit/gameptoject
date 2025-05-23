#include "ui.h"
#include <string>

SDL_Renderer* renderer = nullptr;
TTF_Font* font = nullptr;
// vẽ văn bản vào vùng hình chữ nhật
void drawText(const std::string& text, SDL_Rect rect, SDL_Color color) {
    if (!font) {
        SDL_Log("Font not loaded!");
        return;
    }

    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
    if (!surface) {
        SDL_Log("Failed to create surface: %s", TTF_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);  // Giải phóng ngay sau khi tạo texture

    if (!texture) {
        SDL_Log("Failed to create texture: %s", SDL_GetError());
        return;
    }

    int textW = 0, textH = 0;
    SDL_QueryTexture(texture, nullptr, nullptr, &textW, &textH);

    SDL_Rect dstRect = {
        rect.x + (rect.w - textW) / 2,
        rect.y + (rect.h - textH) / 2,
        textW,
        textH
    };

    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
    SDL_DestroyTexture(texture);

}
// vẽ bảng sudoku và các ô lựa chọn
void drawBoard(const std::vector<Cell>& grid, const std::vector<Cell>& choices, int draggingValue, SDL_Point mousePos, bool dragging) {
    for (auto& cell : grid)  {
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderFillRect(renderer, &cell.rect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &cell.rect);
        if (cell.value != 0)
            drawText(std::to_string(cell.value), cell.rect, cell.fixed ? SDL_Color{0,0,0} : SDL_Color{0,0,255});
    }

    for (auto& ch : choices) {
        SDL_SetRenderDrawColor(renderer, 230, 230, 250, 255);
        SDL_RenderFillRect(renderer, &ch.rect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &ch.rect);
        drawText(std::to_string(ch.value), ch.rect, SDL_Color{0,0,0});
    }
     if (dragging && draggingValue != 0) {
        SDL_Rect dragRect = {mousePos.x - 25, mousePos.y - 25, 50, 50};
        drawText(std::to_string(draggingValue), dragRect, SDL_Color{255,0,0});
    }


}
