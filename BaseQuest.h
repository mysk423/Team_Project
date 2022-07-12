// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Enemy.h"
#include "BaseQuest.generated.h"

UENUM(BlueprintType)
enum class EQuestReward : uint8 {
	E_Default	UMETA(DisplayName = "DEFAULT"),
	E_Experience UMETA(DisplayName = "EXPERIENCE"),
	E_Item	UMETA(DisplayName = "ITEM")
};

UENUM(BlueprintType)
enum class EClearCondition : uint8 {
	E_Default	UMETA(DisplayName = "DEFAULT"),
	E_Slay	UMETA(DisplayName = "SLAY"),
	E_Collet	UMETA(DisplayName = "COLLECT"),
	E_Travel	UMETA(DisplayName = "TRAVEL")
};

USTRUCT(BlueprintType)
struct FReward {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EQuestReward rewardType;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//ADefaultItem* item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float exp;
};

USTRUCT(BlueprintType)
struct FObjective {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EClearCondition clearType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AEnemy> enemyToSlay;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//ADefaultItem* itemCollet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int objeciveID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsComplete;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int numRequired;
};

/**
 * 
 */
UCLASS(BlueprintType)
class TEAM_PROJECT_API UBaseQuest : public UObject
{
	GENERATED_BODY()

	UBaseQuest();

public:
	UFUNCTION(BlueprintCallable)
	void SetQuestDetails(FString _name, FString _description);

	UFUNCTION(BlueprintCallable)
	void SetUpObjective(int _objeciveNum, TSubclassOf<AEnemy> _enemy, FString _description, int _numRequired);

	UFUNCTION(BlueprintCallable)
	void SetNumObjectives(int _numObjectives);

	UFUNCTION(BlueprintCallable)
	void UpdateQuest();

	UFUNCTION(BlueprintCallable)
	void UpdateObjective(int _objectiveNum, int _updateValue);

	UFUNCTION(BlueprintCallable)
	void FinishObjective(int _objeciveNum);

	UFUNCTION(BlueprintCallable)
	void FinishQuest();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FReward reward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FObjective> objectives;
};
