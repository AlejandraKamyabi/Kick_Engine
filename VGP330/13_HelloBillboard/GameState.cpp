#include "GameState.h"

using namespace Kick_Engine;
using namespace Kick_Engine::Graphics;
using namespace Kick_Engine::Kick_Math;
using namespace Kick_Engine::Input;

void GameState::Initialize()
{
    mCamera.SetPosition({ 0.0f, 1.0f, -4.0f });
    mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

    mBillboardEffect.Initialize();
    mBillboardEffect.SetCamera(mCamera);

    Mesh spriteMesh = MeshBuilder::CreateSpriteQuad(1.0f, 1.0f);
    mSprite.meshBuffer.Initialize(spriteMesh);
    mSprite.diffuseMapId = TextureManager::Get()->LoadTexture("Images/mario.png");
};
void GameState::Terminate()
{
    mSprite.Terminate();
    mBillboardEffect.Terminate();
}
void GameState::Update(float deltaTime)
{
    UpdateCameraControl(deltaTime);
}

void GameState::Render()
{
    SimpleDraw::AddGroundPlane(20.0f, Colors::White);
    SimpleDraw::Render(mCamera);

    mBillboardEffect.Begin();
        mBillboardEffect.Render(mSprite);
    mBillboardEffect.End();
}

void GameState::DebugUI()
{
    ImGui::Begin("Debug Control", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    {
        ImGui::DragFloat3("SpritePosition", &mSprite.transform.position.x, 0.1f);
    }
    ImGui::End();
}

void GameState::UpdateCameraControl(float deltaTime)
{
    auto input = Input::InputSystem::Get();
    const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
    const float turnSpeed = 0.1f;

    if (input->IsKeyDown(KeyCode::W))
    {
        mCamera.Walk(moveSpeed * deltaTime);
    }
    else if (input->IsKeyDown(KeyCode::S))
    {
        mCamera.Walk(-moveSpeed * deltaTime);
    }
    if (input->IsKeyDown(KeyCode::D))
    {
        mCamera.Strafe(moveSpeed * deltaTime);
    }
    else if (input->IsKeyDown(KeyCode::A))
    {
        mCamera.Strafe(-moveSpeed * deltaTime);
    }
    if (input->IsKeyDown(KeyCode::E))
    {
        mCamera.Rise(moveSpeed * deltaTime);
    }
    else if (input->IsKeyDown(KeyCode::Q))
    {
        mCamera.Rise(-moveSpeed * deltaTime);
    }
    if (input->IsMouseDown(MouseButton::RBUTTON))
    {
        mCamera.Yaw(input->GetMouseMoveX() * turnSpeed * deltaTime);
        mCamera.Pitch(input->GetMouseMoveY() * turnSpeed * deltaTime);
    }
}