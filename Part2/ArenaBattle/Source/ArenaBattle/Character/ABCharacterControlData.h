// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ABCharacterControlData.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABCharacterControlData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UABCharacterControlData();

	// Pawn
	// 캐릭터의 경우 주로 Control Rotation의 Yaw값을 체크함
	// 해당 값을 체크할지 안할지 결정하기 위한 변수
	UPROPERTY(EditAnywhere, Category = Pawn)
	// C++의 비트필드(Bit Field) 문법
	// 크기가 지정되어 있는 타입일지라도 : 구문을 사용해
	// 해당 변수가 차지하는 비트 크기를 지정
	uint32 bUseControllerRotationYaw : 1;

	// Movement
	UPROPERTY(EditAnywhere, Category = CharacterMovement)
	uint32 bOrientRotationToMovement : 1;

	UPROPERTY(EditAnywhere, Category = CharacterMovement)
	uint32 bUseControllerDesiredRotation : 1;

	UPROPERTY(EditAnywhere, Category = CharacterMovement)
	FRotator RotationRate;
	
	// 앞으로 사용할 입력 매핑 컨텍스트
	// 컨트롤 데이터를 선택했을 때 컨트롤 데이터가 가지고 있는 InputMappingContext를 
	// 런타임에서 바꿀 수 있도록 선언.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputMappingContext> InputMappingContext;

	// SpringArm
	UPROPERTY(EditAnywhere, Category = SpringArm)
	float TargetArmLength;

	UPROPERTY(EditAnywhere, Category = SpringArm)
	FRotator RelativeRotation;
	
	UPROPERTY(EditAnywhere, Category = SpringArm)
	uint32 bUsePawnControlRotation : 1;

	UPROPERTY(EditAnywhere, Category = SpringArm)
	uint32 bInheritPitch : 1;

	UPROPERTY(EditAnywhere, Category = SpringArm)
	uint32 bInheritYaw : 1;

	UPROPERTY(EditAnywhere, Category = SpringArm)
	uint32 bInheritRoll : 1;

	UPROPERTY(EditAnywhere, Category = SpringArm)
	uint32 bDoCollisionTest : 1;

};
