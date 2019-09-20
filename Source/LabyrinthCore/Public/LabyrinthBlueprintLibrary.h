// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LabyrinthBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class LABYRINTHCORE_API ULabyrinthBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/** Returns true if this is being run from an editor preview */
	UFUNCTION(BlueprintPure, Category = Loading)
	static bool IsInEditor();

};
