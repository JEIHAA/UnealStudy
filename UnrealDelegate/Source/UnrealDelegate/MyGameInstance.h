// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALDELEGATE_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	public:
	UMyGameInstance(); //생성자로직

	virtual void Init() override;
	
private:

	// 학교는 학사 시스템을 소유하고 있어야함
	// 학사 정보는 언리얼 오브젝트이고 포인터로 관리
	// 포인터로 관리하면 전방 선언을 할 수 있음
	// 언리얼 오브젝트의 포인터를 멤버 변수로 지정할 때는 TObjectPtr 사용
	UPROPERTY()
	TObjectPtr < class UCourseInfo > CourseInfo;

	UPROPERTY()
	FString SchoolName;
};
