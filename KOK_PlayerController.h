// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "KOK_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TEAM_PROJECT_API AKOK_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AKOK_PlayerController();

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widget, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> HUDOverlayClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Widget, meta = (AllowPrivateAccess = "true"))
	UUserWidget* HUDOverlay;
	
};
