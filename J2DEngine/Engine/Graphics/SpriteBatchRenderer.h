#pragma once
#include "Base.h"
#include "Renderer.h"
#include <vector>

class CSpriteRenderer : public CRenderer, public CBase
{
public:
	CSpriteRenderer();
	~CSpriteRenderer();

	bool Init(CDirectXFramework* aFramework) override;
	void Render(std::vector<SSpriteRenderCommand>& aSpritesToRender);
};

