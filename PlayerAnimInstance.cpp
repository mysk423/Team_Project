// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "MainCharacter.h"

void UPlayerAnimInstance::UpdateAnimationProperties(float DeltaTime) {
	if (Wukong == nullptr)
	{
		Wukong = Cast<AMainCharacter>(TryGetPawnOwner());
	}
	if (Wukong)
	{
		FVector Velocity{ Wukong->GetVelocity() };
		Velocity.Z = 0;
		Speed = Velocity.Size();

		bIsInAir = Wukong->GetCharacterMovement()->IsFalling();

		if (Wukong->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f)
		{
			bIsAccelerating = true;
		}
		else
		{
			bIsAccelerating = false;
		}

		FRotator AimRotation = Wukong->GetBaseAimRotation();
		FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(Wukong->GetVelocity());
		MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;
		
		if (Wukong->GetVelocity().Size() > 0.f)
		{
			LastMovementOffsetYaw = MovementOffsetYaw;
		}

		if (UAnimInstance::GetCurveValue(FName("FullBody")) > 0.f)
		{
			FullBody = true;
		}
		else
		{
			FullBody = false;
		}
	}
}

void UPlayerAnimInstance::NativeInitializeAnimation() {
	Wukong = Cast<AMainCharacter>(TryGetPawnOwner());
}