#include <sstream>
#include <SFML/Graphics.hpp>
#include <iostream>

const sf::Keyboard::Key controls[8] = {
    sf::Keyboard::W,   // Player Up
    sf::Keyboard::S,   // Player Down
    sf::Keyboard::A,   // Player Left
    sf::Keyboard::D,   // Player Right
    sf::Keyboard::Up,  // Player Up
    sf::Keyboard::Down, // Player Down
	sf::Keyboard::Left,  // Player Left
	sf::Keyboard::Right  // Player Right
};

//Parameters
const sf::Vector2f paddle_size(25.f, 100.f);
const float ball_radius = 10.f;
const int game_width = 800;
const int game_height = 600;
const float paddle_speed = 400.f;
const float paddle_offset_wall = 10.f;
const float time_step = 0.017f; //60 fps

sf::Vector2f fish_velocity;
bool is_player_serving = true;
const float initial_velocity_x = 100.f;
const float initial_velocity_y = 60.f;
const float velocity_multiplier = 1.1f;

int score[2] = { 0,0 };

//Objects of the game
//sf::CircleShape fish;
//sf::RectangleShape hook;
sf::Text text;
sf::Font font;

sf::Texture spritesheet;
sf::Sprite hook;
sf::Sprite fish;


void reset() {
    fish_velocity = { (is_player_serving ? initial_velocity_x : -initial_velocity_x), initial_velocity_y };

    // reset paddle position
    hook.setPosition(paddle_offset_wall + paddle_size.x + ball_radius * 2.f, game_height / 2.f);
    // reset Ball Position in the centre of the left paddle
    fish.setPosition(paddle_offset_wall + paddle_size.x + ball_radius * 2.f, game_height / 2.f);

    // Update Score Text
    std::stringstream sstr;
    sstr << score[0] << " - " << score[1];
    text.setString(sstr.str());
    // Keep Score Text Centered
    text.setPosition((game_width * .5f) - (text.getLocalBounds().width * .5f), 0);
}

void init() {
    if (!spritesheet.loadFromFile("C:/Users/evehc/OneDrive/Desktop/uniyear3/games_engineering/cwrepos/pull0/resources/img/fish_sheet.png")) {
        std::cerr << "Failed to load spritesheet!" << std::endl;
    }
    hook.setTexture(spritesheet);
    hook.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(64, 64))); 

    fish.setTexture(spritesheet);
    fish.setTextureRect(sf::IntRect(sf::Vector2i(65, 0), sf::Vector2i(64, 64)));

    // Set size and origin of paddles
    //hook.setSize(paddle_size);
    hook.setOrigin(paddle_size / 2.f);
    // Set size and origin of ball
    //fish.setRadius(ball_radius);
    fish.setOrigin(ball_radius, ball_radius); //Should be half the ball width and height

    // Load font-face from res dir
    font.loadFromFile("C:/Users/evehc/OneDrive/Desktop/uniyear3/games_engineering/cwrepos/pull0/resources/fonts/RobotoMono-Regular.ttf"); //not good
    // Set text element to use font
    text.setFont(font);
    // set the character size to 24 pixels
    text.setCharacterSize(24);
    text.setColor(sf::Color(255, 255, 255));
    reset();
}


void update(float dt) {


    // handle paddle movement
    sf::Vector2f direction(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(controls[0]) || sf::Keyboard::isKeyPressed(controls[4]) &&
        hook.getPosition().y > paddle_size.y / 2.f) {
        direction.y--;
    }
    if (sf::Keyboard::isKeyPressed(controls[1]) || sf::Keyboard::isKeyPressed(controls[5]) &&
        hook.getPosition().y < game_height - paddle_size.y / 2.f) {
        direction.y++;
    }
    if (sf::Keyboard::isKeyPressed(controls[2]) || sf::Keyboard::isKeyPressed(controls[6]) &&
        hook.getPosition().x > paddle_size.x / 2.f) {
        direction.x--;
    }
    if (sf::Keyboard::isKeyPressed(controls[3]) || sf::Keyboard::isKeyPressed(controls[7]) &&
        hook.getPosition().x < game_width - paddle_size.x / 2.f) {
        direction.x++;
    }

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0.0f) {
        direction /= length;
    }

    hook.move(sf::Vector2f(direction.x * paddle_speed * dt, direction.y * paddle_speed * dt));

    fish.move(fish_velocity * dt);

    // check ball collision
    const float bx = fish.getPosition().x;
    const float by = fish.getPosition().y;
    if (by > game_height) {
        // bottom wall
        fish_velocity.x *= velocity_multiplier;
        fish_velocity.y *= -velocity_multiplier;
        fish.move(sf::Vector2f(0.f, -10.f));
    }
    else if (by < 0) {
        // top wall
        fish_velocity.x *= velocity_multiplier;
        fish_velocity.y *= -velocity_multiplier;
        fish.move(sf::Vector2f(0.f, 10.f));
    }
    if (bx < 0) {
        // left wall
        fish_velocity.x *= -velocity_multiplier;
        fish_velocity.y *= velocity_multiplier;
        fish.move(sf::Vector2f(10.f, 0.f));
    }
    else if (bx > game_width) {
        // right wall
        fish_velocity.x *= -velocity_multiplier;
        fish_velocity.y *= velocity_multiplier;
        fish.move(sf::Vector2f(-10.f, 0.f));
    }

    else if (
        //ball is inline or behind paddle AND
        bx < paddle_size.x + paddle_offset_wall &&
        //ball is below top edge of paddle AND
        by > hook.getPosition().y - (paddle_size.y * 0.5) &&
        //ball is above bottom edge of paddle
        by < hook.getPosition().y + (paddle_size.y * 0.5)) {
        //bounces off left paddle
        fish_velocity.x *= -velocity_multiplier;
        fish_velocity.y *= velocity_multiplier;
        fish.move(sf::Vector2f(+10.f, 0));
    }
    else if (
        //ball is inline or behind paddle AND
        bx > game_width - paddle_size.x - paddle_offset_wall &&
        //ball is below top edge of paddle AND
        by > hook.getPosition().y - (paddle_size.y * 0.5) &&
        //ball is above bottom edge of paddle
        by < hook.getPosition().y + (paddle_size.y * 0.5)) {
        // bounce off right paddle
        fish_velocity.x *= -velocity_multiplier;
        fish_velocity.y *= velocity_multiplier;
        fish.move(sf::Vector2f(-10.f, 0));
    }
}



void render(sf::RenderWindow& window) {
    // Draw Everything
    window.draw(hook);
    window.draw(fish);
    window.draw(text);
}

int main() {
    sf::RenderWindow window(sf::VideoMode({ game_width, game_height }), "FIH");
    window.setVerticalSyncEnabled(true);
    init();
    //initialise and load
    while (window.isOpen()) {
        // Reset clock, recalculate deltatime
        static sf::Clock clock;
        float dt = clock.restart().asSeconds();
        // check and consume events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return 0;
            }
        }
        // Quit Via ESC Key
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        window.clear();
        update(dt);
        render(window);
        //wait for the time_step to finish before displaying the next frame.
        sf::sleep(sf::seconds(time_step));
        //Wait for Vsync
        window.display();
    }
    return 0;
}