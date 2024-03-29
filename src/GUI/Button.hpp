#pragma once

#include <cstring>
#include <string>
#include <iostream>

#include "raylib.h"

class Button
{
    public:
        Button(std::string name, int posX, int posY)
        {
            this->X = posX;
            this->Y = posY;

            const int length = name.length();
            char* char_array = new char[length + 1];

            std::strcpy(char_array, name.c_str());
            Wave selectFX = LoadWave("rescources/sounds/select.wav");
            Wave clickFX = LoadWave("rescources/sounds/click.wav");

            SelectFX_AsSound = LoadSoundFromWave(selectFX);
            ClickFX_asSound = LoadSoundFromWave(clickFX);

            UnloadWave(clickFX);
            UnloadWave(selectFX);
            
            this->name = char_array;
        };


        /// @brief Render button on screen, if it's hovered, it will be in another color
        /// @param _setup function that will be executed when the button is clicked
        void Render(void (*_setup)())
        {

            DrawRectangle(X + 25, Y, 250, 75, (isHovered(GetMouseX(), GetMouseY()) ? RED : BLACK));

            DrawRectangle(X + 30, Y + 5, 240, 65, (isHovered(GetMouseX(), GetMouseY()) ? BLACK : WHITE));

            DrawText(name, X + (150 - MeasureText(name, 30) / 2), Y + 25, 30, (isHovered(GetMouseX(), GetMouseY()) ? RED : BLACK));

            if(isHovered(GetMouseX(), GetMouseY()))
            {
                if(!hovered)
                {
                    PlaySound(SelectFX_AsSound);
                }
                if(IsMouseButtonPressed(0))
                {
                    PlaySound(ClickFX_asSound);
                    onclick(_setup);
                }
            }
            hovered = isHovered(GetMouseX(), GetMouseY());
        }
    private:
        Sound SelectFX_AsSound, ClickFX_asSound;
        bool hovered;
        int X, Y;
        char* name;
        void onclick(void (*onclick)()) {onclick();};

        /// @brief Function to find 
        /// @param posX position X of the cursor
        /// @param posY position Y of the cursor
        /// @return true if hovered, false otherwise
        int isHovered(int posX, int posY)
        {
            return (posX < X + 250 && posX > X && posY < Y + 75 && posY > Y);
        };
};