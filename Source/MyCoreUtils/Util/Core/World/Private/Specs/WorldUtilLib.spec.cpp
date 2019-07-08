#include "Util/Core/WorldUtilLib.h"
#include "Util/Core/LogUtilLib.h"
#include "Util/TestUtil/TUActor.h"

#include "AutomationTest.h"
#include "GameFramework/Actor.h"

BEGIN_DEFINE_SPEC(WorldUtilLibSpec, "MyUtil.Core.World.WorldUtilLibSpec", EAutomationTestFlags::EngineFilter | EAutomationTestFlags::EditorContext)
	UWorld* W = nullptr;
END_DEFINE_SPEC(WorldUtilLibSpec)

void WorldUtilLibSpec::Define()
{
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
