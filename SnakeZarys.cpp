#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include <vector>

const int WIDTH = 800;
const int HEIGHT = 600;
const int GRID_SIZE = 20;

struct SnakeSegment {
    int x, y;
};

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class SnakeGame {
public:
    SnakeGame();
    void runGameLoop();

private:
    void initialize();
    void update();
    void render();
    void handleInput();
    void generateFood();
    bool checkCollision();
    void gameOver();

    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE* eventQueue;
    ALLEGRO_TIMER* timer;
    ALLEGRO_FONT* font;

    std::vector<SnakeSegment> snake;
    Direction currentDirection;
    int foodX, foodY;
};

SnakeGame::SnakeGame() {
    initialize();
}

void SnakeGame::initialize() {
    if (!al_init() || !al_install_keyboard() || !al_init_primitives_addon() ||
        !al_init_font_addon() || !al_init_ttf_addon()) {
        std::cerr << "Failed to initialize Allegro!" << std::endl;
        exit(EXIT_FAILURE);
    }

    display = al_create_display(WIDTH, HEIGHT);
    if (!display) {
        std::cerr << "Failed to create display!" << std::endl;
        exit(EXIT_FAILURE);
    }

    al_set_window_title(display, "Snake Game");

    eventQueue = al_create_event_queue();
    timer = al_create_timer(1.0 / 10); // 10 frames per second
    font = al_load_ttf_font("arial.ttf", 24, 0);

    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_register_event_source(eventQueue, al_get_timer_event_source(timer));
    al_register_event_source(eventQueue, al_get_display_event_source(display));

    // Initialize the snake
    snake.push_back({ WIDTH / 2, HEIGHT / 2 });
    currentDirection = RIGHT;

    // Initialize the first food
    generateFood();

    al_start_timer(timer);
}

void SnakeGame::runGameLoop() {
    bool redraw = true;
    bool exitGame = false;

    while (!exitGame) {
        ALLEGRO_EVENT event;
        al_wait_for_event(eventQueue, &event);

        if (event.type == ALLEGRO_EVENT_TIMER) {
            update();
            redraw = true;
        }
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            exitGame = true;
        }
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                exitGame = true;
            }
            handleInput();
        }

        if (redraw && al_is_event_queue_empty(eventQueue)) {
            render();
            redraw = false;
        }
    }
}

void SnakeGame::update() {
    // Move the snake
    int headX = snake.front().x;
    int headY = snake.front().y;

    switch (currentDirection) {
    case UP:
        headY -= GRID_SIZE;
        break;
    case DOWN:
        headY += GRID_SIZE;
        break;
    case LEFT:
        headX -= GRID_SIZE;
        break;
    case RIGHT:
        headX += GRID_SIZE;
        break;
    }

    // Check for collisions
    if (headX < 0 || headX >= WIDTH || headY < 0 || headY >= HEIGHT || checkCollision()) {
        gameOver();
        return;
    }

    // Check if the snake has eaten the food
    if (headX == foodX && headY == foodY) {
        generateFood();
    }
    else {
        // If not, remove the tail segment
        snake.pop_back();
    }

    // Add the new head
    snake.insert(snake.begin(), { headX, headY });
}

void SnakeGame::render() {
    al_clear_to_color(al_map_rgb(0, 0, 0));

    // Draw the snake
    al_draw_filled_rectangle(snake.front().x, snake.front().y,
        snake.front().x + GRID_SIZE, snake.front().y + GRID_SIZE,
        al_map_rgb(0, 255, 0));

    for (size_t i = 1; i < snake.size(); ++i) {
        al_draw_filled_rectangle(snake[i].x, snake[i].y,
            snake[i].x + GRID_SIZE, snake[i].y + GRID_SIZE,
            al_map_rgb(0, 128, 0));
    }

    // Draw the food
    al_draw_filled_rectangle(foodX, foodY, foodX + GRID_SIZE, foodY + GRID_SIZE, al_map_rgb(255, 0, 0));

    al_flip_display();
}

void SnakeGame::handleInput() {
    ALLEGRO_KEYBOARD_STATE keyState;
    al_get_keyboard_state(&keyState);

    if (al_key_down(&keyState, ALLEGRO_KEY_UP) && currentDirection != DOWN) {
        currentDirection = UP;
    }
    else if (al_key_down(&keyState, ALLEGRO_KEY_DOWN) && currentDirection != UP) {
        currentDirection = DOWN;
    }
    else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT) && currentDirection != RIGHT) {
        currentDirection = LEFT;
    }
    else if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT) && currentDirection != LEFT) {
        currentDirection = RIGHT;
    }
}

void SnakeGame::generateFood() {
    bool validPosition = false;

    while (!validPosition) {
        validPosition = true; // Zakładamy, że nowa pozycja jest poprawna, dopóki nie udowodnimy przeciwnego.

        foodX = (rand() % (WIDTH / GRID_SIZE)) * GRID_SIZE;
        foodY = (rand() % (HEIGHT / GRID_SIZE)) * GRID_SIZE;

        // Sprawdzamy, czy nowa pozycja jedzenia nie znajduje się na ciele węża.
        for (const auto& segment : snake) {
            if (foodX == segment.x && foodY == segment.y) {
                validPosition = false;
                break;
            }
        }
    }
}

bool SnakeGame::checkCollision() {
    int headX = snake.front().x;
    int headY = snake.front().y;

    // Check collision with the snake's body
    for (size_t i = 1; i < snake.size(); ++i) {
        if (headX == snake[i].x && headY == snake[i].y) {
            return true;
        }
    }

    return false;
}

void SnakeGame::gameOver() {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "Game Over!");
    al_flip_display();
    al_rest(2); // Pause for 2 seconds before exiting

    al_destroy_display(display);
    al_destroy_event_queue(eventQueue);
    al_destroy_timer(timer);
    al_destroy_font(font);

    exit(EXIT_SUCCESS);
}

int main() {
    SnakeGame snakeGame;
    snakeGame.runGameLoop();

    return 0;
}
