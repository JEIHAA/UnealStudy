// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ABAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UABAnimInstance();

protected:
	// 주요 이벤트 함수
	// AnimInstance가 처음 생성될 때 한번 호출
	virtual void NativeInitializeAnimation() override;
	// 프레임마다 호출
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	// AnimGraph가 참조할 변수

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	TObjectPtr<class ACharacter> Owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	TObjectPtr<class UCharacterMovementComponent> Movement;

	// 현재 캐릭터 속도
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	FVector Velocity;

	// 땅 위에서의 이동속도
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	float GroundSpeed;

	// Idle 상태인지 판단
	// bool 타입은 사이즈가 어떻게 될지 명확하지 않음
	// 명확한 사이즈를 위해 정수형으로 선언
	// 접두사 b 붙이고 비트 플래그 추가
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	uint32 bIsIdle : 1;

	// 움직이고 있는지 쉬고 있는지 나타냄
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	float MovingThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	uint32 bIsFalling : 1;

	// 점프하고 있는지 판단
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	uint32 bIsJumping : 1;

	// 현재 점프 중인지 나타냄
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	float JumpingThreshold;
};
