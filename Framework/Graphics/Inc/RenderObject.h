#pragma once

#include "MeshBuffer_D3D11.h"
#include "TextureManager.h"
#include "Transform.h"
#include "Material.h"

namespace Kick_Engine::Graphics
{
	struct Model;

	struct RenderObject
	{
		void Terminate();

		Transform transform;
		MeshBuffer_D3D11 meshBuffer;

		Material material;

		TextureID diffuseMapId;
		TextureID normalMapId;
		TextureID specMapId;
		TextureID bumpMapId;
	};

	using RenderGroup = std::vector<RenderObject>;
	[[nodiscard]] RenderGroup CreateRenderGroup(const Model& model);
	void CleanupRenderGroup(RenderGroup& renderGroup);

	void SetRenderGroupPosition(RenderGroup& renderGroup, const Math::Vector3& position);

	template<class Effect>
	void DrawRenderGroup(Effect& effect, const RenderGroup& renderGroup)

	{
		for (const RenderObject& renderObject : renderGroup)
		{

			effect.Render(renderObject);

		}
	}

}