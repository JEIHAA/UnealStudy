// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/ABCharacterStatComponent.h"

// Sets default values for this component's properties
UABCharacterStatComponent::UABCharacterStatComponent()
{
	MaxHp = 200.0f;
	CurrentHp = MaxHp;
}


// Called when the game starts
void UABCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHp(MaxHp);
	
}

float UABCharacterStatComponent::ApplyDamage(float InDamage)
{
	const float PreHp = CurrentHp;
	// 들어온 값이 예측할 수 있는 범위 내에 있도록 Clamp 처리
	const float ActualDamage = FMath::Clamp<float>(InDamage, 0, InDamage);
	SetHp(PreHp-ActualDamage);

	// CurrentHp가 허용되는 아주 작은 값보다도 더 작다면 사실상 죽은 상태
	// KINDA_SMALL_NUMBER: (1.e-4f) ~ (0.00001)
	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		// 죽으면 델리게이트 알림보냄
		OnHpZero.Broadcast();
	}
	return ActualDamage;
}

void UABCharacterStatComponent::SetHp(float NewHp)
{
	CurrentHp = FMath::Clamp<float>(NewHp, 0.0f, NewHp);
	// Hp가 변경됐다면 OnHpChanged라는 델리게이트에 등록한
	// 언리얼 오브젝트나 C++ 함수, 블루프린트 함수에게 
	// 변경되었으니 알아서 처리하라고 신호를 보냄
	OnHpChanged.Broadcast(CurrentHp);
	// MULTI이기 때문에 Broadcast
}

