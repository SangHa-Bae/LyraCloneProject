// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine/GameInstance.h"

#include "LyraCloneGameInstance.generated.h"

UCLASS()
class ULyraCloneGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	ULyraCloneGameInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void Init() override;
	virtual void Shutdown() override;
};
