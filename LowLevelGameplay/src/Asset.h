#pragma once
#include <Object.h>
#include <string>

namespace LLGP
{
	class Asset : public Object
	{
	public:
		Asset(std::string path) : Object() {}
		virtual ~Asset() = default;
	};
}
