// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABStageGimmick.generated.h"

UCLASS()
class ARENABATTLE_API AABStageGimmick : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABStageGimmick();

// Stage Section (스테이지 본체)
protected:
	// 루트 컴포넌트에 해당하는 스테이지를 담을 스태틱 메쉬 컴포넌트 생성
	UPROPERTY(VisibleAnywhere, Category = "Stage", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> Stage;

	// 플레이어가 들어온 것을 감지할 수 있는 스테이지 트리거로 박스 컴포넌트 생성
	UPROPERTY(VisibleAnywhere, Category = "Stage", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBoxComponent> StageTrigger;

	// 플레이어와 스테이지 트리거의 오버랩 이벤트가 발동되었을 때 받아줄 함수
	// 트리거 컴포넌트의 델리게이트에 연결됨, 함수가 복잡하지만 기본 구조는 매번 고정적으로 사용됨
	UFUNCTION()
	void OnStageTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

// Gate Section
protected:
	// 게이트는 4개이기 때문에 맵으로 구성
	// 각 게이트에 동서남북 중 하나의 방향을 키로 전달,
	// 해당하는 문에 대한 스태틱 메쉬를 얻도록 설정
	UPROPERTY(VisibleAnywhere, Category = "Gate", Meta = (AllowPrivateAceess = "true"))
	TMap<FName, TObjectPtr<class UStaticMeshComponent>> Gates;

	// 각 문에 트리거를 배치해 배열로 관리
	UPROPERTY(VisibleAnywhere, Category = "Gate", Meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<class UBoxComponent>> GateTriggers;

	UFUNCTION()
	void OnGateTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
