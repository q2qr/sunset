#include "../include/UIAPI.h"
#include "../include/MCOffsets.h"
#include "../include/ModLoader.h"

#include <stdio.h>
#include <string.h>

namespace {

static void* g_guiComponent = 0;
static const uint32_t kGameToc = 0x014CDAB0;

template<typename ReturnT, typename... Args>
inline ReturnT CallGame(uint32_t functionAddress, Args... args)
{
    uint32_t descriptor[2] = { functionAddress, kGameToc };
    ReturnT (*fn)(Args...) = (ReturnT(*)(Args...))descriptor;
    return fn(args...);
}

struct FontString {
    const wchar_t* text;
    uint32_t dataType;
    uint32_t wcstrlen;
    uint32_t wcstrlen1;
    float scale;
};

static uint32_t WideLen(const wchar_t* text)
{
    uint32_t len = 0;
    if (!text) {
        return 0;
    }

    while (text[len] != L'\0') {
        ++len;
    }

    return len;
}

static FontString MakeFontString(const wchar_t* text)
{
    FontString value;
    value.text = text;
    value.dataType = 7;
    value.wcstrlen = WideLen(text);
    value.wcstrlen1 = value.wcstrlen + 3;
    value.scale = 1.0f;
    return value;
}

static void AsciiToWide(const char* in, wchar_t* out, size_t outCount)
{
    if (!in || !out || outCount == 0) {
        return;
    }

    size_t i = 0;
    while (in[i] != '\0' && i + 1 < outCount) {
        out[i] = (wchar_t)in[i];
        ++i;
    }
    out[i] = L'\0';
}

}

void UI_SetGuiComponent(void* guiComponent)
{
    g_guiComponent = guiComponent;
}

uint32_t UI_MakeColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    return ((uint32_t)a << 24) |
           ((uint32_t)r << 16) |
           ((uint32_t)g << 8) |
           (uint32_t)b;
}

void UI_DrawRect(float x, float y, float width, float height, uint32_t argbColor)
{
    if (!g_guiComponent) {
        return;
    }

    CallGame<void>((uint32_t)MCOffsets::GuiFillRect,
                   g_guiComponent,
                   (uint32_t)x,
                   (uint32_t)y,
                   (uint32_t)width,
                   (uint32_t)height,
                   argbColor);
}

void UI_DrawShadowText(uint32_t fontRenderer, const wchar_t* text, float x, float y, uint32_t argbColor)
{
    if (!fontRenderer || !text) {
        return;
    }

    FontString formatted = MakeFontString(text);

    CallGame<void>((uint32_t)MCOffsets::DrawShadowText,
                   fontRenderer,
                   (uint32_t)&formatted,
                   (uint32_t)x,
                   (uint32_t)y,
                   argbColor,
                   0u,
                   1u);
}

int UI_DrawLoadedModsList(void* guiComponent, uint32_t fontRenderer, float x, float y, float lineHeight, uint32_t argbColor)
{
    if (guiComponent) {
        g_guiComponent = guiComponent;
    }

    ModPublicInfo mods[32];
    int count = ModLoader_GetLoadedMods(mods, 32);

    wchar_t line[192];
    for (int i = 0; i < count; ++i) {
        char ascii[192];
        snprintf(ascii,
                 sizeof(ascii),
                 "[%s] %s %s",
                 mods[i].fromSunsetPackage ? "SUNSET" : "SPRX",
                 mods[i].name[0] ? mods[i].name : "UnnamedMod",
                 mods[i].version[0] ? mods[i].version : "");

        AsciiToWide(ascii, line, sizeof(line) / sizeof(line[0]));
        UI_DrawShadowText(fontRenderer, line, x, y + (lineHeight * i), argbColor);
    }

    return count;
}
