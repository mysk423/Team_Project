// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class TEAM_PROJECT_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter(); 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

<<<<<<< HEAD


=======
>>>>>>> 1dfea83a3c542f7808a4e9ea7411c1c5976de456
protected:
	void Forward(float value);
	void Right(float value);
	void Turn(float value);
	void Lookup(float value);

	void Attack();

	void StrongAttack();

	//Animnotify 호출함수
	UFUNCTION(BlueprintCallable)
		void EndAttacking();

	UFUNCTION(BlueprintCallable)
		void AttackInputChecking();
	
private:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MouseTurnRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MouseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final turn rate */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float BaseLookUpRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = StrongAttack, meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* StrongAttackMontage;

	float CameraDefaultFOV;

	/** Current field of view this frame*/
	float CameraCurrentFOV;

	AController* PlayerController;

	//공격 콤보 구현
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	bool bIsAttackNextAttack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	bool bAttacking;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	bool bLMBDown;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	int ComboCnt;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = StrongAttack, meta = (AllowPrivateAccess = "true"))
		bool bStrongAttack;

public:
	/** Returns CameraBoom subobject */
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject */
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	//왼쪽 마우스 눌렀을때
	void LMBDown();
	FORCEINLINE void LMBUp() { bLMBDown = false; }
	//강 공격 안하는 중...
	FORCEINLINE void NotStrongAttack() { bStrongAttack = false; }
};
