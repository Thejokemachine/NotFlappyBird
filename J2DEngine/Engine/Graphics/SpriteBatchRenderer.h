#pragma once
#include "Base.h"
#include "Renderer.h"
#include <vector>

struct SSpriteBatchRenderCommand;

class CSpriteBatchRenderer : public CRenderer, public CBase
{
public:
	CSpriteBatchRenderer();
	~CSpriteBatchRenderer();

	bool Init(CDirectXFramework* aFramework) override;
	void Render(std::vector<SSpriteBatchRenderCommand>& aSpritesToRender);
};

