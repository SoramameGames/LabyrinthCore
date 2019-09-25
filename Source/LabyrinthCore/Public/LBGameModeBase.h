// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LBGameModeBase.generated.h"

class ALBPlayerCharacter;

/**
 * 
 */
UCLASS()
class LABYRINTHCORE_API ALBGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ALBGameModeBase(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintReadOnly, Category = "Labyrinth")
		class ALBPlayerCharacter* PlayerCharacter;

};
