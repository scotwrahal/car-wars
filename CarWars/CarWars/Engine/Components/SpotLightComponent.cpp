#include "SpotLightComponent.h"
#include "../Systems/Content/ContentManager.h"
#include "imgui/imgui.h"

#include "glm/gtc/type_ptr.hpp"

SpotLightComponent::SpotLightComponent(nlohmann::json data) {
	color = ContentManager::JsonToVec3(data["Color"], glm::vec3(1.f));
	direction = ContentManager::JsonToVec3(data["Direction"], glm::vec3(0.f, 0.f, 1.f));
	power = ContentManager::GetFromJson<float>(data["Power"], 10);
	angle = glm::radians(ContentManager::GetFromJson<float>(data["Angle"], 20));
}

SpotLightComponent::SpotLightComponent(glm::vec3 _color, float _power, float _angle, glm::vec3 _direction)
	: color(_color), power(_power), angle(_angle), direction(_direction) {}

float SpotLightComponent::GetPower() const {
	return power;
}

float SpotLightComponent::GetAngle() const {
	return angle;
}

glm::vec3 SpotLightComponent::GetDirection() const {
	return direction;
}

SpotLight SpotLightComponent::GetData() const {
	return SpotLight(color, power, GetEntity()->transform.GetGlobalPosition(), angle, GetEntity()->transform.GetGlobalDirection(direction));
}

ComponentType SpotLightComponent::GetType() {
	return ComponentType_SpotLight;
}

void SpotLightComponent::HandleEvent(Event* event) {}

void SpotLightComponent::RenderDebugGui() {
    ImGui::PushItemWidth(-100);
    ImGui::SliderAngle("Angle", &angle);
    ImGui::SliderFloat("Power", &power, 0, 1000);
    ImGui::SliderFloat3("Direction", glm::value_ptr(direction), -10.f, 10.f);
    ImGui::ColorPicker3("Colour", glm::value_ptr(color));
}

glm::vec3 SpotLightComponent::GetColor() const {
	return color;
}