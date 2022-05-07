#include "hzpch.h"
#include "Scene.h"

#include "Components.h"
#include "Entity.h"
#include "Hazel/Renderer/Renderer2D.h"
#include <glm/gtc/matrix_transform.hpp>

#include <glm/glm.hpp>

namespace Hazel
{
	static void DoMath(const glm::mat4& transform)
	{

	}

	static void OnTransformConstruct(entt::registry& registry, entt::entity entity)
	{
		
	}

	Scene::Scene()
	{
#if ENTT_EXAMPLE_CODE
		entt::entity entity = m_Registry.create();
		m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));

		m_Registry.on_construct<TransformComponent>().connect<&OnTransformConstruct>();


		if (m_Registry.has<TransformComponent>(entity))
			TransformComponent& transform = m_Registry.get<TransformComponent>(entity);

		
		auto view = m_Registry.view<TransformComponent>();
		for (auto entity : view)
		{
			TransformComponent& transform = view.get<TransformComponent>(entity);
		}

		auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent>);
		for (auto entity : group)
		{
			auto& [transform, mesh] = group.get<TransformComponent, MeshComponent>(entity);
		}
#endif
		
	}

	Scene::~Scene()
	{

	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}


	void Scene::OnUpdate(Timestep ts)
	{
		static float rotate = 0.0f;
		const float rotateSpeed = 20;
		rotate = ts * rotateSpeed;
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

			transform = glm::mat4(transform) * 
				glm::rotate(glm::mat4(1.0f), glm::radians(rotate), { 0.0f, 0.0f, 1.0f });
			Renderer2D::DrawQuad(transform, sprite.Color);
		}

	}

}

