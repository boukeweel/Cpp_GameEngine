#include "Engine.h"
#include "EngineTime.h"
#include "Renderer.h"
#include "ResourceManger.h"
#include "Scene.h"
#include <SDL_image.h>
#include <iostream>

namespace GameEngine {

    Engine::Engine(const std::string& title, int width, int height)
        : m_title(title), m_width(width), m_height(height) {
    }
    
    Engine::~Engine() {
        shutdown();
    }
    
    bool Engine::init(const std::string& resourcePath) {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::cerr << "SDL_Init Error: " << SDL_GetError() << '\n';
            return false;
        }
    
        m_window = SDL_CreateWindow(
            m_title.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            m_width,
            m_height,
            SDL_WINDOW_SHOWN
        );
    
        if (!m_window) {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << '\n';
            SDL_Quit();
            return false;
        }
    
        GameEngine::Renderer::GetInstance().Init(m_window);
        GameEngine::ResourceManager::GetInstance().Init(resourcePath);

        m_currentScene = std::make_unique<Scene>("Default Scene");
    
        srand(static_cast<unsigned int>(time(nullptr)));
    
        m_running = true;
        return true;
    }
    
    void Engine::run() {

        
        auto& renderer = GameEngine::Renderer::GetInstance();

        if (!m_currentScene) {
            m_currentScene = std::make_unique<Scene>("Default Scene");
        }
    
        while (m_running) {
            GameEngine::EngineTime::Update();
            GameEngine::EngineTime::lag += GameEngine::EngineTime::deltaTime();
        
        
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    m_running = false;
                }
            }
        
            while (GameEngine::EngineTime::lag >= GameEngine::EngineTime::GetFixedDeltaTime()) {
                
                m_currentScene->FixedUpdate();
            
                GameEngine::EngineTime::lag -= GameEngine::EngineTime::GetFixedDeltaTime();
            }
        
            m_currentScene->Update();
            renderer.Render(*m_currentScene);
        
        
            SDL_Delay(GameEngine::EngineTime::GetSleepTime().count());
        
        }
    }
    
    void Engine::shutdown() {
        if (m_window) {
            SDL_DestroyWindow(m_window);
            m_window = nullptr;
        }
        if (SDL_WasInit(SDL_INIT_VIDEO)) {
            SDL_Quit();
        }
    }
}