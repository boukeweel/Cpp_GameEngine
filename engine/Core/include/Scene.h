#ifndef SCENE_H
#define SCENE_H

#include "Canvas.h"
#include "GameObject.h"
#include "Renderer.h"
#include <memory>
#include <string>
#include <sys/types.h>
#include <vector>

namespace GameEngine{

    class Scene final{
    public:
        Scene(const std::string& name);

        ///Only adds if the canvas pointer is nullptr atm
        bool AddCanvas(std::unique_ptr<Canvas> Canvas);
        ///Always adds; replaces any existing canvas
        void AggressiveAddCanvas(std::unique_ptr<Canvas> Canvas);
        ///Removes and returns ownership of the canvas (may be null)
        std::unique_ptr<Canvas> RemoveCanvas();
        bool HasCanvas();
        Canvas* GetCanvas();

        void AddObject(std::unique_ptr<GameObject> object);
        void RemoveObject(std::unique_ptr<GameObject> object);

        void RemoveAll();
        void LoadInScene();

        void FixedUpdate();
        void Update();
        void Render() const;

        unsigned int GetId(){return m_id;}
        const std::string& GetName(){return m_name;}
    
    private:
        std::vector<std::unique_ptr<GameObject>> m_sceneObjects{};
        std::unique_ptr<Canvas> m_canvas{};

        std::string m_name{};
        unsigned int m_id{};

        static unsigned int s_idCounter;

    public:
        ~Scene() = default;
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;
    };
}

#endif //SCENE_H