#include"GlControl.h"
	
void GlControl::ctrolInit(GlContext* context) {
	ctx = context;
	glClearColor(1, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
};
void GlControl::render() {
	ctx->swapBuffer();
}