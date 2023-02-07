
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
        : window(game_window)
{
    srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{
    //init background
    if (!background_texture.loadFromFile("Data/Images/background.png"))
    {
        std::cout << "background texture did not load \n";
    }

    background.setTexture(background_texture);

    //init bird sprite
    if (!bird_texture.loadFromFile("Data/Images/bird.png"))
    {
        std::cout << "bird texture did not load \n";
    }

    //init text
    if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
    {
        std::cout << "font did not load \n";
    }

    //title text properties
    title_text.setString("Whack-A-Bird!");
    title_text.setFont(font);
    title_text.setCharacterSize(80);
    title_text.setFillColor(sf::Color(255,255,255,255));

    title_text.setPosition(
            window.getSize().x / 2 - title_text.getGlobalBounds().width / 2,
            window.getSize().y / 4 - title_text.getGlobalBounds().height / 2);

    //menu text properties
    play_option.setString("> Play <");
    play_option.setFont(font);
    play_option.setCharacterSize(40);
    play_option.setFillColor(sf::Color(128,128,0,255));

    play_option.setPosition(
            window.getSize().x / 2 - play_option.getGlobalBounds().width / 2 - 200,
            window.getSize().y / 2 - play_option.getGlobalBounds().height / 2);

    //quit text properties

    quit_option.setString("Quit");
    quit_option.setFont(font);
    quit_option.setCharacterSize(40);
    quit_option.setFillColor(sf::Color(128,128,0,255));

    quit_option.setPosition(
            window.getSize().x / 2 - quit_option.getGlobalBounds().width / 2 + 200,
            window.getSize().y / 2 - quit_option.getGlobalBounds().height / 2);

    //score text properties

    score_text.setString(std::to_string(score));
    score_text.setFont(font);
    score_text.setCharacterSize(40);
    score_text.setFillColor(sf::Color(0,0,0,255));

    score_text.setPosition(
            window.getSize().x - 50,
            0);

    // score text header properties

    score_text_header.setString("Score: ");
    score_text_header.setFont(font);
    score_text_header.setCharacterSize((40));
    score_text_header.setCharacterSize((40));
    score_text_header.setFillColor(sf::Color(0, 0, 0, 255));

    score_text_header.setPosition(
            window.getSize().x - 250,
            0);
    bird.setTexture(bird_texture);


    bird.setPosition(100,100);


    return true;
}

void Game::update(float dt)
{
    if (reverse)
    {
        bird.move(1.0f * speed * dt, 0);
        bird.setTextureRect(sf::IntRect(
                0, 0, bird.getLocalBounds().width, bird.getLocalBounds().height));
    }
    else
    {
        bird.move(-1.0f * speed * dt, 0);
        bird.setTextureRect(sf::IntRect(
                bird.getLocalBounds().width,
                0,
                -bird.getLocalBounds().width,
                bird.getLocalBounds().height));
    }

    if ((bird.getPosition().x > (window.getSize().x - bird.getGlobalBounds().width)) ||
        (bird.getPosition().x < 0))
    {
        reverse = !reverse;
    }

    score_text.setString(std::to_string(score));
}

void Game::render()
{
    // main menu rendering
    if (in_menu)
    {
        window.draw(title_text);
        window.draw(play_option);
        window.draw(quit_option);
    }
    else
    // main game elements to render
    {
        window.draw(background);
        window.draw(bird);
        window.draw(score_text);
        window.draw(score_text_header);
    }
}

void Game::mouseClicked(sf::Event event)
{
    //get the click position
    sf::Vector2i click = sf::Mouse::getPosition(window);

    // check if in bounds of bird Sprite
    if (collisionCheck(click, bird))
    {
        score = score + 1;
        spawn();
    }
}

void Game::keyPressed(sf::Event event)
{
    if (
            (event.key.code == sf::Keyboard::Left) ||
            (event.key.code == sf::Keyboard::Right))
    {
        play_selected = !play_selected;
        if (play_selected)
        {
            play_option.setString("> Play <");
            quit_option.setString("Quit");
        }
        else
        {
            play_option.setString("Play");
            quit_option.setString("> Quit <");
        }
    }
    else if (event.key.code == sf::Keyboard::Enter)
    {
        if (play_selected)
        {
            in_menu = false;
        }
        else
        {
            window.close();
        }
    }
}


bool Game::collisionCheck(sf::Vector2i click, sf::Sprite sprite)
{
    if (click.x > sprite.getPosition().x && click.x < sprite.getPosition().x + sprite.getGlobalBounds().width && click.y > sprite.getPosition().y && click.y < sprite.getPosition().y + sprite.getGlobalBounds().height)
    {
        return true;
    }
    return false;
}

void Game::spawn()
{
    int pos_x = std::rand() % int(window.getSize().x - bird.getGlobalBounds().width);
    int pos_y = std::rand() % int(window.getSize().y - bird.getGlobalBounds().height);
    bool ranspawn = std::rand() % 2;
    if (ranspawn) {
        bird.setPosition(pos_x, pos_y);
    }
    else
    {
        bird.setPosition(100,-200);
    }
    bool randir = std::rand() % 2;
    if (randir)
    {
        reverse = !reverse;
    }
    else
    {
        reverse = reverse;
    }
}
