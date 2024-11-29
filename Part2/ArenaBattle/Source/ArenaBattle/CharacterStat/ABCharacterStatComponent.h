// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ABCharacterStatComponent.generated.h"

// 스탯 컴포넌트가 델리게이트를 만들고 구독을 등록한 다른 객체에게
// Hp가 변경됐을 때 적합한 행동을 처리하도록 구조 설계
DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate);
// 매크로를 사용해 각 구조체 선언
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChangedDelegate, float /*CurrentHp*/);
// 하나의 인자만 받음 변경된 Hp값을 구독한 객체들에게 보냄

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARENABATTLE_API UABCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UABCharacterStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// 델리게이트 선언
	// 델리게이트로 선언한 구조체 가져다 쓰면 됨
	FOnHpZeroDelegate OnHpZero;
	FOnHpChangedDelegate OnHpChanged;

	FORCEINLINE float GetMaxHp() { return MaxHp; }
	FORCEINLINE float GetCurrentHp() { return CurrentHp; }
	float ApplyDamage(float InDamage);

// Tick을 호출하지 않고 최대한 부하를 줄이도록 구현
protected:
	// Hp가 변경되려면 바로 대입하는 것이 아닌
	// 반드시 이 함수를 호출하도록 설정
	void SetHp(float NewHp);

	// 체력 값은 값들은 기본 값이긴하지만
	// 배치한 캐릭터마다 서로 다른 값을 가지고 있기 때문에
	// VisibleInstanceOnly를 사용해주면 캐릭터마다 다른 값을 설정할 수 있음
	UPROPERTY(VisibleInstanceOnly, Category = "Stat")
	float MaxHp;
		
	// 스탯 컴포넌트라는 오브젝트를 저장할 때
	// 이러한 속성들이 모두 디스크에 저장됨.
	// 현재 Hp같은 경우 게임을 할 때마다
	// 새롭게 지정되기 때문에 디스크에 저장할 필요가 없을 수도 있음
	// 디스크에 저장할 필요가 없다면 Transient 키워드를 추가해 
	// 디스크에 저장할 때 공간을 아낄 수 있음.
	UPROPERTY(VisibleInstanceOnly, Category = "Stat")
	float CurrentHp;
};
