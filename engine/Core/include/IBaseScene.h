#ifndef Base_SCENE_H
#define Base_SCENE_H

namespace GameEngine
{
    class Scene;
    class IBaseScene
    {
    public:
        virtual void Load(Scene& Scene) = 0;
        virtual ~IBaseScene() = default;
    };
}

#endif //BASE_SCENE_H