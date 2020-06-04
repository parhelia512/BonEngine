#include <_CAPI/CAPI.h>
#include <BonEngine.h>

/**
 * Special scene to accept callbacks.
 */
class _CallbacksScene : public bon::engine::Scene
{
public:
	BON_CallbackNoArgs onLoad;
	BON_CallbackNoArgs onUnload;
	BON_CallbackNoArgs onStart;
	BON_CallbackNoArgs onDraw;
	BON_CallbackDoubleArg onUpdate;
	BON_CallbackDoubleArg onFixedUpdate;
	
	virtual void _Load() override
	{
		onLoad();
	}

	virtual void _Unload() override
	{
		onUnload();
	}

	virtual void _Start() override
	{
		onStart();
	}

	virtual void _Update(double deltaTime) override
	{
		onUpdate(deltaTime);
	}

	virtual void _Draw() override
	{
		onDraw();
	}

	virtual void _FixedUpdate(double deltaTime) override
	{
		onFixedUpdate(deltaTime);
	}
};

// create and return scene with callbacks
bon::engine::Scene* BON_CreateScene(BON_CallbackNoArgs onLoad, BON_CallbackNoArgs onUnload, BON_CallbackNoArgs onStart, BON_CallbackNoArgs onDraw, BON_CallbackDoubleArg onUpdate, BON_CallbackDoubleArg onFixedUpdate)
{
	_CallbacksScene* ret = new _CallbacksScene();
	ret->onLoad = onLoad;
	ret->onUnload = onUnload;
	ret->onStart = onStart;
	ret->onDraw = onDraw;
	ret->onUpdate = onUpdate;
	ret->onFixedUpdate = onFixedUpdate;
	return ret;
}

// destroy a scene
void BON_DestroyScene(bon::engine::Scene* scene)
{
	delete scene;
}

// start engine with special scene to accept callback
void BON_Start(bon::engine::Scene* scene)
{
	bon::Start(*scene);
}