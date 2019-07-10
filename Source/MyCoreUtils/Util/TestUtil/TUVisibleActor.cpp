#include "TUVisibleActor.h"
#include "Util/Core/LogUtilLib.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/SphereComponent.h"

ATUVisibleActor::ATUVisibleActor()
{
	M_NOT_IMPL_MSG(TEXT("Collision profile, movement settings"));

	RootComponent = RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));

	InitCameraAndSpringArm(RootSceneComponent);
	InitMesh(RootSceneComponent);
	InitProxSphere(RootSceneComponent);
}

void ATUVisibleActor::InitCameraAndSpringArm(USceneComponent* InAttachTo)
{
	checkf(InAttachTo, TEXT("When calling %s component to attach to must be non-NULL pointer"), TEXT(__FUNCTION__));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	M_NOT_IMPL();
	SpringArm->SetupAttachment(InAttachTo);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	M_NOT_IMPL();
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

void ATUVisibleActor::InitMesh(USceneComponent* InAttachTo)
{
	checkf(InAttachTo, TEXT("When calling %s component to attach to must be non-NULL pointer"), TEXT(__FUNCTION__));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	M_NOT_IMPL();
	Mesh->SetupAttachment(InAttachTo);
}

void ATUVisibleActor::InitProxSphere(USceneComponent* InAttachTo)
{
	checkf(InAttachTo, TEXT("When calling %s component to attach to must be non-NULL pointer"), TEXT(__FUNCTION__));

	ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	M_NOT_IMPL();
	ProxSphere->SetupAttachment(InAttachTo);
}
