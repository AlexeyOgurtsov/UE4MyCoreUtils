
#include "TUPawn.h"
#include "VisibleActorConfig.h"
#include "Util/Core/LogUtilLib.h"

#include "GameFramework/PlayerController.h"
#include "I/ITUController.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/SphereComponent.h"

#include "UObject/ConstructorHelpers.h"


ATUPawn::ATUPawn()
{
	M_LOGFUNC_IF(bLogBigEvents);
	LogThisIf(bLogBigEvents);

	InitMesh(nullptr);
	RootComponent = Mesh;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RootSceneComponent->SetupAttachment(RootComponent);

	InitProxSphere(RootSceneComponent);
	InitCameraAndSpringArm(RootSceneComponent);
}

void ATUPawn::PossessedBy(AController* InNewController)
{
	M_LOGFUNC_IF(bLogBigEvents);
	LogThisIf(bLogBigEvents);
	if(bLogBigEvents)
	{
		ULogUtilLib::LogKeyedNameClassSafeC(TEXT("InNewController"), InNewController);
		ULogUtilLib::LogKeyedNameClassSafeC(TEXT("GetController() Before SUPER"), GetController());
	}
	Super::PossessedBy(InNewController);
	if(bLogBigEvents)
	{
		ULogUtilLib::LogKeyedNameClassSafeC(TEXT("GetController() After SUPER"), GetController());
	}
}

void ATUPawn::UnPossessed()
{
	M_LOGFUNC_IF(bLogBigEvents);
	LogThisIf(bLogBigEvents);
	if(bLogBigEvents)
	{
		ULogUtilLib::LogKeyedNameClassSafeC(TEXT("GetController() Before SUPER"), GetController());
	}
	Super::UnPossessed();
	if(bLogBigEvents)
	{
		ULogUtilLib::LogKeyedNameClassSafeC(TEXT("GetController() After SUPER"), GetController());
	}
}

void ATUPawn::Restart()
{
	M_LOGFUNC_IF(bLogBigEvents);
	LogThisIf(bLogBigEvents);
	Super::Restart();
}

void ATUPawn::BecomeViewTarget(APlayerController* PC)
{
	M_LOGFUNC_IF(bLogBigEvents);
	LogThisIf(bLogBigEvents);
	if(bLogBigEvents)
	{
		ULogUtilLib::LogKeyedNameClassSafeC(TEXT("PC"), PC);
	}
	Super::BecomeViewTarget(PC);
}

void ATUPawn::PostInitProperties()
{
	Super::PostInitProperties();

	M_LOGFUNC_IF(bLogBigEvents);
	LogThisIf(bLogBigEvents);
}

void ATUPawn::PreRegisterAllComponents()
{
	M_LOGFUNC_IF(bLogBigEvents);
	LogThisIf(bLogBigEvents);
	Super::PreRegisterAllComponents();
}

void ATUPawn::PostRegisterAllComponents() 
{
	M_LOGFUNC_IF(bLogBigEvents);
	LogThisIf(bLogBigEvents);
	Super::PostRegisterAllComponents();
}

void ATUPawn::PreInitializeComponents()
{
	M_LOGFUNC_IF(bLogBigEvents);
	LogThisIf(bLogBigEvents);
	Super::PreInitializeComponents();
}

void ATUPawn::PostInitializeComponents()
{
	M_LOGFUNC_IF(bLogBigEvents);
	LogThisIf(bLogBigEvents);
	Super::PostInitializeComponents();
}

void ATUPawn::BeginPlay()
{
	M_LOGFUNC_IF(bLogBigEvents);
	LogThisIf(bLogBigEvents);

	Super::BeginPlay();

	MyBeginPlay();
	BeginPlayFinished();
}

void ATUPawn::MyBeginPlay_Implementation()
{
	M_LOGFUNC_IF(bLogBigEvents);
	LogThisIf(bLogBigEvents);
}

void ATUPawn::BeginPlayFinished()
{
	M_LOGFUNC_IF(bLogBigEvents);
	if( TScriptInterface<ITUController> const C = K2GetTUControllerLogged() )
	{
		ITUController::Execute_PawnBeginPlayEnded(C.GetObject());
	}
}

void ATUPawn::InitCameraAndSpringArm(USceneComponent* InAttachTo)
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = VisibleActorConfig::Default::SPRINGARM_TARGET_ARM_LENGTH;
	SpringArm->SetRelativeRotation(VisibleActorConfig::Default::SPRINGARM_RELATIVE_ROTATION);
	SpringArm->SetRelativeLocation(VisibleActorConfig::Default::SPRINGARM_RELATIVE_LOCATION);
	SpringArm->bEnableCameraLag = VisibleActorConfig::Default::SPRINGARM_ENABLE_CAMERA_LAG;
	SpringArm->CameraLagSpeed = VisibleActorConfig::Default::SPRINGARM_CAMERA_LAG_SPEED;
	SpringArm->SetupAttachment(InAttachTo);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = true;
	if(InAttachTo)
	{
		Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	}
}

void ATUPawn::InitMesh(USceneComponent* InAttachTo)
{
	static ConstructorHelpers::FObjectFinderOptional<UStaticMesh> MeshFinder { VisibleActorConfig::Default::MESH_ASSET_PATH };
	M_LOG_ERROR_IF( ! MeshFinder.Succeeded(), TEXT("Default mesh (\"%s\") NOT found"), VisibleActorConfig::Default::MESH_ASSET_PATH);

	{
		Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
		if(MeshFinder.Succeeded())
		{
			M_LOG(TEXT("Default mesh (\"%s\") found, setting it up"), VisibleActorConfig::Default::MESH_ASSET_PATH);
			Mesh->SetStaticMesh(MeshFinder.Get());
		}

		if(InAttachTo)
		{
			Mesh->SetupAttachment(InAttachTo);
		}
	}
}

void ATUPawn::InitProxSphere(USceneComponent* InAttachTo)
{
	ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	ProxSphere->InitSphereRadius(VisibleActorConfig::Default::PROX_SPHERE_RADIUS);
	ProxSphere->SetRelativeLocation(VisibleActorConfig::Default::MESH_REAL_CENTER_ACTOR_SPACE_LOCATION);
	if(InAttachTo)
	{
		ProxSphere->SetupAttachment(InAttachTo);
	}
}

TScriptInterface<ITUController> ATUPawn::K2GetTUController() const
{
	return TScriptInterface<ITUController>(GetController());
}

TScriptInterface<ITUController> ATUPawn::K2GetTUControllerLogged(ELogFlags InLogFlags) const
{
	TScriptInterface<ITUController> const C = K2GetTUController();
	if( ! C )
	{
		M_LOG_ERROR_IF_FLAGS(InLogFlags, TEXT("GetTUController() returned NULL"));
	}
	return C;
}

TScriptInterface<ITUController> ATUPawn::K2GetTUControllerChecked() const
{
	TScriptInterface<ITUController> const C = K2GetTUController();	
	checkf(C, TEXT("GetTUController() must return non-NULL pawn!"));
	return C;
}

ITUController* ATUPawn::GetTUController() const
{
	return Cast<ITUController>(GetController());
}

ITUController* ATUPawn::GetTUControllerLogged(ELogFlags InLogFlags) const
{
	ITUController* const C = GetTUController();
	if(C == nullptr)
	{
		M_LOG_ERROR_IF_FLAGS(InLogFlags, TEXT("GetTUController() returned NULL"));
	}
	return C;
}

ITUController* ATUPawn::GetTUControllerChecked() const
{
	ITUController* const C = GetTUController();	
	checkf(C, TEXT("GetTUController() must return non-NULL pawn!"));
	return C;
}

AController* ATUPawn::GetControllerLogged(ELogFlags InLogFlags) const
{
	AController* const C = GetController();
	if(C == nullptr)
	{
		M_LOG_ERROR_IF_FLAGS(InLogFlags, TEXT("GetController() returned NULL"));
	}
	return C;
}

AController* ATUPawn::GetControllerChecked() const
{
	AController* const C = GetController();	
	checkf(C, TEXT("GetController() must return non-NULL pawn!"));
	return C;
}

APlayerController* ATUPawn::GetPCLogged(ELogFlags InLogFlags) const
{
	APlayerController* const C = GetPC();
	if(C == nullptr)
	{
		M_LOG_ERROR_IF_FLAGS(InLogFlags, TEXT("GetPC() returned NULL"));
	}
	return C;
}

APlayerController* ATUPawn::GetPC() const
{
	return Cast<APlayerController>(GetController());
}

APlayerController* ATUPawn::GetPCChecked() const
{
	APlayerController* const C = GetPC();	
	checkf(C, TEXT("GetController() must return non-NULL pawn!"));
	return C;
}

void ATUPawn::LogThisIf(bool const bInShouldLog)
{
	if(bInShouldLog)
	{
		LogThis();
	}
}

void ATUPawn::LogThis()
{
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("This"), this);
}
