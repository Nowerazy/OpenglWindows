#pragma once
#include "GlContext.h"
class GlControl {
private:
	GlContext* ctx;
public:
	void ctrolInit(GlContext*);
	void render();
};