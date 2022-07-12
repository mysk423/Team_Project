// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"
#include "Components/BoxComponent.h"
#include "MainCharacter.h"
#include "Components/WidgetComponent.h"

// Sets default values
ANPC::ANPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InterActionCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("InterActionCaplsue"));
	InterActionCollision->SetupAttachment(GetRootComponent());
	InterActionCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	InterActionCollision->SetCollisionResponseToChannel(
		ECollisionChannel::ECC_Visibility,
		ECollisionResponse::ECR_Block
	);

	InterActionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InterActionWidget"));
	InterActionWidget->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
	InterActionWidget->SetVisibility(false);
	InterActionCollision->OnComponentBeginOverlap.AddDynamic(this, &ANPC::OnBoxOverlap);
	InterActionCollision->OnComponentEndOverlap.AddDynamic(this, &ANPC::OnBoxEndOverLap);

	if (InterActionWidget)
	{
		InterActionWidget->SetVisibility(false);
	}
}

void ANPC::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
		if (MainCharacter)
		{
			InterActionWidget->SetVisibility(true);
		}
	}
}

void ANPC::OnBoxEndOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
		if (MainCharacter)
		{
			InterActionWidget->SetVisibility(false);
		}
	}
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

