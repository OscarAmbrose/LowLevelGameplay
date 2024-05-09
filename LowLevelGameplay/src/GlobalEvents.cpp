#include <GlobalEvents.h>

LLGP::Event<float> g_OnUpdate;
LLGP::Event<float> g_OnStart;
LLGP::Event<float> g_OnFixedUpdate;
LLGP::Event<sf::Event> g_OnPollInputs;
//LLGP::Event<float> g_OnRender;
LLGP::Event<sf::RenderWindow*> g_OnRender;
