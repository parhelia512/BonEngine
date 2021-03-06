#include <Engine/Scene.h>
#include <BonEngine.h>

namespace bon
{
	namespace engine
	{
		// is it the first scene to run?
		bool Scene::IsFirstScene() const
		{
			return _GetEngine().ActiveScene() == this && _GetEngine().SwitchedScenesCount() == 1;
		}
	}
}