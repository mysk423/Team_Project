// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseQuest.h"

UBaseQuest::UBaseQuest() {
	name = "Default Quest";
	description = "Go do this!";

	reward.rewardType = EQuestReward::E_Default;
	reward.exp = 100.0f;

}

void UBaseQuest::SetQuestDetails(FString _name, FString _description)
{
	name = _name;
	description = _description;
}

void UBaseQuest::SetUpObjective(int _objeciveNum, TSubclassOf<AEnemy> _enemy, FString _description, int _numRequired)
{
	if (_objeciveNum < objectives.Num())
	{
		if (_enemy != nullptr)
		{
			objectives[_objeciveNum].clearType = EClearCondition::E_Slay;
			objectives[_objeciveNum].enemyToSlay = _enemy;
		}
		objectives[_objeciveNum].description = _description;
		objectives[_objeciveNum].numRequired = _numRequired;
	}
}

void UBaseQuest::SetNumObjectives(int _numObjectives)
{
	objectives.SetNum(_numObjectives);
}

void UBaseQuest::UpdateQuest()
{
}

void UBaseQuest::UpdateObjective(int _objectiveNum, int _updateValue)
{
}

void UBaseQuest::FinishObjective(int _objeciveNum)
{
}

void UBaseQuest::FinishQuest()
{
}
