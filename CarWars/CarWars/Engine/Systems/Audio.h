#pragma once

#include <vector>

#include "System.h"
#include "Game.h"
#include "StateManager.h"
#include "../Components/CameraComponent.h"
#include "../Components/RigidbodyComponents/VehicleComponent.h"
#include "fmod/fmod.hpp"
#include "fmod/fmod_errors.h"
#include "../Entities/EntityManager.h"
#include "glm/glm.hpp"

#define MAX_DISTANCE 5000.0
#define MIN_DISTANCE 0.15
#define MAX_CHANNELS 200
#define NUM_MUSIC 7

// 25 is too low
#define UPDATES_TO_RUN 100 // +6 "mandatory updates"

typedef FMOD::Sound* SoundClass;

struct CarSound {
    unsigned int currentSoundPos;
    glm::vec3 currentPosition;
    glm::vec3 lastPosition;
    glm::vec3 velocity;
    FMOD::Sound *sound=0;
    FMOD::Channel *channel=0;
    bool changedDirection = false;
    bool reversing = false;
};

struct WeaponSounds {
    FMOD::Sound* missleLaunch;
    FMOD::Sound* explosion;

    FMOD::Sound* bulletShoot;
    FMOD::Sound* bulletHitHeavy;
    FMOD::Sound* bulletHitMedium;
    FMOD::Sound* bulletHitLight;
    FMOD::Sound* bulletHitGround;
    FMOD::Sound* bulletHitWall;

    FMOD::Sound* railgunCharge;
    FMOD::Sound* railgunShoot;
    FMOD::Sound* railgunHitHeavy;
    FMOD::Sound* railgunHitMedium;
    FMOD::Sound* railgunHitLight;
    FMOD::Sound* railgunHitGround;
    FMOD::Sound* railgunHitWall;
};

struct MenuSounds {
    FMOD::Sound* navigate;
    FMOD::Sound* enter;
    FMOD::Sound* back;
};

struct EnvironmentalSounds {
	FMOD::Sound* hitCar;
	FMOD::Sound* hitGround;
	FMOD::Sound* hitWall;
	FMOD::Sound* powerup;
	FMOD::Sound* jump;
};

struct AttachedSound {
	FMOD::Channel *channel;
	Entity* entity;
};



class Audio : public System {
public:
    WeaponSounds Weapons;
    MenuSounds Menu;
	EnvironmentalSounds Environment;

    float musicVolume = 0.065f;
    float aiSoundVolume = 0.25f;
    float playerSoundVolume = 0.05f;

    // Access the singleton instance
    static Audio& Instance();
    ~Audio();

    void Initialize();

    void Update() override;
    void PlayMusic(const char *filename);

	void PlayAudio2D(FMOD::Sound* sound, float volume);
	void PlayAudio3D(FMOD::Sound *s, glm::vec3 position, glm::vec3 velocity, float volume);
	void PlayAudio3DAttached(FMOD::Sound *s, Entity* entity, float volume);

	int PlaySound3D(FMOD::Sound* sound, glm::vec3 position, glm::vec3 velocity, float volume);
	void StopSound3D(int index);

private:
    int updateFunctionId;
    int availableUpdates;
    int updatePosition;
	vector<AttachedSound> attachedSounds;
    bool gameStarted = false;
    int currentMusicIndex = 0;
    const char *musicPlaylist[NUM_MUSIC] = {
        "Content/Music/unity.mp3",
        "Content/Music/hello.mp3",
        "Content/Music/highscore.mp3",
        "Content/Music/invincible.mp3",
        "Content/Music/lone-digger.mp3",
        "Content/Music/monody.mp3",
        "Content/Music/xenogenesis.mp3"
    };

    FMOD::System *soundSystem;
    GameState prevGameState;
    bool carsStarted = false;

	FMOD::Sound* soundArray3D[100];
	FMOD::Channel* channelArray3D[100];
	bool availableSound3D[100];

    std::vector<CarSound> carSounds;
    //unsigned int gameMusicPosition, gameMusicLength;
    FMOD::Sound *music;
    FMOD::Channel *musicChannel;

    FMOD::Sound *sound, *sound3d, *soundToPlay, *soundToPlay3d;
    FMOD::Channel *channel = 0, *channel3d = 0;
    FMOD_RESULT result;
    unsigned int version;
    int numsubsounds;
    int numsubsounds3d;

	void PauseSounds();
	void ResumeSounds();
    void MenuMusicControl();
    void UpdateListeners();
    void UpdateRunningCars();
    void StartCars();
    void PauseCars(bool paused);
    void UpdateCars();
    void StopCars();
    void ReleaseSounds();
    void CheckMusic();
    void AddSoundToMemory(const char *filepath, FMOD::Sound** sound);
	void UpdateAttached();


    // No instantiation or copying
    Audio();
    Audio(const Audio&) = delete;
    Audio& operator= (const Audio&) = delete;
};

