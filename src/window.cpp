#include "../include/window.h"
#include "../include/grid.h"


SFMLWindow::SFMLWindow(int width, int height, std::string title)
{
    sf::RenderWindow sfml_window(sf::VideoMode(1530,900), "Pathfinder Visualizer", sf::Style::Close);

    // Create grid


    // Handle window events

    // Handle mosue events

    // update grid
}

void SFMLWindow::LoadTGUIWidgets(tgui::GuiBase& gui, Grid* grid_ptr)
{
    // Labels
    CreateLegendLabel(gui, "Algorithm Visualizer", 18, 60, 50);  // GUI title
    CreateLegendLabel(gui, "Map Generation", 15, 40, 140);  // Content label
    CreateLegendLabel(gui, "Pathfinder Algorithms", 15, 40, 320);  // Content label
    CreateLegendLabel(gui, "Legend", 15, 40, 430);  // Startpoint label
    CreateLegendLabel(gui, "Startpoint", 12, 80, 467);  // Startpoint legend label
    CreateLegendLabel(gui, "Endpoint", 12, 80, 507);  // Endpoint legend label
    CreateLegendLabel(gui, "Path", 12, 80, 547);  // Path legend label
    CreateLegendLabel(gui, "Unexplored", 12, 80, 587);  // Unxplored legend label
    CreateLegendLabel(gui, "Explored", 12, 218, 467);  // Explored legend label
    CreateLegendLabel(gui, "Wall", 12, 218, 507);  // Border legend label
    
    // Map algorithm sidenote
    auto user_note = tgui::Label::create();
    user_note->setText("Note: You can choose either to generate \na map or create your own by manually \nclicking the squares");
    user_note->getRenderer()->setTextColor(sf::Color(93,93,93));
    user_note->setTextSize(12);
    user_note->setPosition(40, 163);
    gui.add(user_note);

    // Map algorithm options
    auto map_btn = tgui::ComboBox::create();
    map_btn->addItem("Recursive Division");
    map_btn->addItem("Item 2");
    map_btn->addItem("Item 3");
    map_btn->getRenderer()->setBackgroundColor(sf::Color(213,213,213));
    map_btn->setSize(250, 25);
    map_btn->setPosition(40, 210);
    map_btn->setSelectedItem("Recursive Division");
    gui.add(map_btn);

    // Generate Map Button
    auto generate_map_btn = tgui::Button::create();
    generate_map_btn->setText("Generate Map");
    generate_map_btn->getRenderer()->setBackgroundColor(sf::Color(213,213,213));
    generate_map_btn->getRenderer()->setBorderColor(sf::Color(19,19,19));
    generate_map_btn->getRenderer()->setBackgroundColorHover(sf::Color(213,213,213,200));
    generate_map_btn->setSize(250,40);
    generate_map_btn->setPosition(40, 240);
    // *************** RECURSIVE DIVSION ALGORITHM 
    // Add button functionality
    // generate_map_btn->onPress([=]{
    //         /* grid_ptr->GenerateMazeAlgorithms(grid_ptr, maze_algo_ptr_, map_btn->getSelectedItemIndex()); */
    //         maze_algo_ptr_->RecursiveDivision(grid_ptr);
    //         });
    // gui.add(generate_map_btn);


    // Pathfinder algorithm options
    auto algo_btn = tgui::ComboBox::create();
    algo_btn->addItem("Dijkstra's Algorithm");
    algo_btn->addItem("A Search*");
    algo_btn->addItem("Greedy Best-first Search");
    algo_btn->addItem("Swarm Algorithm");
    algo_btn->addItem("Convergent Swarm Algorithm");
    algo_btn->addItem("Bidirectional Swarm Algorithm");
    algo_btn->addItem("Breath-first Search");
    algo_btn->addItem("Depth-first Search");
    algo_btn->getRenderer()->setBackgroundColor(sf::Color(213,213,213));
    algo_btn->setSize(250, 25);
    algo_btn->setPosition(40, 350);
    /* algo_btn->onPress([=]{ */
    /*         // Create pathfinding class */
    /*         }) */
    gui.add(algo_btn);
    
    // Reset maze button
    auto reset_maze_btn = tgui::Button::create();
    reset_maze_btn->setText("Clear Maze");
    reset_maze_btn->getRenderer()->setBackgroundColor(sf::Color(213,213,213));
    reset_maze_btn->getRenderer()->setBorderColor(sf::Color(19,19,19));
    reset_maze_btn->getRenderer()->setBackgroundColorHover(sf::Color(213,213,213,200));
    reset_maze_btn->setSize(125,35);
    reset_maze_btn->setPosition(40, 744);
    reset_maze_btn->onPress([=]{ 
            grid_ptr->ClearGrid();
            });
    gui.add(reset_maze_btn);
    
    // Reset path button
    auto reset_path_btn = tgui::Button::create();
    reset_path_btn->setText("Reset Path");
    reset_path_btn->getRenderer()->setBackgroundColor(sf::Color(213,213,213));
    reset_path_btn->getRenderer()->setBorderColor(sf::Color(19,19,19));
    reset_path_btn->getRenderer()->setBackgroundColorHover(sf::Color(213,213,213,200));
    reset_path_btn->setSize(125,35);
    reset_path_btn->setPosition(165, 744);
    reset_path_btn->onPress([=]{
            grid_ptr->ClearPath();
            });
    gui.add(reset_path_btn);
    
    // Start button
    auto visualize_btn = tgui::Button::create();
    visualize_btn->setText("VISUALIZE");
    visualize_btn->getRenderer()->setBackgroundColor(sf::Color(0,87,255));
    visualize_btn->getRenderer()->setBorderColor(sf::Color(19,19,19));
    visualize_btn->getRenderer()->setTextColor(sf::Color(213,213,213));
    visualize_btn->getRenderer()->setBackgroundColorHover(sf::Color(0,87,255,200));
    visualize_btn->getRenderer()->setTextColorHover(sf::Color(19,19,19,200));
    visualize_btn->setSize(250,50);
    visualize_btn->setPosition(40, 780);
    gui.add(visualize_btn);
}

void SFMLWindow::LoadSFMLWidgets(sf::RenderWindow& window)
{
    CreateLegendTile(window, 30, 30, 34, 139, 34, 43, 460);  // Startpoint tile
    CreateLegendTile(window, 30, 30, 255, 0, 4, 43, 500);  // Endpoint tile
    CreateLegendTile(window, 30, 30, 0, 87, 255, 43, 540);  // Path tile
    CreateLegendTile(window, 30, 30, 255, 255, 255, 43, 580);  // Unexplored tile
    CreateLegendTile(window, 30, 30, 220, 226, 254, 180, 460);  // Explored tile
    CreateLegendTile(window, 30, 30, 64, 64, 64, 180, 500);  // Border tile
}

void SFMLWindow::CreateLegendLabel(tgui::GuiBase& gui, std::string text, int size, int x, int y)
{
    auto lbl = tgui::Label::create();
    lbl->setText(text);
    lbl->getRenderer()->setTextColor(sf::Color(213,213,213));
    lbl->setTextSize(size);
    lbl->setSize(250, 25);
    lbl->setPosition(x, y);
    gui.add(lbl);
}

void SFMLWindow::CreateLegendTile(sf::RenderWindow& window, int length, int width, int r, int g, int b, int x, int y)
{
    sf::RectangleShape legend_tile;
    legend_tile.setSize(sf::Vector2f(length, width));
    legend_tile.setFillColor(sf::Color(r,g,b));
    legend_tile.setOutlineColor(sf::Color(19,19,19));
    legend_tile.setPosition(x, y);
    window.draw(legend_tile);
}


// // -----------------------------------------------------------------
void SFMLWindow::ChangeBackground(sf::RenderWindow& window) {
    window.clear(sf::Color::Red);
}

void SFMLWindow::PrintStatement() {
    std::cout << "hwllo world" << std::endl;
}