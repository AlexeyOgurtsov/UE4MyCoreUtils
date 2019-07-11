
#include "TUPawn.h"
#include "Util/Core/LogUtilLib.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/SphereComponent.h"

#include "UObject/ConstructorHelpers.h"

ATUPawn::ATUPawn()
{
	RootComponent = RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));

	InitCameraAndSpringArm(RootSceneComponent);
	InitMesh(RootSceneComponent);
	InitProxSphere(RootSceneComponent);
}

void ATUPawn::InitCameraAndSpringArm(USceneComponent* InAttachTo)
{
	checkf(InAttachTo, TEXT("When calling %s component to attach to must be non-NULL pointer"), TEXT(__FUNCTION__));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = 400.0F;
	SpringArm->RelativeRotation = FRotator{-45.f, 0, 0 };
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 3.0F;
	SpringArm->SetupAttachment(InAttachTo);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

void ATUPawn::InitMesh(USceneComponent* InAttachTo)
{
	checkf(InAttachTo, TEXT("When calling %s component to attach to must be non-NULL pointer"), TEXT(__FUNCTION__));

	constexpr const TCHAR* DEFAULT_MESH_ASSET_PATH = TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'");

	static ConstructorHelpers::FObjectFinderOptional<UStaticMesh> MeshFinder { DEFAULT_MESH_ASSET_PATH };
	M_LOG_ERROR_IF( ! MeshFinder.Succeeded(), TEXT("Default mesh (\"%s\") NOT found"), DEFAULT_MESH_ASSET_PATH);

	{
		Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
		if(MeshFinder.Succeeded())
		{
			M_LOG(TEXT("Default mesh (\"%s\") found, setting it up"), DEFAULT_MESH_ASSET_PATH);
			Mesh->SetStaticMesh(MeshFinder.Get());
		}

		Mesh->SetupAttachment(InAttachTo);
	}
}

void ATUPawn::InitProxSphere(USceneComponent* InAttachTo)
{
	checkf(InAttachTo, TEXT("When calling %s component to attach to must be non-NULL pointer"), TEXT(__FUNCTION__));

	ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	ProxSphere->InitSphereRadius(100.0f);
	ProxSphere->SetupAttachment(InAttachTo);
}
