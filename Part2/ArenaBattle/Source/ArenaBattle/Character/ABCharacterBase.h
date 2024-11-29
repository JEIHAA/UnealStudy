// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/ABAnimationAttackInterface.h"
#include "Interface/ABCharacterWidgetInterface.h"
#include "ABCharacterBase.generated.h"

// 컨트롤 데이터 ENUM
UENUM()
enum class ECharacterControlType : uint8
{
	Shoulder,
	Quater
};

UCLASS()
class ARENABATTLE_API AABCharacterBase : public ACharacter, public IABAnimationAttackInterface, public IABCharacterWidgetInterface
{
	GENERATED_BODY()

public:
	AABCharacterBase();

	// 셋업을 종료하는 시점에서 BegingPlay가 실행되기 전인 
	// Stat의 델리게이트를 등록해서 죽었을 때 죽는 모션을 수행하도록 처리
	// BeginPlay에서 구현할 수도 있고 생성자에서 미리 바인딩할 수도 있는데
	// 알아서 지정. 어디서 바인딩해도 크게 지장없음
	virtual void PostInitializeComponents() override;


protected:
	// 캐릭터 컨트롤 데이터 애셋을 입력으로 받음
	// Pawn과 Movement 데이터 설정
	virtual void SetCharacterControlData(const class UABCharacterControlData* CharacterControlData);

	// 두 가지 애셋 오브젝트를 얻어올 Map
	UPROPERTY(EditAnywhere, Category = "CharacterControl", Meta = (AllowPrivateAccess = "true"))
	TMap<ECharacterControlType, class UABCharacterControlData*> CharacterControlManager;

// Combo Action Anim Section (몽타주)
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UAnimMontage> ComboActionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UABComboActionData> ComboActionData;

	void ProcessComboCommand();

	// 몽타주가 시작될 때 호출
	void ComboActionBegin();
	// 몽타주가 모두 종료됐을 때 호출
	// 몽타주에 설정된 델리게이트를 통해 바로 호출될 수 있도록
	// 파라미터 맞추기
	// 두 가지의 타입으로 되어 있는데,
	// UAnimMotage에 선언되어 있는 델리게이트의 파라미터와 맞춘 것
	// (FOnMontageEnded, class UAnimMontage* bool/*bInterrupted*/)
	void ComboActionEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded);

	// 타이머를 발동시킬 함수
	void SetComboCheckTimer();
	// 타이머가 발동되면 입력이 들어왔는지 안들어왔느지를 체크하는 함수
	void ComboCheck();

	// 현재 콤보가 어디까지 진행됐는지를 저장하기 위한 변수
	// 내부에서만 사용할 것이기 때문에 UPROPERTY는 붙이지 않았음
	// 0 일때는 콤보가 시작되지 않은 것, 1보다 크거나 같으면 콤보가 시작된 것
	int32 CurrentCombo = 0;

	// 언리얼 엔진 월드에서 제공하는 타이머 기능을 이용해서
	// 원하는 시간에 특정 함수를 호출하도록 설정할 수 있는 구조체
	FTimerHandle ComboTimerHandle;
	// 발동한 타이머 이전에 입력 커맨드가 들어왔는지 점검
	// 내부에서만 사용하기 때문에 UPROPERTY를 붙이지 않고,
	// 그렇기 때문에 정수형으로 boolean 값을 쓰지 않아도 됨
	bool HasNextComboCommand = false;


// Attack Hit Section
protected:
	virtual void AttackHitCheck() override;
	// 데미지를 입는 함수. AActor에서 상속받음
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

// Dead Anim Section (몽타주)
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> DeadMontage;

	// 죽는 상태 구현 함수
	virtual void SetDead();
	// 사망 모션 출력 함수
	void PlayerDeadAnimation();

	// 죽은 뒤 일정 시간이 지나고 어떤 이벤트가 발생하도록
	// 시간 딜레이 변수
	float DeadEventDelayTime = 5.0f;

// Stat Section
protected:
	// 언리얼 엔진이 제공하는 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UABCharacterStatComponent> Stat;

// UI Widget Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UABWidgetComponent> HpBar;
	// WidgetComponent가 아닌 ABWidgetComponent로 확장

	// 인터페이스 함수 추가
	virtual void SetupCharacterWidget(class UABUserWidget* InUserWidget) override;
};