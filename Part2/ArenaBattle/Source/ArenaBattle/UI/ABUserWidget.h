// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ABUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// 액터 값 가져오는 함수
	FORCEINLINE void SetOwningActor(AActor* NewOwner) { OwningActor = NewOwner; }

protected:
	// 현재 유저 위젯을 소유하고 있는 액터 정보를 보관할 수 있는 포인터
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actor")
	TObjectPtr<AActor> OwningActor;
};
