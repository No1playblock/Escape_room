// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Components/AudioComponent.h"
#include "Escape_RoomCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class UEnhancedInputComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UENUM(BlueprintType)
enum class ECharacterMapState : uint8
{
	Map1 UMETA(DisplayName = "Map1"),
	Map2 UMETA(DisplayName = "Map2"),
	Map3 UMETA(DisplayName = "Map3")
};
UCLASS(config=Game)
class AEscape_RoomCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	void SetHasBow(bool bNewHasBow);

	bool GetHasBow();

	void SetHasKey(bool bNewHasKey);

	bool GetHasKey();

	void KilZombie();

	void UnbindAction();

	FORCEINLINE void SetCanShoot(bool InCanShoot) { CanShoot = InCanShoot; }

	FORCEINLINE void SetCurrentMap(ECharacterMapState InCurrentMap) { CurrentMap = InCurrentMap; }

private:
	AEscape_RoomCharacter();

	virtual void BeginPlay();

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	void LineTracing();

	void PlayBowPullSound();

	void SetWidget();

	void PlayWalkingSound();

	void QuitGame();

	void ShootArrow();

	//ÄÄÆ÷³ÍÆ®
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	TObjectPtr<USkeletalMeshComponent> Mesh1P;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> KeyPosition;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BowPosition;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> ArrowPosition;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<UCameraComponent> FirstPersonCameraComponent;

	//MappinContext
	UPROPERTY(EditAnywhere,Category=Input)
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> ShootMappingContext;


	//Move Input Action
	UPROPERTY(EditAnywhere, Category=Input)
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> QuitAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> ClickAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> ShootAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> LookAction;

	//Sound
	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<USoundBase> KeyWalkingSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<USoundBase> Map1_WalkingSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<USoundBase> Map2_WalkingSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<USoundBase> OpenBedSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<USoundBase> PickUpKeySound;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<USoundBase> ShootArrowSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<USoundBase> BowPullSound;

	//UI
	
	TObjectPtr<UUserWidget> WidgetInstance;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> PointerWidget;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> CrossHairWidget;


	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraShakeBase> CameraShake;


	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<AActor> Arrow;

	TObjectPtr<UAudioComponent> WalkAudioComponent;
	TObjectPtr<UAudioComponent> WalkWithKeyAudioComponent;
	TObjectPtr<UAudioComponent> BowPullAudioComponent;
	
	

	int ZombieKillCount = 0;

	ECharacterMapState CurrentMap;

	double ClickStart=0.0;
	double ClickEnd=0.0;

	bool bHasBow;

	bool bHasKey;

	bool CanShoot = true;

	FTimerHandle WalkingSoundTimer;

	FTimerHandle CameraShakeTimer;

	FTimerHandle WalkingKWithKeySoundTimer;

	UEnhancedInputComponent* EnhancedInputComponent;

	bool IsFirstClick = false;

	float WalkingIntervalTime;

	float CameraShakeIntervalTime;

};

