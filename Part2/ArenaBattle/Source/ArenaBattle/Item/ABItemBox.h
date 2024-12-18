// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABItemBox.generated.h"

UCLASS()
class ARENABATTLE_API AABItemBox : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AABItemBox();

protected:
	// 루트 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = Box)
	// 오버랩 이벤트를 사용할 트리거 컴포넌트에는 
	// 이미 오버랩 이벤트를 감지하기 위한 델리게이트가 선언되어있음.
	TObjectPtr<class UBoxComponent> Trigger;
	// 스테틱 메쉬
	UPROPERTY(VisibleAnywhere, Category = Box)
	TObjectPtr<class UStaticMeshComponent> Mesh;
	// 파티클
	UPROPERTY(VisibleAnywhere, Category = Effect)
	TObjectPtr<class UParticleSystemComponent> Effect;
	// 아이템 정보
	UPROPERTY(EditAnywhere, Category="Item")
	// 부모 클래스형을 지정해 어떤 아이템이든 대응
	TObjectPtr<class UABItemData> Item;

	// 트리거 컴포넌트의 델리게이트에 연결될 함수를 액터에 선언.
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32	OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

	UFUNCTION()
	void OnEffectFinished(class UParticleSystemComponent* ParticleSystem);
};