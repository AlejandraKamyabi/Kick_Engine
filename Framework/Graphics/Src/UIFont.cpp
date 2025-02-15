#include "Precompiled.h"
#include "UIFont.h"

#include "GraphicsSystem.h"

using namespace Kick_Engine;
using namespace Kick_Engine::Graphics;
using namespace Kick_Engine::Kick_Math;

namespace
{
    const wchar_t* GetFontFamily(UIFont::FontType font)
    {
        switch (font)
        {
        case UIFont::FontType::Arial:
            return L"Arial";
            break;
        case UIFont::FontType::CourierNew:
            return L"CourierNew";
            break;
        case UIFont::FontType::Consolas:
            return L"Consolas";
            break;
        default:
            ASSERT(false, "UIFont: invalid font");
            break;
        }

        return L"Arial";
    }
    inline uint32_t ToFontColor(const Kick_Engine::Color& color)
    {
        uint8_t r = (uint8_t)(color.r * 255.0f);
        uint8_t g = (uint8_t)(color.g * 255.0f);
        uint8_t b = (uint8_t)(color.b * 255.0f);
        uint8_t a = (uint8_t)(color.a * 255.0f);

        return (a << 24) | (b << 16) | (g << 8) | r;
    }

    std::unique_ptr<UIFont> sUIFont;
}

void UIFont::StaticInitialize(FontType font)
{
    ASSERT(sUIFont == nullptr, "UIFont: is already initialized");
    sUIFont = std::make_unique<UIFont>();
    sUIFont->Initialize(font);
}

void UIFont::StaticTerminate()
{
    if (sUIFont != nullptr)
    {
        sUIFont->Terminate();
        sUIFont.reset();
    }
}

UIFont* UIFont::Get()
{
    ASSERT(sUIFont != nullptr, "UIFont: was not initialized");
    return sUIFont.get();
}

UIFont::~UIFont()
{
    ASSERT(mFontFactory == nullptr && mFontWrapper == nullptr, "UIFont: terminate must be called");
}

void UIFont::Initialize(FontType font)
{
    mFontType = font;
    auto device = GraphicsSystem::Get()->GetDevice();
    FW1CreateFactory(FW1_VERSION, &mFontFactory);
    auto hr = mFontFactory->CreateFontWrapper(device, GetFontFamily(font), &mFontWrapper);
    ASSERT(SUCCEEDED(hr), "UIFont: failed to create font wrapper");

}

void UIFont::Terminate()
{
    SafeRelease(mFontWrapper);
    SafeRelease(mFontFactory);
}

void UIFont::DrawString(const wchar_t* str, const Kick_Math::Vector2& position, float size, const Color& color)
{
    int len = (int)wcslen(str);
    auto context = GraphicsSystem::Get()->GetContext();
    mFontWrapper->DrawString(context, str, size, position.x, position.y, ToFontColor(color), FW1_RESTORESTATE);
}

float UIFont::GetStringWidth(const wchar_t* str, float size) const
{
    FW1_RECTF layoutRect;
    layoutRect.Left = 0.0f;
    layoutRect.Top = 0.0f;
    layoutRect.Right = (float)GraphicsSystem::Get()->GetBackBufferWidth();
    layoutRect.Bottom = (float)GraphicsSystem::Get()->GetBackBufferHeight();
    auto rect = mFontWrapper->MeasureString(str, GetFontFamily(mFontType), size, &layoutRect, FW1_RESTORESTATE);
    return rect.Right - rect.Left;
}
