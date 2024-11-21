// Copyright Epic Games, Inc. All Rights Reserved.

#include "Escape_RoomCharacter.h"
#include "Escape_RoomProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "DrawDebugHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Drawer.h"
#include "Bed.h"
#include "Arrow.h"
#include "CrossHairWidget.h"
#include "PointerWidget.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AEscape_RoomCharacter

AEscape_RoomCharacter::AEscape_RoomCharacter()
{
	// Character doesnt have a rifle at start

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	CurrentMap = ECharacterMapState::Map1;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	KeyPosition = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyPosition"));
	KeyPosition->SetupAttachment(FirstPersonCameraComponent);

	BowPosition = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BowPosition"));
	BowPosition->SetupAttachment(FirstPersonCameraComponent);
	BowPosition->SetRelativeRotation(FRotator(-29.054887f, 65.126466f, -162.936960f));

	ArrowPosition = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowPosition"));
	ArrowPosition->SetupAttachment(BowPosition);

	ArrowPosition->SetHiddenInGame(true);
}

void AEscape_RoomCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	SetWidget();
	SetHasBow(false);
	SetHasKey(false);
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}
void AEscape_RoomCharacter::KilZombie()
{
	zombieKillCount++;
	if (zombieKillCount == 4)
	{
		if (WidgetInstance && WidgetInstance->IsInViewport())
		{
			WidgetInstance->RemoveFromParent();
		}
		WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), CrossHairWidget);
		Cast<UCrossHairWidget>(WidgetInstance)->SubTitle7();
		if (WidgetInstance)
		{
			WidgetInstance->AddToViewport();
		}

	}
}

void AEscape_RoomCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AEscape_RoomCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AEscape_RoomCharacter::Look);

		EnhancedInputComponent->BindAction(QuitAction, ETriggerEvent::Triggered, this, &AEscape_RoomCharacter::QuitGame);

		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Triggered, this, &AEscape_RoomCharacter::LineTracing);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Completed, this, &AEscape_RoomCharacter::ShootArrow);


	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}
void AEscape_RoomCharacter::UnbindAction()
{

	if (EnhancedInputComponent)
	{
		// ActionName에 해당하는 모든 바인딩을 제거합니다.

		EnhancedInputComponent->ClearActionBindings();
		EnhancedInputComponent->BindAction(QuitAction, ETriggerEvent::Triggered, this, &AEscape_RoomCharacter::QuitGame);
	}
}
void AEscape_RoomCharacter::QuitGame()
{

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->ConsoleCommand("quit");
}
void AEscape_RoomCharacter::LineTracing()
{

	FVector2D ViewportSize;
	if (GEngine && GEngine->GameViewport)
		GEngine->GameViewport->GetViewportSize(ViewportSize);

	FVector2D CrosshairLocation(ViewportSize.X / 2.0f, ViewportSize.Y / 2.0f);

	FVector CrosshairWorldPosition;
	FVector CrosshairWorldDirection;

	bool bScreenToWorld = UGameplayStatics::GetPlayerController(this, 0)->
		DeprojectScreenPositionToWorld(CrosshairLocation.X, CrosshairLocation.Y, CrosshairWorldPosition, CrosshairWorldDirection);

	if (bScreenToWorld)
	{
		FHitResult ScreenTraceHit;
		const FVector Start = CrosshairWorldPosition;
		const FVector End = Start + CrosshairWorldDirection * 50'000.0f;

		GetWorld()->LineTraceSingleByChannel(ScreenTraceHit, Start, End, ECollisionChannel::ECC_Visibility);

		if (!GetHasBow() && ScreenTraceHit.bBlockingHit)
		{

			//Line 그리기
			//DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f);

			if (ScreenTraceHit.GetActor()->ActorHasTag("Bow"))
			{
				SetHasBow(true);
				SetWidget();
				ScreenTraceHit.GetActor()->Destroy();

			}
			else if (ScreenTraceHit.GetActor()->ActorHasTag("Key"))
			{
				SetHasKey(true);
				SetWidget();
				UGameplayStatics::PlaySoundAtLocation(this, PickUpKeySound, GetActorLocation());
				ScreenTraceHit.GetActor()->Destroy();


			}

			else if (ScreenTraceHit.GetActor()->ActorHasTag("Bed") && GetHasKey())
			{
				//Bed Open
				SetHasKey(false);

				Cast<ABed>(ScreenTraceHit.GetActor())->OpenBed();

			}
			else if (ScreenTraceHit.GetActor()->ActorHasTag("Drawer"))
			{
				//Drawer Open 
				Cast<ADrawer>(ScreenTraceHit.GetActor())->OpenDrawer();

			}
		}
		else if (GetHasBow() && CanShoot)
		{

			if (BowPullSound)
			{
				BowPullAudioComponent = UGameplayStatics::SpawnSound2D(this, BowPullSound);

				BowPosition->SetRelativeLocation(FVector(29.975149f, 29.686334f, -10.f));
				BowPosition->SetRelativeRotation(FRotator(-80.312072, -0.689265, -79.197716));		//쏠때 활 세우기

				ArrowPosition->SetHiddenInGame(false);
				ClickStart = FPlatformTime::Seconds();

			}


		}
	}
}
void AEscape_RoomCharacter::PlayBowPullSound()
{
	if (BowPullSound)
	{

		BowPullAudioComponent = UGameplayStatics::SpawnSound2D(this, BowPullSound);
	}

}
void AEscape_RoomCharacter::ShootArrow()
{
	if (!IsFirstClick)
	{
		IsFirstClick = true;
		return;
	}
	if (!CanShoot)
	{
		return;
	}
	BowPosition->SetRelativeLocation(FVector(29.975149f, 25.0f, -30.974728f));
	BowPosition->SetRelativeRotation(FRotator(-29.054887f, 65.126466f, -162.936960f));		//쏘고나서 활 눕히기

	ArrowPosition->SetHiddenInGame(true);
	ClickEnd = FPlatformTime::Seconds();

	if (BowPullAudioComponent!=nullptr && BowPullAudioComponent->IsPlaying())
	{

		BowPullAudioComponent->Stop();
		BowPullAudioComponent = nullptr;

	}
	else if (!BowPullAudioComponent->IsPlaying())
	{
		BowPullAudioComponent = nullptr;
	}
	double ArrowSpeed = ClickEnd - ClickStart;

	if (ArrowSpeed > 3.3f)
	{
		ArrowSpeed = 3.3f;
	}
	else if (ArrowSpeed < 0.7f)
	{
		return;
	}
	

	FVector2D ViewportSize;
	if (GEngine && GEngine->GameViewport)
		GEngine->GameViewport->GetViewportSize(ViewportSize);

	FVector2D CrosshairLocation(ViewportSize.X / 2.0f, ViewportSize.Y / 2.0f);

	FVector CrosshairWorldPosition;
	FVector CrosshairWorldDirection;

	bool bScreenToWorld = UGameplayStatics::GetPlayerController(this, 0)->
		DeprojectScreenPositionToWorld(CrosshairLocation.X, CrosshairLocation.Y, CrosshairWorldPosition, CrosshairWorldDirection);


	if (bScreenToWorld)
	{
		FHitResult ScreenTraceHit;
		const FVector Start = CrosshairWorldPosition;
		const FVector End = Start + CrosshairWorldDirection * 50'000.0f;


		GetWorld()->LineTraceSingleByChannel(ScreenTraceHit, Start, End, ECollisionChannel::ECC_Visibility);

		FVector Direction = ScreenTraceHit.Location - BowPosition->GetComponentLocation();

		UGameplayStatics::SpawnSound2D(this, ShootArrowSound);

		AArrow* arrow = GetWorld()->SpawnActor<AArrow>(Arrow, BowPosition->GetComponentLocation(), Direction.Rotation());

		arrow->GetProjectileMovement()->Velocity = Direction.GetSafeNormal() * ArrowSpeed * 2000.0f;
	}

}



void AEscape_RoomCharacter::SetWidget() {

	if (WidgetInstance && WidgetInstance->IsInViewport())
	{
		WidgetInstance->RemoveFromParent();
	}

	if (GetHasBow())
	{
		if (CrossHairWidget)
		{

			WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), CrossHairWidget);

			Cast<UCrossHairWidget>(WidgetInstance)->SubTitle1();
		}
	}
	else
	{
		if (PointerWidget)
		{
			WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), PointerWidget);
			if (GetHasKey())
			{
				Cast<UPointerWidget>(WidgetInstance)->HasKeySubTitle();
			}
			else
			{
				Cast<UPointerWidget>(WidgetInstance)->StartSubTitle();
			}
		}
	}
	if (WidgetInstance)
	{
		WidgetInstance->AddToViewport();
	}
}

void AEscape_RoomCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PlayWalkingSound();
}
void AEscape_RoomCharacter::PlayWalkingSound()
{
	if (GetHasKey())		//열쇠를 가지고 있으면 열쇠짤랑소리 출력
	{
		if (GetVelocity().Size() > 0)
		{
			if (!GetWorld()->GetTimerManager().IsTimerActive(WalkingKWithKeySoundTimer))
			{
				if (KeyWalkingSound)
				{

					WalkWithKeyAudioComponent = UGameplayStatics::SpawnSound2D(this, KeyWalkingSound);
				}
				GetWorld()->GetTimerManager().SetTimer(WalkingKWithKeySoundTimer, this, &AEscape_RoomCharacter::PlayWalkingSound, 5.0f, false); // Adjust the interval as needed
			}
		}
		else
		{
			if (WalkWithKeyAudioComponent)
			{
				WalkWithKeyAudioComponent->Stop();
				GetWorld()->GetTimerManager().ClearTimer(WalkingKWithKeySoundTimer);
				WalkWithKeyAudioComponent = nullptr;
			}
		}
	}

	USoundBase* WalkingSound;
	switch (CurrentMap)
	{
	case ECharacterMapState::Map1:
		WalkingSound = Map1_WalkingSound;
		WalkingIntervalTime = 6.7f;
		CameraShakeIntervalTime = 0.7f;
		break;
	case ECharacterMapState::Map2:
		WalkingSound = Map2_WalkingSound;
		WalkingIntervalTime = 29.0f;
		CameraShakeIntervalTime = 0.8f;
		break;
	case ECharacterMapState::Map3:
		WalkingSound = Map2_WalkingSound;
		WalkingIntervalTime = 29.0f;
		CameraShakeIntervalTime = 0.8f;
		break;
	default:
		WalkingSound = Map1_WalkingSound;
		WalkingIntervalTime = 6.7f;
		CameraShakeIntervalTime = 0.7f;
		break;
	}

	if (GetVelocity().Size() > 0)
	{
		if (!GetWorld()->GetTimerManager().IsTimerActive(WalkingSoundTimer))
		{
			if (KeyWalkingSound)
			{
				WalkAudioComponent = UGameplayStatics::SpawnSound2D(this, WalkingSound);
				APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
				if (PlayerController)
				{
					UGameplayStatics::PlayWorldCameraShake(this, CameraShake, GetActorLocation(), 0.f, 5000.f);

				}
			}
			GetWorld()->GetTimerManager().SetTimer(WalkingSoundTimer, this, &AEscape_RoomCharacter::PlayWalkingSound, WalkingIntervalTime, false); // Adjust the interval as needed
		}
		if (!GetWorld()->GetTimerManager().IsTimerActive(CameraShakeTimer))
		{
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
			if (PlayerController)
			{
				UGameplayStatics::PlayWorldCameraShake(this, CameraShake, GetActorLocation(), 0.f, 5000.f);

			}
			GetWorld()->GetTimerManager().SetTimer(CameraShakeTimer, this, &AEscape_RoomCharacter::PlayWalkingSound, CameraShakeIntervalTime, false); // Adjust the interval as needed
		}
	}
	else
	{

		if (WalkAudioComponent)
		{
			WalkAudioComponent->Stop();
			GetWorld()->GetTimerManager().ClearTimer(WalkingSoundTimer);
			WalkAudioComponent = nullptr;
		}

	}

}

void AEscape_RoomCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		PlayWalkingSound();

		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AEscape_RoomCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}


void AEscape_RoomCharacter::SetHasBow(bool bNewHasBow)
{
	bHasBow = bNewHasBow;
	if (BowPosition)
	{

		BowPosition->SetHiddenInGame((!bHasBow));
	}
	if (bHasBow)
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				Subsystem->AddMappingContext(ShootMappingContext, 1);
			}
		}
	}

}

bool AEscape_RoomCharacter::GetHasBow()
{
	return bHasBow;
}

void AEscape_RoomCharacter::SetHasKey(bool bNewHasKey)
{
	bHasKey = bNewHasKey;
	if (KeyPosition)
	{

		KeyPosition->SetHiddenInGame((!bHasKey));
	}

}

bool AEscape_RoomCharacter::GetHasKey()
{
	return bHasKey;
}
