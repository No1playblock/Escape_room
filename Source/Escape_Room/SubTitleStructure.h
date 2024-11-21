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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Time;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bPlayingSound;*/
};