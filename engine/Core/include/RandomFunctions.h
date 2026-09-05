#ifndef GAMEENGINE_RANDOM_FUNCTIONS_H
#define GAMEENGINE_RANDOM_FUNCTIONS_H

#include <random>

namespace GameEngine
{
    class Random final
    {
    public:
        [[nodiscard]] static float RandomF()
        {
            std::uniform_real_distribution<float> dist(0.0f, 1.0f);
            return dist(s_engine);
        }

        [[nodiscard]] static float RandomF(float max)
        {
            std::uniform_real_distribution<float> dist(0.0f, max);
            return dist(s_engine);
        }

        [[nodiscard]] static float RandomF(float min, float max)
        {
            std::uniform_real_distribution<float> dist(min, max);
            return dist(s_engine);
        }

        [[nodiscard]] static int RandomI(int max)
        {
            std::uniform_int_distribution<int> dist(0, max);
            return dist(s_engine);
        }

        [[nodiscard]] static int RandomI(int min, int max)
        {
            std::uniform_int_distribution<int> dist(min, max);
            return dist(s_engine);
        }

    private:
        friend class Engine;

        static void Init()
        {
            s_engine.seed(std::random_device{}());
        }

        static inline std::mt19937 s_engine{};
    };
}

#endif //GAMEENGINE_RANDOM_FUNCTIONS_H