#include "AutomationTest.h"
#include "Util/Core/LogUtilLib.h"

DEFINE_SPEC(LogUtilLibSpec, "MyUtil.Core.Log.LogUtilLibSpec", EAutomationTestFlags::EngineFilter | EAutomationTestFlags::EditorContext)

void LogUtilLibSpec::Define()
{
	Describe("GetNameAndClassSafe", [this]()
	{
		It("should NOT fail when nullptr passed", [this]()
		{
			FString const ResultS = ULogUtilLib::GetNameAndClassSafe(nullptr);
			TestTrue(TEXT("Result text length must be greater than zero"), ResultS.Len() > 0);
		});

		//It("tests failing test (is test running at all?)", [this]()
		//{
		//	TestTrue(TEXT("Do Fail"), false);
		//});
	});

	Describe("LogObjectRange", [this]()
	{
		It("should correctly process nullptr", [this]()
		{
			TArray<const UObject*> const A { nullptr, nullptr, nullptr };
			int32 TotalObjects = ULogUtilLib::LogObjectRange(A);
			TestEqual(TEXT("Must return count of objects processsed"), TotalObjects, A.Num());
		});
	});
}
