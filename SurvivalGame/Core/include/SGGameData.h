#ifndef SG_GAME_DATE_H
#define SG_GAME_DATE_H

#include "Singleton.h"
#include "GameObject.h"

namespace SurvivalGame
{
    class SGGameDate : public GameEngine::Singleton<SGGameDate>
    {
    public:
        void SetPlayer(GameEngine::GameObject* player){m_player = player;}
        GameEngine::GameObject* GetPlayer(){return m_player;}

    private:
        GameEngine::GameObject* m_player{nullptr};
    };
}

#endif