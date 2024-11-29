// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ABComboActionData.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABComboActionData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UABComboActionData();

	UPROPERTY(EditAnywhere, Category = "Name")
	FString MontageSectionNameProfix;

	UPROPERTY(EditAnywhere, Category = "Name")
	uint32 MaxComboCount;

	// 프레임의 기준 재생 속도를 지정해
	// 정확한 타이밍에 체크가 발생하도록 설정
	UPROPERTY(EditAnywhere, Category = "Name")
	float FrameRate;

	// 입력이 사전에 입력됐는지를 감지하는 프레임 지정
	UPROPERTY(EditAnywhere, Category = "Name")
	TArray<float> EffectiveFrameCount;

};
