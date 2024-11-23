// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ABCharacterBase.generated.h"

// 컨트롤 데이터 ENUM
UENUM()
enum class ECharacterControlType : uint8
{
	Shoulder,
	Quater
};

UCLASS()
class ARENABATTLE_API AABCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AABCharacterBase();

protected:
	// 캐릭터 컨트롤 데이터 애셋을 입력으로 받음
	// Pawn과 Movement 데이터 설정
	virtual void SetCharacterControlData(const class UABCharacterControlData* CharacterControlData);

	// 두 가지 애셋 오브젝트를 얻어올 Map
	UPROPERTY(EditAnywhere, Category = CharacterControl, Meta = (AllowPrivateAccess = "true"))
	TMap<ECharacterControlType, class UABCharacterControlData*> CharacterControlManager;

};