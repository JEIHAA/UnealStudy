// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALMEMORY_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	
	virtual void Init() override;

	virtual void Shutdown() override;

private:

	// UPROPERTY가 아닌 변수와 UPROPERTY 지정한 변수만들기
	TObjectPtr<class UStudent> NonPropStudent;

	UPROPERTY()
	TObjectPtr<class UStudent> PropStudent;

	TArray<TObjectPtr<class UStudent>> NonPropStudents;

	UPROPERTY()
	TArray<TObjectPtr<class UStudent>> PropStudents;


	// 일반 객체이기 때문에 UPROPERTY를 사용할 수 없어서
	// 값이 어떻게 될지 보장할 수 없기 때문에 null로 초기화
	class FStudentManager* StudentManager = nullptr;
};

