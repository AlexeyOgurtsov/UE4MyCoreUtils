
#include "TUPawn.h"
#include "VisibleActorConfig.h"
#include "Util/Core/Phys/PhysUtilLib.h"
#include "Util/Core/LogUtilLib.h"

#include "GameFramework/PlayerController.h"
#include "I/ITUController.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/SphereComponent.h"

#include "Engine/World.h"
#include "CollisionQueryParams.h"
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

AActor* ATUPawn::TraceByLook(bool bInTraceComplex, ECollisionChannel InCollisionChannel, ELogFlags InLogFlags) const
{
	return TraceByLookCustom(DefaultLookTraceLength, bInTraceComplex, InCollisionChannel, InLogFlags);
}

AActor* ATUPawn::TraceByLookCustom(float InLength, bool bInTraceComplex, ECollisionChannel InCollisionChannel, ELogFlags InLogFlags) const
{
	M_LOG_IF_FLAGS(InLogFlags, TEXT("Calling \"%s\" on object \"%s\" of class \"%s\" with Length=%f, TraceComplex=%s, CollisionChannel=%s"), 
			TEXT(__FUNCTION__), 
			*GetName(), *GetClass()->GetName(),
			InLength, (bInTraceComplex ? TEXT("TRUE") : TEXT("false")), *UPhysUtilLib::GetCollisionChannelString(InCollisionChannel)
			);

	FVector ViewLocation;
	FRotator ViewRotation;

	if(Controller)
	{
		M_LOG_IF_FLAGS(InLogFlags, TEXT("Pawn is possessed with controller \"%s\" of class \"%s\""), *Controller->GetName(), *Controller->GetClass()->GetName());
		Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	}
	else
	{
		M_LOG_IF_FLAGS(InLogFlags, TEXT("No controller attached"));
		GetActorEyesViewPoint(ViewLocation, ViewRotation);
	}

	M_LOG_IF_FLAGS(InLogFlags, TEXT("View location = %s, View rotation = %s"), *ViewLocation.ToString(), *ViewRotation.ToString());

	FHitResult HitResult;
	const AActor* const IgnoreActor = this;
	FCollisionQueryParams QueryParams { FName(TEXT("LookTraceTag")), bInTraceComplex, IgnoreActor };
	FCollisionResponseParams ResponseParams;
	const bool bHit = GetWorld()->LineTraceSingleByChannel
	(
	 	HitResult,
		ViewLocation, ViewLocation + ViewRotation.Vector() * InLength,
		InCollisionChannel,
		QueryParams,
		ResponseParams
	);
	if( ! bHit )
	{
		M_LOG_ERROR_IF_FLAGS(InLogFlags, TEXT("No actor found during the trace"));
		return nullptr;
	}
	AActor* const Actor = HitResult.Actor.Get();
	M_LOG_IF_FLAGS(InLogFlags, TEXT("Actor \"%s\" of class \"%s\" is found during the trace"), *Actor->GetName(), *Actor->GetClass()->GetName());
	return Actor;
}

void ATUPawn::OnController_Axis_LookPitch_Implementation(float InAmount)
{
	ITUController::Execute_Default_Axis_LookPitch(GetController(), this, InAmount);
}

void ATUPawn::OnController_Axis_LookYaw_Implementation(float InAmount)
{
	ITUController::Execute_Default_Axis_LookYaw(GetController(), this, InAmount);
}

void ATUPawn::OnController_Axis_Forward_Implementation(float InAmount)
{
	ITUController::Execute_Default_Axis_Forward(GetController(), this, InAmount);
}

void ATUPawn::OnController_Axis_Right_Implementation(float InAmount)
{
	ITUController::Execute_Default_Axis_Right(GetController(), this, InAmount);
}

void ATUPawn::OnController_Axis_Up_Implementation(float InAmount)
{
	ITUController::Execute_Default_Axis_Up(GetController(), this, InAmount);
}

void ATUPawn::OnController_Action_Use_Implementation()
{
	// Nothing is done here yet
}

void ATUPawn::OnController_Action_UseTwo_Implementation()
{
	// Nothing is done here yet
}

void ATUPawn::OnController_Action_UseThree_Implementation()
{
	// Nothing is done here yet
}

void ATUPawn::OnController_Action_Fire_Implementation()
{
	// Nothing is done here yet
}

void ATUPawn::OnController_Action_FireTwo_Implementation()
{
	// Nothing is done here yet
}

void ATUPawn::OnController_Action_FireThree_Implementation()
{
	// Nothing is done here yet
}

void ATUPawn::OnController_Action_SelectZero_Implementation()
{
	// Nothing is done here yet
}

void ATUPawn::OnController_Action_SelectOne_Implementation()
{
	// Nothing is done here yet
}

void ATUPawn::OnController_Action_SelectTwo_Implementation()
{
	// Nothing is done here yet
}

void ATUPawn::OnController_Action_SelectThree_Implementation()
{
	// Nothing is done here yet
}

void ATUPawn::OnController_Action_SelectFour_Implementation()
{
	// Nothing is done here yet
}

void ATUPawn::OnController_Action_SelectFive_Implementation()
{
	// Nothing is done here yet
}

void ATUPawn::OnController_Action_SelectSix_Implementation()
{
	// Nothing is done here yet
}

void ATUPawn::OnController_Action_SelectSeven_Implementation()
{
	// Nothing is done here yet
}

void ATUPawn::OnController_Action_SelectEight_Implementation()
{
	// Nothing is done here yet
}

void ATUPawn::OnController_Action_SelectNine_Implementation()
{
	// Nothing is done here yet
}

void ATUPawn::OnController_Action_OpenGameMenu_Implementation()
{
	// Nothing is done here yet
}

void ATUPawn::OnController_Action_CloseGameMenu_Implementation()
{
	// Nothing is done here yet
}

void ATUPawn::OnController_Action_DebugOne_Implementation()
{
	// Nothing is done here yet
}

void ATUPawn::OnController_Action_DebugTwo_Implementation()
{
	// Nothing is done here yet
}

void ATUPawn::OnController_Action_DebugThree_Implementation()
{
	// Nothing is done here yet
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
