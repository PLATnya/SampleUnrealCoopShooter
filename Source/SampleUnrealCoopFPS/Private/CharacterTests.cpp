// Fill out your copyright notice in the Description page of Project Settings.


#include "SampleUnrealCoopFPS/Public/CharacterTests.h"

#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "Engine.h"
#include "Engine/Engine.h"
#include "EngineUtils.h"
#include "MGunActor.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGameTest, "CustomTests.Game",
    EAutomationTestFlags::EditorContext |
    EAutomationTestFlags::ProductFilter)


UWorld* GetTestWorld() {
	const TIndirectArray<FWorldContext>& WorldContexts = GEngine->GetWorldContexts();
	for (const FWorldContext& Context : WorldContexts) {
		if (((Context.WorldType == EWorldType::PIE) || (Context.WorldType == EWorldType::Game))
            && (Context.World() != nullptr)) {
			return Context.World();
            }
	}

	return nullptr;
}

bool FGameTest::RunTest(const FString& Parameters) {
	//AutomationOpenMap(TEXT("/Game/Levels/StartupLevel"));
#ifdef NDEBUG
	bool a = false;
	UWorld* World = GetTestWorld();
	
	TestTrue("Essential actor is spawned", TActorIterator<AMGunActor>(World)->IsActorInitialized() );
	return true;	
#endif

	return false;
}

