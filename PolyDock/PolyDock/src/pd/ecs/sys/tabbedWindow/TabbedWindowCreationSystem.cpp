#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowCreationSystem.hpp>

// in
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowCreateRequestComponent.hpp>
// out
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowMovementActiveComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/SelectedTabsComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/ActiveTabComponent.hpp>

using namespace ::pd::ecs::sys::tabbedWindow;
using namespace ::pd::ecs::cmp::tabbedWindow;
using namespace ::pd::ecs::cmp::tabsHeader;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowCreationSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<TabbedWindowCreateRequestComponent>();

	for (auto entity : view)
	{
		auto& request = view.get<TabbedWindowCreateRequestComponent>(entity);

		registry.assign<TabbedWindowComponent>(entity, request.position, request.size);
		registry.assign<TabsHeaderComponent>(entity, request.tabs);
		registry.assign<SelectedTabsComponent>(entity, request.selectedTabs);
		if (request.activeTab.has_value())
			registry.assign<ActiveTabComponent>(entity, request.activeTab.value());

		if (request.windowMovementState == TabbedWindowCreateRequestComponent::eWindowMovementState::ACTIVE)
			registry.assign<TabbedWindowMovementActiveComponent>(entity);

		registry.remove<TabbedWindowCreateRequestComponent>(entity);
	}
}