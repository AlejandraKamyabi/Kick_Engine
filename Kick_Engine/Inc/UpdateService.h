#pragma once

#include "Service.h"

namespace Kick_Engine
{
    class Component;

    class UpdateService final : public Service
    {
    public:
        SET_TYPE_ID(ServiceId::Update);

        void Update(float deltaTime) override;

        void Register(Component* component);
        void Unregister(Component* component);

    private:

        using UpdateComponents = std::vector<Component*>;
        UpdateComponents mUpdateComponents;
        UpdateComponents mPendingComponents;

        bool mIsUpdating = false;
    };
}