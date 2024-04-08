#pragma once
#include <concepts>

template<typename T> 
concept SameClassConcept = std::is_base_of<class Component,T>::value;
