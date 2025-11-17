#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <TGUI/TGUI.hpp>

// add libraries here
#include "./grid.h"


class SFMLWindow
{
    public:
        SFMLWindow(int width, int height, std::string title);
        void LoadTGUIWidgets(tgui::GuiBase& gui, Grid* grid_ptr);
        void LoadSFMLWidgets(sf::RenderWindow& window);
        void CreateLegendLabel(tgui::GuiBase& gui, std::string text, int size, int x, int y);
        void CreateLegendTile(sf::RenderWindow& window, int length, int width, int r, int g, int b, int x, int y);

        // test
        void ChangeBackground(sf::RenderWindow& window);
        void PrintStatement();
};