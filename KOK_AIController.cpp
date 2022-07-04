// Fill out your copyright notice in the Description page of Project Settings.


#include "KOK_AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AKOK_AIController::HomePosKey(TEXT("HomePos"));
const FName AKOK_AIController::PatrolPosKey(TEXT("PatrolPos"));
const FName AKOK_AIController::TargetKey(TEXT("Target"));

AKOK_AIController::AKOK_AIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/_Game/AI/BB_MICharacter.BB_MICharacter"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/_Game/AI/BT_MICharacter.BT_MICharacter"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}

void AKOK_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AKOK_AIController::RunAI()
{
	if (UseBlackboard(BBAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(HomePosKey, GetPawn()->GetActorLocation());
	}
}

void AKOK_AIController::StopAI()
{
	auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (nullptr != BehaviorTreeComponent)
	{
		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
	}
}

