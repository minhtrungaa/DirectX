#pragma once
/*
	This will be base scene
	mainly have interface for inherit later
*/
class Scene
{
public:
	Scene() {}
	~Scene() {}

	virtual void Init();

	// TODO: Add delta time later for update
	virtual void Update(unsigned __int32 dt);

	virtual void Render();
};