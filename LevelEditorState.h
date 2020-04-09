#pragma once
#include "Game.hpp"
#include "Button.hpp"
#include "Player.hpp"


enum
{
    EMPTY,
    BLOCK,
    PLAYER,
    DESTINATION
}fieldType;

struct field
{
    sf::RectangleShape rec;
    int type;
    int posX;
    int posY;
};

class LevelEditorState : public State
{
public:
    LevelEditorState(std::shared_ptr<gameData> data);

    void init();

    void handleInput();
    void update(float dt);
    void draw(float dt);
private:
    std::shared_ptr<gameData> _data;
    sf::Vector2i _mousePosition;
    std::vector<field> _rectangles;
    sf::Clock _clock;
    const int BLOCK_SIZE{60};

};
