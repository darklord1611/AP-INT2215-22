#include<iostream>
#include<SDL2/SDL.h>
#define SDL_MAIN_HANDLED

// Colors
namespace Colors {
    const SDL_Color BLACK = {0, 0, 0, SDL_ALPHA_OPAQUE};
    const SDL_Color GREEN = {0, 255, 0, SDL_ALPHA_OPAQUE};
    
}

using namespace std;
// Graphics
namespace Graphics {
    struct Screen {
        const int WIDTH = 1200;
        const int HEIGHT = 600;
        const int center_x = WIDTH / 2;
        const int center_y = HEIGHT / 2;
    };
};

// Game objects

enum SquareState {IDLE, MOVING_UP, MOVING_DOWN, MOVING_RIGHT, MOVING_LEFT};
struct Square 
{
    int HEIGHT;
    int WIDTH;
    int x;
    int y;
    SquareState state;
    int step;
};

// Application
struct App {
    SDL_Window* window;
    SDL_Renderer* renderer;
    Graphics:: Screen screen;
    const int DEFAULT_STEP = 2;
    Square square = {32, 32, screen.center_x, screen.center_y, IDLE, DEFAULT_STEP};

} app;

// SDL rountines

bool InitSDL() 
{
    if (SDL_Init(SDL_INIT_EVERYTHING) > 0) 
    {
        cout << "SDL_Init failed with error: " << SDL_GetError() << endl;
        return false;
    }
    return true;
}

// Graphic rountines
void ClearScreen(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, Colors::BLACK.r, Colors::BLACK.g, Colors::BLACK.b, Colors::BLACK.a);
    SDL_RenderClear(renderer);
}

void drawSquare(int x, int y) 
{
    SDL_Rect rect;
    rect.x = x - (app.square.WIDTH / 2);
    rect.y = y - (app.square.HEIGHT / 2);
    rect.w = app.square.WIDTH;
    rect.h = app.square.HEIGHT;
    // Define the green color on the renderer
    SDL_SetRenderDrawColor(app.renderer, Colors::GREEN.r, Colors::GREEN.g, Colors::GREEN.b, Colors::GREEN.a);
    // Fill the triangle with green color
    SDL_RenderFillRect(app.renderer, &rect);
}

// Application routines

void setNewState(SquareState new_state) 
{
    app.square.state = new_state;
}

void increaseStep()
{
    app.square.step *= app.DEFAULT_STEP;

}

void decreaseStep() 
{
    int new_step = app.square.step / app.DEFAULT_STEP;
    if(new_step > app.DEFAULT_STEP) 
    {
        app.square.step = new_step;
    } else 
    {
        app.square.step = app.DEFAULT_STEP;
    }
}

void ShutdownApplication() {
    if(app.window != nullptr) {
        SDL_DestroyWindow(app.window);
        app.window = nullptr;
    }
    if(app.window != nullptr) {
        SDL_DestroyRenderer(app.renderer);
        app.renderer = nullptr;
    }

    SDL_Quit();
}

bool InitApplication() {
    if(InitSDL() == false) 
    {
        ShutdownApplication();
        return false;
    }
    app.window = SDL_CreateWindow(
        "SDL Create Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        app.screen.WIDTH,
        app.screen.HEIGHT,
        SDL_WINDOW_OPENGL
    );
    if(app.window == nullptr) {
        cout << "Unable to open main window: " << SDL_GetError() << endl;
        SDL_Quit();
        return false;
    }
    app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_PRESENTVSYNC);
    return true;
}

int main(int argc, char* argv[]) {
    if(InitApplication() == false) 
    {
        ShutdownApplication();
        return 1;
    }

    // Draw loop
    SDL_Event event;
    bool running = true;

    while(running) 
    {
        ClearScreen(app.renderer);

        // Check square's state
        switch(app.square.state) {
            case MOVING_LEFT:
            {
                int new_top_left_x = app.square.x - app.square.step - (app.square.WIDTH / 2);
                if(new_top_left_x > app.square.step) 
                {
                    app.square.x = app.square.x - app.square.step;
                } else 
                {
                    app.square.x = (app.square.WIDTH / 2);
                    setNewState(MOVING_RIGHT);
                }
                break;
            }
            case MOVING_UP:
            {
                int new_y = app.square.y - app.square.step;
                if(new_y > (app.square.HEIGHT / 2)) 
                {
                    app.square.y = new_y;
                } else 
                {
                    app.square.y = app.square.HEIGHT / 2;
                    setNewState(MOVING_DOWN);
                }
                break;
            }
            case MOVING_DOWN:
            {
                int new_y = app.square.y + app.square.step;
                if(new_y + (app.square.HEIGHT / 2) < app.screen.HEIGHT) 
                {
                    app.square.y = new_y;
                } else 
                {
                    app.square.y = new_y - (new_y + (app.square.HEIGHT / 2) - app.screen.HEIGHT);
                    setNewState(MOVING_UP);
                }
                break;
            }
            case MOVING_RIGHT:
            {
                int new_top_left_x = app.square.x + app.square.step;
                if(new_top_left_x + (app.square.WIDTH / 2) <= app.screen.WIDTH)
                {
                    app.square.x = app.square.x + app.square.step;
                } else 
                {
                    setNewState(MOVING_LEFT);
                }
                break;
            }
            default:
                break;
        }

        // Check and process I/O events
        if(SDL_PollEvent(&event)) 
        {
            switch (event.type) 
            {
                case SDL_KEYDOWN: 
                {
                    running = event.key.keysym.scancode != SDL_SCANCODE_ESCAPE;
                    if(event.key.keysym.scancode == SDL_SCANCODE_UP) 
                    {
                        setNewState(MOVING_UP);
                    } 
                    if(event.key.keysym.scancode == SDL_SCANCODE_DOWN) 
                    {
                        setNewState(MOVING_DOWN);
                    }
                    if(event.key.keysym.scancode == SDL_SCANCODE_RIGHT) 
                    {
                        setNewState(MOVING_RIGHT);
                    }
                    if(event.key.keysym.scancode == SDL_SCANCODE_LEFT) 
                    {
                        setNewState(MOVING_LEFT);
                    }
                    if(event.key.keysym.scancode == SDL_SCANCODE_S) 
                    {
                        setNewState(IDLE);
                    }
                    if(event.key.keysym.scancode == SDL_SCANCODE_I) 
                    {
                        increaseStep();
                    }
                    if(event.key.keysym.scancode == SDL_SCANCODE_D) 
                    {
                        decreaseStep();
                    }
                    break;
                }
                case SDL_QUIT: 
                {
                    running = false;
                    break;
                }
                default:
                    break;
            }
        }
        
        //Draw the new content on the renderer
        drawSquare(app.square.x, app.square.y);
        
        // Update the screen with the content rendered in the background buffer
        SDL_RenderPresent(app.renderer);
    }
    ShutdownApplication();
    return 0;
}