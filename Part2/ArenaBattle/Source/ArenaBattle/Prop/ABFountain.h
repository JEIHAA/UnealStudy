// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABFountain.generated.h"

UCLASS()
class ARENABATTLE_API AABFountain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABFountain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 배경 물체 만들기
	// UPROPERTY에 지정자 설정
	// 객체 타입이라 VisibleAnywhere, 블루프린트에서 읽고쓰기 가능하게 BlueprintReadWrite
	// Category = Mesh 언리얼 헤더 툴에 의해 카테고리 분석
	// 자동으로 메쉬에 대한 카테고리에 Body에 대한 값을 편집할 수 있게 UI 제공됨
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr < class UStaticMeshComponent > Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr < class UStaticMeshComponent > Water;

};
