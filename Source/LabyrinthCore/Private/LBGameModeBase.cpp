// Fill out your copyright notice in the Description page of Project Settings.


#include "LBGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "LBPlayerCharacter.h"

ALBGameModeBase::ALBGameModeBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	TSubclassOf<ALBPlayerCharacter> findClass;
	findClass = ALBPlayerCharacter::StaticClass();
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), findClass, actors);

	if (actors.Num())
	{
		PlayerCharacter = Cast<ALBPlayerCharacter>(actors[0]);
		//FString message = FString("PlayerName:") + PlayerCharacter->GetName();
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, message);
	}

}
