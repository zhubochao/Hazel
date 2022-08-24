#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "SceneCamera.h"
#include "Hazel/Scene/ScriptableEntity.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include "Hazel/Renderer/Texture.h"

namespace Hazel
{
	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag) : Tag(tag) {}
	};

	struct CameraComponent
	{
		SceneCamera Camera;
		bool Primary = true; 
		bool FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;

	};

	struct TransformComponent
	{
		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& translation)
			: Translation(translation) {}

		glm::mat4 GetTransform() const
		{
			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

			return glm::translate(glm::mat4(1.0f), Translation)
				* rotation
				* glm::scale(glm::mat4(1.0f), Scale);
		}
	};

	struct SpriteRendererComponent
	{
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };
		Ref<Texture2D> Texture;
		float TilingFactor = 1.0f;

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			: Color(color) {}
	};

	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;

// 		std::function<void()> InstantiateFunction;
// 		std::function<void()> DestroyInstanceFunction;
// 
// 		std::function<void(ScriptableEntity*)> OnCreateFunction;
// 		std::function<void(ScriptableEntity*)> OnDestroyFunction;
// 		std::function<void(ScriptableEntity*, Timestep)> OnUpdateFunction;
		
		ScriptableEntity* (*InstantiateScript)();
		void (*DestroyScript)(NativeScriptComponent*);

		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) {delete nsc->Instance; nsc->Instance = nullptr; };
// 			InstantiateFunction = [&](){ Instance = new T(); };
// 			DestroyInstanceFunction = [&]() {delete (T*)Instance; Instance = nullptr; };
// 			
// 			OnCreateFunction = [](ScriptableEntity* instance) {((T*)instance)->OnCreate(); };
// 			OnDestroyFunction = [](ScriptableEntity* instance) {((T*)instance)->OnDestroy(); };
//  		OnUpdateFunction = [](ScriptableEntity* instance, Timestep ts) {((T*)instance)->OnUpdate(ts); };
		}
	};
}
