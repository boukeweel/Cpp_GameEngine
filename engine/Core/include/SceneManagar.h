#ifndef SCENE_MANAGAR_H
#define SCENE_MANAGAR_H

#include "Singleton.h"
#include <vector>
#include <memory>

namespace GameEngine{
    class Scene;
    class IBaseScene;
    class IWindowInfo;

    struct SceneContext
    {
       const IWindowInfo* window = nullptr;
    };

    class SceneManagar : public Singleton<SceneManagar>
    {
    public:
        void SetSceneContext(SceneContext SceneContext);    

        Scene& CreateScene(const std::string& name, std::unique_ptr<IBaseScene> load);
        void LoadScene(unsigned int IdScene);
        //void LoadScene(Const std::string& name);

        Scene& GetCurrentScene() const { return *m_Scenes[m_CurrentScene]; }
		unsigned int GetCurrentSceneId() const { return m_CurrentScene; }

        void FixedUpdate();
        void Update();
        void Render() const;
    private:
        std::vector<std::unique_ptr<Scene>> m_Scenes{};

        SceneContext m_SceneContext;

        unsigned int m_CurrentScene{0};
    };
}
#endif //SCENE_MANAGAR_H