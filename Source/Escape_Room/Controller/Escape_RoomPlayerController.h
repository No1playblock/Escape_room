// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Escape_RoomPlayerController.generated.h"

class UInputMappingContext;

/**
 *
 */
UCLASS()
class ESCAPE_ROOM_API AEscape_RoomPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* InputMappingContext;

	virtual void BeginPlay() override;
};
