#include "Engine.h"
#include "EngineTime.h"
#include "InputHandler.h"
#include "Renderer.h"
#include "ResourceManger.h"
#include "SceneManagar.h"
#include "Scene.h"
#include "IBaseScene.h"
#include <SDL_image.h>
#include <iostream>
#include <iostream>

namespace GameEngine {

    Engine::Engine(const std::string& title, int width, int height)
        : m_title(title), m_width(width), m_height(height),m_window(title, width, height) {}
    
    Engine::~Engine() {
        shutdown();
    }
    
    bool Engine::init(const std::string& resourcePath) {
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        { 
            std::cerr << "SDL_Init Error: " << SDL_GetError() << '\n'; 
            return false;
        }

        if (!m_window.Init())
        {
            SDL_Quit();
            return false;
        }
    
        GameEngine::Renderer::GetInstance().Init(m_window.GetHandle());
        GameEngine::ResourceManager::GetInstance().Init(resourcePath);
        
        SceneContext context = { &m_window };
        GameEngine::SceneManagar::GetInstance().SetSceneContext(context);
    
        srand(static_cast<unsigned int>(time(nullptr)));
    
        m_running = true;
        return true;
    }
    
    void Engine::run() {
        auto& renderer = Renderer::GetInstance();
        auto& inputHandler = InputHandler::GetInstance();
        auto& SceneManagar = SceneManagar::GetInstance();
    
        while (m_running) {
            //update Time
            GameEngine::EngineTime::Update();

            GameEngine::EngineTime::lag += GameEngine::EngineTime::GetdeltaTime();

            //Handle Input
            m_running = inputHandler.ProccesInput();
            
        
            while (GameEngine::EngineTime::lag >= GameEngine::EngineTime::GetFixedDeltaTime()) {
                
                SceneManagar.FixedUpdate();
                GameEngine::EngineTime::lag -= GameEngine::EngineTime::GetFixedDeltaTime();
            }
        
            SceneManagar.Update();
            renderer.Render(SceneManagar.GetCurrentScene());
        
        
            SDL_Delay(GameEngine::EngineTime::GetSleepTime().count());
        
        }
    }
    
    void Engine::shutdown() {
        m_window.Shutdown();
        if (SDL_WasInit(SDL_INIT_VIDEO)) SDL_Quit();
    }
}