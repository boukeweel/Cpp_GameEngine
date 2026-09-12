# Engines
- [ ] Canvas System
    - [ ] Text rendering on canvas
        - problem = fix problem where text looks squiwist
    - [ ] Image rendering on canvas
    - [ ] Buttons
    - [ ] Eventmangar for button selection with keyboard.
- [ ] Camera
    - [x] First simple version Camera owned by renderer
    - [ ] Second Camera component for GameObjects (camera made for scrolling games that will follow the player where he goes)
- [ ] Object culling for rendering
    - Look into Frustum culling
- [ ] Controler input
- [ ] Audio system
- [ ] Child/Parent system
- [ ] sprite animation
- [ ] scene managar
- [ ] Collision system
    - [x] rect collidor
    - [ ] capsule collidor (if length == 0; it becomes a sphere)
    - [x] Get QuadTrees to work.
        - <img src="./Docs/Images/QuadTree_WorkingScreenShot.png" alt="QuadTree" width="500">
    - [x] Able to Get colliders from a portion of the Qaudtree
    - [x] narrow phase for collision.
    - [ ] Layer system
- [ ] physic system
    - [ ] gravity reaction
- [ ] Fps counter


## finished todos
- [x] Basic Event structure
    - Events should go into a queue of some sort.
    - all functions linked to a event should be called when the event is called.
    - new data type called Event where you can sub, unsub, and invoke on.
    - it should have a list of void* to every function that should be invoked
    - [x] make events without a type it passes.
    - [x] make a event with a Type you can pass with template function.
- [x] input system [Command Pattern](https://gameprogrammingpatterns.com/command.html)