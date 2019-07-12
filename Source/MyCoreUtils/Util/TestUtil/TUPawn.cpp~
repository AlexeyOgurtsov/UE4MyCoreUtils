
#include "TUPawn.h"
#include "VisibleActorConfig.h"
#include "Util/Core/LogUtilLib.h"

#include "GameFramework/Controller.h"
#include "I/ITUController.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/SphereComponent.h"

#include "UObject/ConstructorHelpers.h"

using namespace VisibleActorConfig;

ATUPawn::ATUPawn()
{
	RootComponent = RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));

	InitCameraAndSpringArm(RootSceneComponent);
	InitMesh(RootSceneComponent);
	InitProxSphere(RootSceneComponent);
}

void ATUPawn::BeginPlay()
{
	M_LOGFUNC();

	Super::BeginPlay();

	MyBeginPlay();
	BeginPlayFinished();
}

void ATUPawn::MyBeginPlay_Implementation()
{
	M_LOGFUNC();
}

void ATUPawn::BeginPlayFinished()
{
	M_LOGFUNC();
	if( TScriptInterface<ITUController> const C = K2GetTUControllerLogged() )
	{
		ITUController::Execute_PawnBeginPlayEnded(C.GetObject());
	}
}

void ATUPawn::InitCameraAndSpringArm(USceneComponent* InAttachTo)
{
	checkf(InAttachTo, TEXT("When calling %s component to attach to must be non-NULL pointer"), TEXT(__FUNCTION__));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = Default::SPRINGARM_TARGET_ARM_LENGTH;
	SpringArm->RelativeRotation = Default::SPRINGARM_RELATIVE_ROTATION;
	SpringArm->RelativeLocation = Default::SPRINGARM_RELATIVE_LOCATION;
	SpringArm->bEnableCameraLag = Default::SPRINGARM_ENABLE_CAMERA_LAG;
	SpringArm->CameraLagSpeed = Default::SPRINGARM_CAMERA_LAG_SPEED;
	SpringArm->SetupAttachment(InAttachTo);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = true;
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

void ATUPawn::InitMesh(USceneComponent* InAttachTo)
{
	checkf(InAttachTo, TEXT("When calling %s component to attach to must be non-NULL pointer"), TEXT(__FUNCTION__));

	static ConstructorHelpers::FObjectFinderOptional<UStaticMesh> MeshFinder { Default::MESH_ASSET_PATH };
	M_LOG_ERROR_IF( ! MeshFinder.Succeeded(), TEXT("Default mesh (\"%s\") NOT found"), Default::MESH_ASSET_PATH);

	{
		Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
		if(MeshFinder.Succeeded())
		{
			M_LOG(TEXT("Default mesh (\"%s\") found, setting it up"), Default::MESH_ASSET_PATH);
			Mesh->SetStaticMesh(MeshFinder.Get());
		}

		Mesh->SetupAttachment(InAttachTo);
	}
}

void ATUPawn::InitProxSphere(USceneComponent* InAttachTo)
{
	checkf(InAttachTo, TEXT("When calling %s component to attach to must be non-NULL pointer"), TEXT(__FUNCTION__));

	ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	ProxSphere->InitSphereRadius(Default::PROX_SPHERE_RADIUS);
	ProxSphere->RelativeLocation = Default::MESH_REAL_CENTER_ACTOR_SPACE_LOCATION;
	ProxSphere->SetupAttachment(InAttachTo);
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
