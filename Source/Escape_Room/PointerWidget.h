// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PointerWidget.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPE_ROOM_API UPointerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Custom")
	void HasKeySubTitle();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Custom")
	void StartSubTitle();
	
};
