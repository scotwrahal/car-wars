#pragma once

#include <string>
#include "Mesh.h"
#include <map>
#include "Texture.h"
#include "Material.h"
#include "json/json.hpp"
#include "../../Entities/Entity.h"
#include "../Content/HeightMap.h"
#include "NavigationMesh.h"

struct Texture;

class ContentManager {
public:
    static const glm::vec4 COLOR_WHITE;
    static const glm::vec4 COLOR_LIGHT_GREY;
    static const glm::vec4 COLOR_BLACK;
    static const glm::vec4 COLOR_LIGHT_RED;
    static const glm::vec4 COLOR_RED;
    static const glm::vec4 COLOR_LIGHT_GREEN;
    static const glm::vec4 COLOR_GREEN;
    static const glm::vec4 COLOR_DARK_BLUE;
    static const glm::vec4 COLOR_LIGHT_BLUE;
    static const glm::vec4 COLOR_BLUE;
    static const glm::vec4 COLOR_YELLOW;
    static const glm::vec4 COLOR_CYAN;

	static const std::string CONTENT_DIR_PATH;

	static const std::string MESH_DIR_PATH;
	static const std::string TEXTURE_DIR_PATH;
	static const std::string MATERIAL_DIR_PATH;
	static const std::string PX_MATERIAL_DIR_PATH;
	static const std::string SCENE_DIR_PATH;
    static const std::string MAP_DIR_PATH;

	static const std::string SKYBOX_DIR_PATH;
	static const std::string SKYBOX_FACE_NAMES[6];

	static const std::string PREFAB_DIR_PATH;
	static const std::string ENTITY_PREFAB_DIR_PATH;
	static const std::string COMPONENT_PREFAB_DIR_PATH;

	static const std::string COLLISION_GROUPS_DIR_PATH;

	static const std::string SHADERS_DIR_PATH;

	static Mesh* GetMesh(std::string filePath, unsigned pFlags=0);
	static Texture* GetTexture(std::string filePath);
	static Material* GetMaterial(nlohmann::json data);
	static physx::PxMaterial* GetPxMaterial(std::string filePath);

    static HeightMap* GetHeightMap(std::string dirPath);
    static NavigationMesh* GetNavigationMesh(std::string dirPath);

    static std::string GetTextureName(Texture* texture);

	static std::vector<Entity*> LoadScene(std::string filePath, Entity *parent=nullptr);
    static std::vector<Entity*> DestroySceneAndLoadScene(std::string filePath, Entity *parent = nullptr);

	template <typename T>
	static T GetFromJson(nlohmann::json json, T defaultValue);
	static nlohmann::json LoadJson(std::string filePath);
	static void MergeJson(nlohmann::json &obj0, nlohmann::json &obj1, bool overwrite=true);
	static glm::vec4 JsonToVec4(nlohmann::json data, glm::vec4 defaultValue);
	static glm::vec4 JsonToVec4(nlohmann::json data);
    static glm::vec3 JsonToVec3(nlohmann::json data, glm::vec3 defaultValue);
	static glm::vec3 JsonToVec3(nlohmann::json data);
	static glm::vec2 JsonToVec2(nlohmann::json data, glm::vec2 defaultValue);
	static glm::vec2 JsonToVec2(nlohmann::json data);
    static glm::vec4 GetColorFromJson(nlohmann::json data, glm::vec4 defaultValue);

    static void LoadCollisionGroups(std::string filePath);

    static void LoadSkybox(std::string directoryPath);
    static GLuint GetSkybox();

	static GLuint LoadShader(std::string filePath, GLenum shaderType);

	// TODO: These guys
	// static Audio*? GetAudio(std::string filePath);

    template <class T>
    static T* LoadComponent(nlohmann::json data);
	static Component* LoadComponent(nlohmann::json data);
	static Entity* LoadEntity(nlohmann::json data, Entity *parent=nullptr);

private:
    static std::map<std::string, nlohmann::json> scenePrefabs;
    static std::map<std::string, nlohmann::json> entityPrefabs;
    static std::map<std::string, nlohmann::json> componentPrefabs;

    static std::map<std::string, HeightMap*> heightMaps;
    static std::map<std::string, NavigationMesh*> navigationMeshes;

	static std::map<std::string, Mesh*> meshes;
	static std::map<std::string, Texture*> textures;
	static std::map<std::string, Material*> materials;
	static std::map<std::string, physx::PxMaterial*> pxMaterials;
    static GLuint skyboxCubemap;
};

template <typename T>
T ContentManager::GetFromJson(nlohmann::json json, T defaultValue) {
    if (json.is_null()) return defaultValue;
    return json.get<T>();
}

template <class T>
T* ContentManager::LoadComponent(nlohmann::json data) {
    Component* component = LoadComponent(data);
    return static_cast<T*>(component);
}
