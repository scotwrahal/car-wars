#include "AiComponent.h"
#include "../Systems/Content/ContentManager.h"

AiComponent::AiComponent(nlohmann::json data) : targetEntity(nullptr), waypointIndex(0) {
    std::string modeName = ContentManager::GetFromJson<std::string>(data["Mode"], "Waypoints");
    if (modeName == "Waypoints") {
        mode = AiMode_Waypoints;
    } else if (modeName == "Chase") {
        mode = AiMode_Chase;
    }
}

ComponentType AiComponent::GetType() {
    return ComponentType_AI;
}

void AiComponent::HandleEvent(Event* event) { }

void AiComponent::RenderDebugGui() {
    Component::RenderDebugGui();
}

void AiComponent::SetTargetEntity(Entity* target) {
    targetEntity = target;
}

Entity* AiComponent::GetTargetEntity() const {
    return targetEntity;
}

AiMode AiComponent::GetMode() const {
    return mode;
}

size_t AiComponent::GetWaypoint() const {
    return waypointIndex;
}

size_t AiComponent::NextWaypoint(size_t waypointCount) {
    waypointIndex = (waypointIndex + 1) % waypointCount;
    return GetWaypoint();
}
