#pragma once

/**
* Pawn that has collision and mesh.
*/

#include "GameFramework/Pawn.h"
#include "Util/Core/Log/MyLoggingTypes.h"
#include "Engine/EngineTypes.h"
#include "I/ITUPawnActions.h"
#include "Util/Weapon/I/IWeaponInventoryHolder.h"
#include "Util/Weapon/QuickWeaponComponent/QuickWeaponComponent.h"
#include "TUPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USceneComponent;
class UStaticMeshComponent;
class USkeletalMeshComponent;
class USphereComponent;

class UQuickWeaponComponent;

class ITUController;

UCLASS()
class ATUPawn 
: public APawn
, public ITUPawnActions
, public IWeaponInventoryHolder
{
	GENERATED_BODY()

public:
	ATUPawn();

	
	// ~Logging Begin
	virtual void LogThis();
	void LogThisIf(bool bInShouldLog);

	/**
	* If true, we log non-periodic big events, like BeginPlay, Possess etc.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug|Test")
	bool bLogBigEvents = true;
	// ~Logging End
	
	// ~APawn Begin
	virtual void PossessedBy(AController* InNewController) override;
	virtual void UnPossessed() override;
	virtual void Restart() override;

	virtual void BecomeViewTarget(APlayerController* PC) override;
	// ~APawn End
	
	// ~Helpers Begin
	/**
	* Performs a single-line trace.
	* Current pawn is always ignored.
	*/
	UFUNCTION(BlueprintCallable, Category=Trace)
	AActor* TraceByLook(bool bInTraceComplex = false, ECollisionChannel CollisionChannel = ECollisionChannel::ECC_Visibility, ELogFlags InLogFlags = ELogFlags::LogEverSuccess) const;

	AActor* TraceByLookCustom(float Length, bool bTraceComplex = false, ECollisionChannel CollisionChannel = ECollisionChannel::ECC_Visibility, ELogFlags InLogFlags = ELogFlags::LogEverSuccess) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Trace)
	float DefaultLookTraceLength = 10000.0F;
	// ~Helpers End

	// ~Components Begin
	UFUNCTION(BlueprintPure, Category = Components)
	USceneComponent* GetRootSceneComponent() const { return RootSceneComponent; }

	UFUNCTION(BlueprintPure, Category = Camera)
	UCameraComponent* GetCamera() const { return Camera; }

	UFUNCTION(BlueprintPure, Category = Visual)
	UStaticMeshComponent* GetMesh() const { return Mesh; }

	UFUNCTION(BlueprintPure, Category = Collision)
	USphereComponent* GetProxSphere() const { return ProxSphere; }
	// ~Components End
	
	// ~ITUPawnActions Begin
	// This section contains notifying functions about the controller's actions
	virtual void OnController_Axis_LookPitch_Implementation(float InAmount) override;
	virtual void OnController_Axis_LookYaw_Implementation(float InAmount) override;
	virtual void OnController_Axis_Forward_Implementation(float InAmount) override;
	virtual void OnController_Axis_Right_Implementation(float InAmount) override;
	virtual void OnController_Axis_Up_Implementation(float InAmount) override;
	virtual void OnController_Action_Use_Implementation() override;
	virtual void OnController_Action_UseTwo_Implementation() override;
	virtual void OnController_Action_UseThree_Implementation() override;
	virtual void OnController_Action_Fire_Implementation() override;
	virtual void OnController_Action_FireTwo_Implementation() override;
	virtual void OnController_Action_FireThree_Implementation() override;
	virtual void OnController_Action_SelectZero_Implementation() override;
	virtual void OnController_Action_SelectOne_Implementation() override;
	virtual void OnController_Action_SelectTwo_Implementation() override;
	virtual void OnController_Action_SelectThree_Implementation() override;
	virtual void OnController_Action_SelectFour_Implementation() override;
	virtual void OnController_Action_SelectFive_Implementation() override;
	virtual void OnController_Action_SelectSix_Implementation() override;
	virtual void OnController_Action_SelectSeven_Implementation() override;
	virtual void OnController_Action_SelectEight_Implementation() override;
	virtual void OnController_Action_SelectNine_Implementation() override;
	virtual void OnController_Action_OpenGameMenu_Implementation() override;
	virtual void OnController_Action_CloseGameMenu_Implementation() override;
	virtual void OnController_Action_DebugOne_Implementation() override;
	virtual void OnController_Action_DebugTwo_Implementation() override;
	virtual void OnController_Action_DebugThree_Implementation() override;
	// ~ITUPawnActions End

	// ~Weapon Begin
	virtual TScriptInterface<IWeaponInventory> GetWeapons_Implementation() const override { return WeaponComponent; }

	/** GetWeaponComponent*/
	UFUNCTION(BlueprintPure, Category=Weapon)
	UQuickWeaponComponent* GetWeaponComponent() const { return WeaponComponent; }

	/** To be called when the given mesh component has a socket from which to fire*/
	UFUNCTION(BlueprintCallable, Category=Weapon)
	void InitQuickWeaponSocketForComponent(FName InSocketName, FName InComponentName);

	/**
	* Fires weapon by index.
	*
	* @returns: true if fired successfully.
	*/
	UFUNCTION(BlueprintCallable, Category=Weapon)
	bool FireWeaponByIndex_IfCan(int32 InWeaponIndex);

	virtual void PawnStartFire(uint8 FireModeNum) override;
	// ~Weapon End

	// ~Controller Begin
	UFUNCTION(BlueprintPure, Category = Controller, Meta=(DisplayName="GetTUController"))
	TScriptInterface<ITUController> K2GetTUController() const;

	UFUNCTION(BlueprintPure, Category = Controller, Meta=(DisplayName="GetTUControllerLogged"))
	TScriptInterface<ITUController> K2GetTUControllerLogged(ELogFlags InLogFlags = ELogFlags::None) const;

	UFUNCTION(BlueprintPure, Category = Controller, Meta=(DisplayName="GetTUControllerChecked"))
	TScriptInterface<ITUController> K2GetTUControllerChecked() const;

	ITUController* GetTUController() const;
	ITUController* GetTUControllerLogged(ELogFlags InLogFlags = ELogFlags::None) const;
	ITUController* GetTUControllerChecked() const ;

	UFUNCTION(BlueprintPure, Category = Controller)
	AController* GetControllerLogged(ELogFlags InLogFlags = ELogFlags::None) const;

	UFUNCTION(BlueprintPure, Category = Controller)
	AController* GetControllerChecked() const;

	UFUNCTION(BlueprintPure, Category = Controller)
	APlayerController* GetPC() const;

	UFUNCTION(BlueprintPure, Category = Controller)
	APlayerController* GetPCLogged(ELogFlags InLogFlags = ELogFlags::None) const;

	UFUNCTION(BlueprintPure, Category = Controller)
	APlayerController* GetPCChecked() const;
	// ~Controller End
	
	// ~UObject Begin
	virtual void PostInitProperties() override;
	// ~UObject End

	// ~AActor Begin
	virtual void PreRegisterAllComponents() override;
	virtual void PostRegisterAllComponents() override;

	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;
	/**
	* AActor::BeginPlay implementation
	*
	* @note: marked as final, override MyBeginPlay instead
	* @see: MyBeginPlay
	*/
	virtual void BeginPlay() override final;
	// ~AActor End
	
protected:
	// ~Framework Begin
	/**
	* WARNING!!! Override THIS function instead of BeginPlay!!!
	* (we need that Post-beginplay actions to be called inside BeginPlay).
	*
	* @bote: call Super when overriding;
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Framework)
	void MyBeginPlay();
	// ~Framework End

private:
	// ~Framework Begin
	/**
	* Called when Begin play is finished.
	*/	
	UFUNCTION(BlueprintCallable)
	virtual void BeginPlayFinished();
	// ~Framework End

	// ~Components Begin
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Components, Meta=(AllowPrivateAccess = true))
	USceneComponent* RootSceneComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera, Meta=(AllowPrivateAccess = true))
	UCameraComponent* Camera = nullptr;
	void InitCameraAndSpringArm(USceneComponent* InAttachTo);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera, Meta=(AllowPrivateAccess = true))
	USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Visual, Meta=(AllowPrivateAccess = true))
	UStaticMeshComponent* Mesh = nullptr;
	void InitMesh(USceneComponent* InAttachTo);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Collision, Meta=(AllowPrivateAccess = true))
	USphereComponent* ProxSphere = nullptr;
	void InitProxSphere(USceneComponent* InAttachTo);


	/** WeaponComponent*/
	void InitWeaponComponent();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta=(AllowPrivateAccess=true))
	UQuickWeaponComponent* WeaponComponent = nullptr;
	// ~Components End
};
