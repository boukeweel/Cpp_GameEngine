#include "Engine.h"
#include "EngineTime.h"
#include "Renderer.h"
#include <iostream>

namespace GameEngine {

    Engine::Engine(const std::string& title, int width, int height)
        : title_(title), width_(width), height_(height) {
    }
    
    Engine::~Engine() {
        shutdown();
    }
    
    bool Engine::init() {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::cerr << "SDL_Init Error: " << SDL_GetError() << '\n';
            return false;
        }
    
        window_ = SDL_CreateWindow(
            title_.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width_,
            height_,
            SDL_WINDOW_SHOWN
        );
    
        if (!window_) {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << '\n';
            SDL_Quit();
            return false;
        }
    
        GameEngine::Renderer::GetInstance().Init(window_);
    
        srand(static_cast<unsigned int>(time(nullptr)));
    
        running_ = true;
        return true;
    }
    
    void Engine::run() {
    
        auto& renderer = GameEngine::Renderer::GetInstance();
    
        while (running_) {
            GameEngine::EngineTime::Update();
            GameEngine::EngineTime::lag += GameEngine::EngineTime::deltaTime();
        
        
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running_ = false;
                }
            }
        
            while (GameEngine::EngineTime::lag >= GameEngine::EngineTime::GetFixedDeltaTime()) {
                
                //todo: Fixed update call here
            
                GameEngine::EngineTime::lag -= GameEngine::EngineTime::GetFixedDeltaTime();
            }
        
            //todo: Update call here
            renderer.Render();
        
        
            SDL_Delay(GameEngine::EngineTime::GetSleepTime().count());
        
        }
    }
    
    void Engine::shutdown() {
        if (window_) {
            SDL_DestroyWindow(window_);
            window_ = nullptr;
        }
        if (SDL_WasInit(SDL_INIT_VIDEO)) {
            SDL_Quit();
        }
    }
}