#pragma once

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void UI_SetGuiComponent(void* guiComponent);
uint32_t UI_MakeColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void UI_DrawRect(float x, float y, float width, float height, uint32_t argbColor);
void UI_DrawShadowText(uint32_t fontRenderer, const wchar_t* text, float x, float y, uint32_t argbColor);
int UI_DrawLoadedModsList(void* guiComponent, uint32_t fontRenderer, float x, float y, float lineHeight, uint32_t argbColor);

#ifdef __cplusplus
}
#endif
