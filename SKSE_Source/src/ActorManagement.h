#pragma once
#include <cstdint>
#include <vector>
#include "OstimNG-API-Thread.h"

namespace RE { class Actor; }

using API = OstimNG_API::Thread::IThreadInterface;

namespace HotSwap::ActorManagement {

    constexpr uint32_t kMaxActors = 5;

    bool canAddActor(uint32_t threadID, RE::Actor* actor, API* api);
    // Without callback: blocks until migration completes; returns new thread ID or -1.
    // With callback: returns immediately; callback receives new thread ID or -1.
    int32_t addActorToThread(uint32_t threadID, RE::Actor* actor, API* api,
                             void (*onComplete)(int32_t newThreadID, void* context) = nullptr,
                             void* context = nullptr);
    int32_t addActorsToThread(uint32_t threadID, const std::vector<RE::Actor*>& actors, API* api,
                              void (*onComplete)(int32_t newThreadID, void* context) = nullptr,
                              void* context = nullptr);

    bool canRemoveActor(uint32_t threadID, uint32_t position, API* api);
    int32_t removeActorFromThread(uint32_t threadID, uint32_t position, API* api,
                                  void (*onComplete)(int32_t newThreadID, void* context) = nullptr,
                                  void* context = nullptr);
    int32_t removeActorsFromThread(uint32_t threadID, const std::vector<uint32_t>& positions, API* api,
                                   void (*onComplete)(int32_t newThreadID, void* context) = nullptr,
                                   void* context = nullptr);

    bool canSwapActors(uint32_t threadID, uint32_t posA, uint32_t posB, API* api);
    std::vector<uint32_t> getSwapPartners(uint32_t threadID, RE::Actor* actor, API* api);
    int32_t swapActors(uint32_t threadID, uint32_t posA, uint32_t posB, API* api,
                       void (*onComplete)(int32_t newThreadID, void* context) = nullptr,
                       void* context = nullptr);

    void addActorWithUI(uint32_t threadID, API* api);
    void removeActorWithUI(uint32_t threadID, API* api);
    void swapActorsWithUI(uint32_t threadID, API* api);
}
