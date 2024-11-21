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

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* KeyPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BowPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ArrowPosition;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* ShootMappingContext;


	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* QuitAction;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ClickAction;
	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound", meta = (AllowPrivateAccess = "true"))
    USoundBase* KeyWalkingSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	USoundBase* Map1_WalkingSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	USoundBase* Map2_WalkingSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShakeBase> CameraShake;
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	USoundBase* OpenBedSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	USoundBase* PickUpKeySound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	USoundBase* ShootArrowSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	USoundBase* BowPullSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UUserWidget* WidgetInstance;

	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> PointerWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> Arrow;

	UAudioComponent* WalkAudioComponent;
	UAudioComponent* WalkWithKeyAudioComponent;
	UAudioComponent* BowPullAudioComponent;
	
public:
	AEscape_RoomCharacter();

	
	void KilZombie();
	// À§Á¬ Å¬·¡½º
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> CrossHairWidget;

protected:
	virtual void BeginPlay();

	int zombieKillCount = 0;

	void LineTracing();

	void PlayBowPullSound();

	void SetWidget();

	virtual void Tick(float DeltaTime) override;

	void PlayWalkingSound();

	double ClickStart=0.0;
	double ClickEnd=0.0;

public:
		
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasBow;

	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasKey;

	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasBow(bool bNewHasBow);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasBow();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetHasKey(bool bNewHasKey);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool GetHasKey();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECharacterMapState CurrentMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanShoot = true;

	UFUNCTION(BlueprintCallable)
	void UnbindAction();
protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	
	

	void QuitGame();

	void ShootArrow();
	
	FTimerHandle WalkingSoundTimer;

	FTimerHandle CameraShakeTimer;

	FTimerHandle WalkingKWithKeySoundTimer;
	// End of APawn interface

private:
	UEnhancedInputComponent* EnhancedInputComponent;

	bool IsFirstClick = false;

	float WalkingIntervalTime;

	float CameraShakeIntervalTime;

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }



};

