#include "Util/Core/WorldUtilLib.h"
#include "Util/Core/LogUtilLib.h"
#include "Util/TestUtil/TUActor.h"

#include "AutomationTest.h"
#include "GameFramework/Actor.h"

#include "GameFramework/PlayerController.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/GameState.h"

BEGIN_DEFINE_SPEC(WorldUtilLibSpec, "MyUtil.Core.World.WorldUtilLibSpec", EAutomationTestFlags::EngineFilter | EAutomationTestFlags::EditorContext)
	UWorld* W = nullptr;
END_DEFINE_SPEC(WorldUtilLibSpec)

void WorldUtilLibSpec::Define()
{
	Describe("PurgeWorld", [this]()
	{
		BeforeEach([this]()
		{
			W = UWorldUtilLib::NewGameWorldAndContext();
			TestNotNull(TEXT("NewGameWorldAndContext should NOT fail"), W);

			ATUActor* const A = UWorldUtilLib::Spawn<ATUActor>(W, FVector{0,0,0});
			TestNotNull(TEXT("Spawn must be valid"), A);

			APlayerController* const PC = UWorldUtilLib::Spawn<APlayerController>(W, FVector{0,0,0});
			TestNotNull(TEXT("Spawn PlayerController must succeed"), PC);

			AGameMode* const GameMode = UWorldUtilLib::Spawn<AGameMode>(W, FVector{0,0,0});
			TestNotNull(TEXT("Spawn GameInfo must succeed"), GameMode);

			AGameState* const GameState = UWorldUtilLib::Spawn<AGameState>(W, FVector{0,0,0});
			TestNotNull(TEXT("Spawn GameState must succeed"), GameState);

			TSet<AActor*> FailedActors;
			bool const bPurgeSucceeded = UWorldUtilLib::PurgeWorld(W, /*ExcludeSet*/nullptr, &FailedActors);
			TestTrue(TEXT("Purge must succeeded"), bPurgeSucceeded);
		});

		It("should NOT purge player controllers by default", [this]()
		{
			TSet<AActor*> const WorldActorsSet = UWorldUtilLib::GetActorsByPredicate
			(
				W, 
				[](const AActor*) { return true; }, 
				EActorIteratorFlags::AllActors 
			);
			TArray<AActor*> const WorldActors = WorldActorsSet.Array();

			M_NOT_IMPL();
		});
	});

	Describe("Spawn", [this]()
	{
		BeforeEach([this]()
		{
			W = UWorldUtilLib::NewGameWorldAndContext();
			TestNotNull(TEXT("NewGameWorldAndContext should NOT fail"), W);
		});

		It("should spawn valid actor", [this]()
		{
			ATUActor* const A = Cast<ATUActor>(UWorldUtilLib::Spawn(W, ATUActor::StaticClass(), FVector{0,0,0}));	
			TestNotNull(TEXT("Spawn should return valid pointer"), A);
		});

		It("should compile for template version that takes Location and Rotation", [this]()
		{
			ATUActor* const A = UWorldUtilLib::Spawn<ATUActor>(W, FVector{0,0,0});	
			TestNotNull(TEXT("Spawn should return valid pointer"), A);
		});

		It("should compile for template version that takes takes FTransform", [this]()
		{
			ATUActor* const A = UWorldUtilLib::Spawn<ATUActor>(W, FTransform{});	
			TestNotNull(TEXT("Spawn should return valid pointer"), A);
		});

		It("TestIt", [this]()
		{
			M_LOG(TEXT("TestIt"));
		});

		AfterEach([this]()
		{
			UWorldUtilLib::DestroyWorldSafe(&W);
			TestNull(TEXT("DestryoWorldSafe must succeed"), W);
		});
	});
}
