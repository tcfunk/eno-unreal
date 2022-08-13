// Copyright Epic Games, Inc. All Rights Reserved.

#include "EnoGameMode.h"
#include "EnoCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEnoGameMode::AEnoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
