// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABUserWidget.h"
#include "ABHpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABHpBarWidget : public UABUserWidget
{
	GENERATED_BODY()

public:
	// Widget은 그냥 생성자가 아닌 
	// FObjectInitalizer라는 인자를 가진 생성자만 지원
	UABHpBarWidget(const FObjectInitializer& ObjectInitializer);

protected:
	// 부모(UUserWidget) 클래스에서 제공
	virtual void NativeConstruct() override;

public:
	FORCEINLINE void SetMaxHp(float NewMaxHp) { MaxHp = NewMaxHp; }
	void UpdateHpBar(float NewCurrentHp);

protected:
	// 이대로 쓰면 null값이기 때문에 당연히 동작안함
	// 위젯이 초기화될 때 HpProgressBar를 가져와서 
	// 포인터를 가져오는 기능을 추가해줘야함.
	// 이때 적합한 이벤트가 NativeConstruct()
	UPROPERTY()
	TObjectPtr<class UProgressBar> HpProgressBar;

	UPROPERTY()
	float MaxHp;
};
