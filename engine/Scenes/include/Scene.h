#ifndef SCENE_H
#define SCENE_H

#include "Canvas.h"
#include "GameObject.h"
#include "Renderer.h"
#include <memory>
#include <string>
#include <sys/types.h>
#include <vector>
#include "SceneManagar.h"
#include "CollisionHandler.h"

namespace GameEngine{

    class Scene final{

        friend Scene& SceneManagar::CreateScene(const std::string& name, std::unique_ptr<IBaseScene> load);
    public:
        //Scene(const std::string& name);

        ///Only adds if the canvas pointer is nullptr atm
        bool AddCanvas(std::unique_ptr<Canvas> Canvas);
        ///Always adds; replaces any existing canvas
        void AggressiveAddCanvas(std::unique_ptr<Canvas> Canvas);
        ///Removes and returns ownership of the canvas (may be null)
        std::unique_ptr<Canvas> RemoveCanvas();
        bool HasCanvas();
        Canvas* GetCanvas();

        CollisionHandler* GetCollisionHandler() const {return m_CollisionHandler.get();}

        void AddObject(std::unique_ptr<GameObject> object);
        void RemoveObject(std::unique_ptr<GameObject> object);

        void RemoveAll();
        void LoadInScene();

        void FixedUpdate();
        void Update();
        void Render() const;

        unsigned int GetId(){return m_id;}
        const std::string& GetName(){return m_name;}

        const SceneContext& GetSceneContext(){return m_SceneContext;}
    
    private:
        explicit Scene(const std::string& name, std::unique_ptr<IBaseScene> load, const SceneContext& SceneContext);

        std::unique_ptr<IBaseScene> m_Load;

        std::vector<std::unique_ptr<GameObject>> m_sceneObjects{};
        std::unique_ptr<Canvas> m_canvas{};
        std::unique_ptr<CollisionHandler> m_CollisionHandler{};

        std::string m_name{};
        unsigned int m_id{};

        static unsigned int s_idCounter;

        const SceneContext& m_SceneContext;
        

    public:
        ~Scene() = default;
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;
    };
}

#endif //SCENE_H