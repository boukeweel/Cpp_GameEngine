//
// Created by boeken on 9/1/26.
//

#ifndef GAMEENGINE_EVENT_H
#define GAMEENGINE_EVENT_H
#include <vector>
#include <utility>
#include <functional>
#include <cstddef>


namespace GameEngine {
    template<typename... Args>
    class Event {
    public:
        virtual ~Event() = default;

        std::size_t Subscribe(std::function<void(Args...)> callback)
        {
            const std::size_t id = m_nextId++;
            m_CallBacks.emplace_back(id, std::move(callback));
            return id;
        }

        void Unsubscribe(std::size_t id)
        {
            std::erase_if(m_CallBacks, [id](const auto& pair) { return pair.first == id; });
        }

        void Invoke(Args... args)
        {
            for (auto& [id, callback] : m_CallBacks)
                callback(args...);
        }
    private:
        std::vector<std::pair<std::size_t, std::function<void(Args...)>>> m_CallBacks{};
        std::size_t m_nextId{0};
    };

}



#endif //GAMEENGINE_EVENT_H
