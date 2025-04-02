// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SubTitleStructure.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct FSubTitleStructure : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString Text;

	UPROPERTY(EditAnywhere)
	float Time;

};
