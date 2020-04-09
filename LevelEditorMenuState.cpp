#include "LevelEditorMenuState.hpp"
#include "MainMenuState.hpp"

#include <fstream>


LevelEditorMenuState::LevelEditorMenuState(std::shared_ptr<gameData> data):
    _data(data)
{
}

LevelEditorMenuState::LevelEditorMenuState(std::shared_ptr<gameData> data,std::vector<field>& vec):
    _data(data),
    _rectangles(vec)
{
    this->_data->asset.loadTexture("continueEditor","img/Continue.png");
    this->_data->asset.loadTexture("mainMenu","img/MMenu.png");
    this->_data->asset.loadTexture("saveAndExit","img/saveAE.png");

    _continue.init(this->_data->width/2,(this->_data->height/2)-200,this->_data->asset.getTexture("continueEditor"));
    _saveAndExitButton.init(this->_data->width/2,(this->_data->height/2),this->_data->asset.getTexture("saveAndExit"));
    _exitButton.init(this->_data->width/2,(this->_data->height/2) + 200,this->_data->asset.getTexture("mainMenu"));
}

void LevelEditorMenuState::init()
{
}

void LevelEditorMenuState::handleInput()
{
    sf::Event event;
    while(this->_data->window.pollEvent(event)){
        if(event.type==sf::Event::Closed){
            this->_data->window.close();
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
        this->_data->machine.eraseState();
    }
}

void LevelEditorMenuState::update(float dt)
{
    _mousePosition = sf::Mouse::getPosition(this->_data->window);

    if(_saveAndExitButton.hover(this->_data->window))
        _saveAndExitButton.setTexture(this->_data->asset.getTexture("saveAndExit"));
    else
        _saveAndExitButton.setTexture(this->_data->asset.getTexture("saveAndExit"));

    if(_exitButton.hover(this->_data->window))
        _exitButton.setTexture(this->_data->asset.getTexture("mainMenu"));
    else
        _exitButton.setTexture(this->_data->asset.getTexture("mainMenu"));

    if(_continue.hover(this->_data->window))
        _saveAndExitButton.setTexture(this->_data->asset.getTexture("continueEditor"));
    else
        _continue.setTexture(this->_data->asset.getTexture("continueEditor"));

    if(_exitButton.pressed(this->_data->window,sf::Mouse::Left)){
        this->_data->machine.eraseState();
        this->_data->machine.addState(std::unique_ptr<State>(std::make_unique<MainMenuState>(this->_data)));
    }

    if(_continue.pressed(this->_data->window,sf::Mouse::Left)){
        this->_data->machine.eraseState();
    }

    if(_saveAndExitButton.pressed(this->_data->window,sf::Mouse::Left)){
        std::fstream testFile;
        int num;
        std::string levelNumber;

        testFile.open( "level/levels.txt", std::ios::in );
            testFile>>num;
        testFile.close();
        ++num;

        testFile.open( "level/levels.txt", std::ios::out );
            testFile<<num;
        testFile.close();

        testFile.open( "level/levels.txt", std::ios::in );
            testFile>>levelNumber;
        testFile.close();

        testFile.open( "level/level"+levelNumber+".txt", std::ios::out );

        for(int i=0; i<this->_rectangles.size(); ++i){
            if(_rectangles[i].type!=EMPTY)
                testFile << _rectangles[i].type<<" "<<_rectangles[i].posX<<" "<<_rectangles[i].posY<<"\n";
        }

        testFile.close();

        this->_data->machine.eraseState();
        this->_data->machine.addState(std::unique_ptr<State>(std::make_unique<MainMenuState>(this->_data)));
    }
}

void LevelEditorMenuState::draw(float dt)
{
    this->_data->window.clear(sf::Color(100,100,100));

    _continue.draw(  this->_data->window);
    _saveAndExitButton.draw(  this->_data->window);
    _exitButton.draw(  this->_data->window);

    this->_data->window.display();
}
