#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <string>

void drawChar(float x, float y, char c, float scale);
void drawText(float x, float y, const std::string& text, float scale);

#endif
