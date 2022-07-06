// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"

// Sets default values
AMainCharacter::AMainCharacter() : BaseTurnRate(45.f),BaseLookUpRate(45.f), CameraDefaultFOV(0.f), CameraCurrentFOV(0.f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 180.f; // The camera follows at this distance behind the character
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	CameraBoom->SocketOffset = FVector(0.f, 50.f, 70.f);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach camera to end of boom
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = false; // Character moves in the direction of input...
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f); // ... at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	//AIControllerClass = AKOK_AIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bIsAttackNextAttack = false;
	bAttacking = false;
	bLMBDown = false;
	ComboCnt = 0;

	bStrongAttack = false;
	
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (FollowCamera)
	{
		CameraDefaultFOV = GetFollowCamera()->FieldOfView;
		CameraCurrentFOV = CameraDefaultFOV;
	}
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Forward", this, &AMainCharacter::Forward);
	PlayerInputComponent->BindAxis("Right", this, &AMainCharacter::Right);
	PlayerInputComponent->BindAxis("Turn", this, &AMainCharacter::Turn);
	PlayerInputComponent->BindAxis("Lookup", this, &AMainCharacter::Lookup);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("LMB", IE_Pressed, this, &AMainCharacter::LMBDown);
	PlayerInputComponent->BindAction("LMB", IE_Released, this, &AMainCharacter::LMBUp);

	PlayerInputComponent->BindAction("StrongAttack", IE_Pressed, this, &AMainCharacter::StrongAttack);
	PlayerInputComponent->BindAction("StrongAttack", IE_Released, this, &AMainCharacter::NotStrongAttack);
}

void AMainCharacter::Forward(float value)
{
	if ((Controller != nullptr) && (value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation{ Controller->GetControlRotation() };
		const FRotator YawRotation{ 0, Rotation.Yaw, 0 };

		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::X) };
		AddMovementInput(Direction, value);
	}
}

void AMainCharacter::Right(float value)
{
	if ((Controller != nullptr) && (value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation{ Controller->GetControlRotation() };
		const FRotator YawRotation{ 0, Rotation.Yaw, 0 };

		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::Y) };
		AddMovementInput(Direction, value);
	}
}

void AMainCharacter::Turn(float value)
{
	AddControllerYawInput(value);

}

void AMainCharacter::Lookup(float value)
{
	AddControllerPitchInput(value);
}

void AMainCharacter::LMBDown()
{
	UE_LOG(LogTemp, Warning, TEXT("LMBDown()"))
		bLMBDown = true;
	
	//공격중이지 않을때
	if (bAttacking == false)
	{
		Attack();
	}
	//공격중일때
	else if (bAttacking == true)
	{
		bIsAttackNextAttack = true;
	}

}

void AMainCharacter::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("Attack!!()"))

		bLMBDown = true;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (!AnimInstance || !AttackMontage)
	{
		UE_LOG(LogTemp, Warning, TEXT("Please Check Montage!!"))
		return;
	}

	bAttacking = true;

	const char* comboList[] = { "Combo1", "Combo2", "Combo3", "Combo4" };

	//왼쪽 버튼 눌렀을 경우
	//애니메이션이 실행중이지 않았을때
	if (!(AnimInstance->Montage_IsPlaying(AttackMontage)))
	{
		UE_LOG(LogTemp, Warning, TEXT("montage play1"))
		AnimInstance->Montage_Play(AttackMontage);
	}
	//애니메이션이 실행중 일때
	else if (AnimInstance->Montage_IsPlaying(AttackMontage))
	{
		UE_LOG(LogTemp, Warning, TEXT("montage play2"))
		AnimInstance->Montage_Play(AttackMontage);
		AnimInstance->Montage_JumpToSection(FName(comboList[ComboCnt]), AttackMontage);
	}
}

void AMainCharacter::StrongAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("StrongAttack!!()"))

		bStrongAttack = true;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (!AnimInstance || !AttackMontage)
	{
		UE_LOG(LogTemp, Warning, TEXT("Please Check Montage!!"))
			return;
	}
	if (!AnimInstance->Montage_IsPlaying(StrongAttackMontage)&&!AnimInstance->Montage_IsPlaying(AttackMontage))
	{
		AnimInstance->Montage_Play(StrongAttackMontage);
		EndAttacking();
	}
}

void AMainCharacter::EndAttacking()
{
	UE_LOG(LogTemp, Warning, TEXT("EndAttacking()"))
	bAttacking = false;
	bStrongAttack = true;
	ComboCnt = 0;
}

void AMainCharacter::AttackInputChecking()
{
	UE_LOG(LogTemp, Warning, TEXT("AttackInputChecking()"))

		if (ComboCnt >= 3)
		{
			ComboCnt = 0;
		}

		if (bIsAttackNextAttack == true)
		{
			ComboCnt += 1;
			bIsAttackNextAttack = false;
			Attack();
		}

}

void AMainCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}