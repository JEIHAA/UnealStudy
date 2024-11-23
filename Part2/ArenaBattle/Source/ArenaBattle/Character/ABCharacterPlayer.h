// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ABCharacterBase.h"
#include "InputActionValue.h"
// EnhancedInput 모듈 추가해야함
// IntelliSense가 인식하지 못할 경우
// Intermediate와 Binaries폴더를 삭제한 후 프로젝트 재생성
#include "ABCharacterPlayer.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API AABCharacterPlayer : public AABCharacterBase
{
	GENERATED_BODY()
	
public:
	AABCharacterPlayer();

public:
	// 언리얼 엔진의 Input System에서 입력 액션과 우리가 선언한 함수(Move, Look)를 서로 매핑시켜주는 역할
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// 입력 매핑 컨텍스트를 할당하는 역할
	// 입력을 키보드로 받을지, 패드로 받을지에 대해서는 
	// BeginPlay의 DefaultMappingContext를 통해 진행.
	virtual void BeginPlay() override;

// Character Control Section
protected:
	// V를 누르면 컨트롤러를 바꾸는 함수
	void ChangeCharacterControl();
	// 컨트롤러 변경이 발생했을 때 컨트롤에 관련된 모든 설정을 진행해주는 함수
	void SetCharacterControl(ECharacterControlType NewCharacterControlType);

	// CharacterBase에서 상속받은 SetCharacterControlData 오버라이드해서 스프링암 설정
	virtual void SetCharacterControlData(const class UABCharacterControlData* CharacterControlData) override;


// Camera 설정
protected:
	// UPROPERTY()의 Meta 지정자: private으로 선언된 언리얼 오브젝트 객체들을 블루프린트에서도 접근할 수 있게 함
	// 스프링 암. 카메라를 지탱해주는 지지대 역할 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Camera, Meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;
	// 실제 카메라 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Camera, Meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;

// Input 설정
// 기존에 매핑했던 애셋들은 Jump를 제외하고 모두 바뀌었기 때문에 재조정.
protected:
	// 매핑 컨텍스트와 액션에 대한 애셋 지정
	// 다른 애셋으로 변경할 수 있도록 설계하기 위해 EditAnywhere로 설정
	// 1가지 매핑 컨텍스트와 3가지 액션. 3인칭 템플릿에서 제공하고 있는 것들을 사용
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivate = "true"))
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivate = "true"))
	TObjectPtr<class UInputAction> ChangeControlAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivate = "true"))
	TObjectPtr<class UInputAction> ShoulderMoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivate = "true"))
	TObjectPtr<class UInputAction> ShoulderLookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivate = "true"))
	TObjectPtr<class UInputAction> QuaterMoveAction;


	// 각 입력 액션에 대해서 매핑된 함수
	// FInputActionValue 구조체.
	void ShoulderMove(const FInputActionValue& Value);
	void ShoulderLook(const FInputActionValue& Value);

	void QuaterMove(const FInputActionValue& Value);

	// 현재 뷰 상태를 확인하기 위한 변수
	ECharacterControlType CurrentCharacterControlType;
};
