#pragma once
#include <Event.h>
#include <SFML/Graphics.hpp>


extern LLGP::Event<float> g_OnUpdate;
extern LLGP::Event<float> g_OnStart;
extern LLGP::Event<float> g_OnFixedUpdate;
//extern LLGP::Event<float> g_OnRender;
extern LLGP::Event<sf::RenderWindow*> g_OnRender;
