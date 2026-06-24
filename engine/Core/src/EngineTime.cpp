#include "EngineTime.h"

void GameEngine::EngineTime::Update() {
    s_CurrentTime = std::chrono::high_resolution_clock::now();
    s_DeltaTime = std::chrono::duration<double>(s_CurrentTime - s_LastTime).count();
    s_LastTime = s_CurrentTime;

    if (s_DeltaTime > s_MaxDeltatTime) {
        s_DeltaTime = s_MaxDeltatTime;
    }
}
