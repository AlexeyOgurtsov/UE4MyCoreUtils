#include "Util/Core/ContainerUtilLib.h"
#include "Util/Core/LogUtilLib.h"

// ~Includ test classes Begin
#include "GameFramework/GameMode.h"
#include "Components/SphereComponent.h"
#include "Components/AudioComponent.h"
// ~Include test classes End

#include "AutomationTest.h"

BEGIN_DEFINE_SPEC(ContainerUtilLib_ClassContainerSpec, "MyUtil.Core.Container.ContainerUtilLib.ClassContainerSpec", EAutomationTestFlags::EngineFilter | EAutomationTestFlags::EditorContext)
	TSet<UClass*> ClassSet;
	TSet<const UClass*> ConstClassSet;

	TArray<UClass*> ClassArray;
	TArray<const UClass*> ConstClassArray;
END_DEFINE_SPEC(ContainerUtilLib_ClassContainerSpec);

void ContainerUtilLib_ClassContainerSpec::Define()
{
	Describe("Find class inside class container utilities", [this]()
	{
		BeforeEach([this]()
		{
			{
				ConstClassSet.Empty();
				ClassSet.Append
				(
					{
						// nullptr should be handled correctly
						nullptr,

						// So we have a class that is NOT derived from UPrimitveComponent
						UAudioComponent::StaticClass(),

						// Derived from UPrimitiveComponent
						USphereComponent::StaticClass()
					}
				);
			}

			{
				ConstClassSet.Empty();
				for(UClass* O : ClassSet) { ConstClassSet.Add(O); }
			}

			{
				ClassArray = ClassSet.Array();
			}

			{
				ConstClassArray = ConstClassSet.Array();
			}
		});		

		Describe("FindSubclassOf", [this]()
		{
			It("Must find valid class that is subclass of the given one", [this]()
			{
				const UClass* const ClassToSearch = UPrimitiveComponent::StaticClass();

				UClass** const ppFoundClass = UContainerUtilLib::FindSubclassOf(ClassSet, ClassToSearch);
				TestNotNull(TEXT("Class must be found"), ppFoundClass);

				bool const bSuclass = (*ppFoundClass)->IsChildOf(ClassToSearch);
				TestTrue(TEXT("Found object must be subclass of the demanded class"), bSuclass);
			});

			It("Should return nullptr when searching for class that is not contained", [this]()
			{
				UClass* const ClassToSearch = AGameMode::StaticClass();

				UClass** const ppFoundClass = UContainerUtilLib::FindSubclassOf(ClassSet, ClassToSearch);
				TestNull(TEXT("Must return nullptr"), ppFoundClass);
			});
		});
	});
}

BEGIN_DEFINE_SPEC(ContainerUtilLib_ObjectOfClassSpec, "MyUtil.Core.Container.ContainerUtilLib.ObjectOfClassSpec", EAutomationTestFlags::EngineFilter | EAutomationTestFlags::EditorContext)
	TSet<UObject*> ObjSet;
	TSet<const UObject*> ConstObjSet;

	TArray<UObject*> ObjArray;
	TArray<const UObject*> ConstObjArray;
END_DEFINE_SPEC(ContainerUtilLib_ObjectOfClassSpec);

void ContainerUtilLib_ObjectOfClassSpec::Define()
{
	Describe("Find objects of class utilities", [this]()
	{
		BeforeEach([this]()
		{
			{
				ObjSet.Empty();
				ObjSet.Append
				(
					{
						// nullptr should be handled correctly
						nullptr,

						// So we have a component that is NOT derived from UPrimitveComponent
						NewObject<UAudioComponent>(),

					 	// Derived from UPrimitiveComponent
						NewObject<USphereComponent>()
					}
				);
			}

			{
				ConstObjSet.Empty();
				for(UObject* O : ObjSet) { ConstObjSet.Add(O); }
			}

			{
				ObjArray = ObjSet.Array();
			}

			{
				ConstObjArray = ConstObjSet.Array();
			}
		});

		Describe("FindChildOf", [this]()
		{
			It("Must find valid object that is subclass of the given one", [this]()
			{
				const UClass* const ClassToSearch = UPrimitiveComponent::StaticClass();

				UObject** const ppFoundObj = UContainerUtilLib::FindChildOf(ObjSet, ClassToSearch);
				TestNotNull(TEXT("Object must be found"), ppFoundObj);

				bool const bSuclass = (*ppFoundObj)->GetClass()->IsChildOf(ClassToSearch);
				TestTrue(TEXT("Found object must be subclass of the demanded class"), bSuclass);
			});

			It("Should return nullptr when searching for class that is not contained", [this]()
			{
				const UClass* const ClassToSearch = AGameMode::StaticClass();

				UObject** const ppFoundObj = UContainerUtilLib::FindChildOf(ObjSet, ClassToSearch);
				TestNull(TEXT("Must return nullptr"), ppFoundObj);
			});
		});
	});
}
