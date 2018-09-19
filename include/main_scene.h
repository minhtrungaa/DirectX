#pragma once
#include "scene.h"

class MainScene : public Scene
{
public:
	virtual void Init() override;
	virtual void Update(unsigned __int32) override;
	virtual void Render() override;
};