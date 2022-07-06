// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "KOK_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SphereComponent.h"
#include "MainCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/SkeletalMeshSocket.h"

// Sets default values
AEnemy::AEnemy() : bCanAttack(true), AttackWaitTime(1.f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the Agro Sphere
	AgroSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AgroSphere"));
	AgroSphere->SetupAttachment(GetRootComponent());

	// Create the Combat Range Sphere
	CombatRangeSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CombatRange"));
	CombatRangeSphere->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	AgroSphere->OnComponentBeginOverlap.AddDynamic(
		this,
		&AEnemy::AgroSphereOverlap);
	CombatRangeSphere->OnComponentBeginOverlap.AddDynamic(
		this,
		&AEnemy::CombatRangeOverlap);
	CombatRangeSphere->OnComponentEndOverlap.AddDynamic(
		this,
		&AEnemy::CombatRangeEndOverlap);

	// Get the AI Controller
	KOK_AIController = Cast<AKOK_AIController>(GetController());

	/*if (KOK_AIController)
	{
		KOK_AIController->GetBlackboardComponent()->SetValueAsBool(
			FName("CanAttack"), true);
	}
	*/
	const FVector WorldPatrolPoint = UKismetMathLibrary::TransformLocation(GetActorTransform(), PatrolPoint);
	const FVector WorldPatrolPoint2 = UKismetMathLibrary::TransformLocation(GetActorTransform(), PatrolPoint2);

	if (KOK_AIController)
	{
		KOK_AIController->GetBlackboardComponent()->SetValueAsVector(
			TEXT("PatrolPoint"),
			WorldPatrolPoint);

		KOK_AIController->GetBlackboardComponent()->SetValueAsVector(
			TEXT("PatrolPoint2"),
			WorldPatrolPoint2);

		KOK_AIController->RunBehaviorTree(BehaviorTree);
	}
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::AgroSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr) return;

	auto Character = Cast<AMainCharacter>(OtherActor);
	if (Character)
	{
		if (KOK_AIController)
		{
			if (KOK_AIController->GetBlackboardComponent())
			{
				KOK_AIController->GetBlackboardComponent()->SetValueAsObject(
					TEXT("Target"),
					Character);
			}
		}
	}
}

void AEnemy::CombatRangeOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr) return;
	auto ShooterCharacter = Cast<AMainCharacter>(OtherActor);
	if (ShooterCharacter)
	{
		bInAttackRange = true;
		if (KOK_AIController)
		{
			KOK_AIController->GetBlackboardComponent()->SetValueAsBool(
				TEXT("InAttackRange"),
				true
			);
		}
	}
}

void AEnemy::CombatRangeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == nullptr) return;
	auto ShooterCharacter = Cast<AMainCharacter>(OtherActor);
	if (ShooterCharacter)
	{
		bInAttackRange = false;
		if (KOK_AIController)
		{
			KOK_AIController->GetBlackboardComponent()->SetValueAsBool(
				TEXT("InAttackRange"),
				false
			);
		}
	}

}

void AEnemy::PlayAttackMontage(FName Section, float PlayRate)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && AttackMontage)
	{
		AnimInstance->Montage_Play(AttackMontage);
		AnimInstance->Montage_JumpToSection(Section, AttackMontage);
	}
	bCanAttack = false;
	GetWorldTimerManager().SetTimer(
		AttackWaitTimer,
		this,
		&AEnemy::ResetCanAttack,
		AttackWaitTime
	);
	if (KOK_AIController)
	{
		KOK_AIController->GetBlackboardComponent()->SetValueAsBool(
			FName("CanAttack"),
			false);
	}
}

void AEnemy::ResetCanAttack()
{
	bCanAttack = true;
	if (KOK_AIController)
	{
		KOK_AIController->GetBlackboardComponent()->SetValueAsBool(
			FName("CanAttack"),
			true);
	}
}
