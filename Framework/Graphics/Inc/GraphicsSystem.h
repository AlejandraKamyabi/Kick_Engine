#pragma once

#include "Colors.h"
#include "Common.h"

namespace Kick_Engine::Graphics
{
    class GraphicsSystem final
    {
    public:
        static void StaticInitialize(HWND window, bool fullscreen);
        static void StaticTerminate();
        static GraphicsSystem* Get();

    public:
        GraphicsSystem() = default;
        ~GraphicsSystem();

        GraphicsSystem(const GraphicsSystem&) = delete;
        GraphicsSystem(const GraphicsSystem&&) = delete;
        GraphicsSystem& operator=(const GraphicsSystem&) = delete;
        GraphicsSystem& operator=(const GraphicsSystem&&) = delete;

        void Initialize(HWND window, bool fullscreen);
        void Terminate();

        void BeginRender();
        void EndRender();

        void ToggleFullScreen();
        void Resize(uint32_t width, uint32_t height);

        void ResetRenderTarget();
        void ResetViewport();

        void SetClearColor(const Color& color);
        void SetVSync(bool vSync);

        uint32_t GetBackBufferWidth() const;
        uint32_t GetBackBufferHeight() const;

        float GetBackBufferAspectRatio() const;

        ID3D11Device* GetDevice(){ return mD3DDevice; } // {return}
        ID3D11DeviceContext* GetContext() { return mImmediateContext; } //

    private:
        static LRESULT CALLBACK GraphicsSystemMessageHandler(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

        friend ID3D11Device* GetDevice();
        friend ID3D11DeviceContext* GetContext(); //

        ID3D11Device* mD3DDevice = nullptr;
        ID3D11DeviceContext* mImmediateContext = nullptr;

        IDXGISwapChain* mSwapChain = nullptr;
        ID3D11RenderTargetView* mRenderTargetView = nullptr;

        ID3D11Texture2D* mDepthStencilBuffer = nullptr;
        ID3D11DepthStencilView* mDepthStencilView = nullptr;

        DXGI_SWAP_CHAIN_DESC mSwapChainDesc{};
        D3D11_VIEWPORT mViewport{};

        Color mClearColor = Colors::Black;
        UINT mSync = 1;
    };
}