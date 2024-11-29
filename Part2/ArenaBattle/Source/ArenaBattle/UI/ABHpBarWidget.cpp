// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ABHpBarWidget.h"
#include "Components/ProgressBar.h"
// UMG 모듈에서 제공하는 헤더, UMG는 기본으로 추가되어 있지 않음
// 빌드 설정에서 추가해줘야함. UMG 추가
#include "Interface/ABCharacterWidgetInterface.h"

// 생성자에서 받은 인자는 바로 부모 클래스에 넘겨주면 됨
UABHpBarWidget::UABHpBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    // MaxHp 값이 설정이 안되어있으면 여러 문제가 좀 많음
    // 초기화될 때 반드시 올바른 값으로 지정하도록 해줘야함
    MaxHp = -1.0f;
}

void UABHpBarWidget::NativeConstruct()
{
    // 이 함수가 호출될 때는 
    // UI에 관련된 모든 기능들이 거의 초기화가 완료되었다 보면 됨
    // 이 때 HpProgressBar의 정보를 얻어와서 포인터를 초기화시켜주면 됨
    Super::NativeConstruct();

    // 해당 컨트롤(HpProgressBar)을 이름으로 찾기
    HpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PbHpBar")));
    // 이 포인터는 반드시 있어야하기 때문에 혹시 모르니 검사
    ensure(HpProgressBar);

    // UABUserWidget에서 상속받은 OwningActor
    // 이 액터 정보에 UpdateHpBar 함수 정보를 전달해서
    // 델리게이트에 등록시키면 앞으로 스탯이 업데이트 될 때마다
    // 해당 함수가 호출되면서 HpBar가 변하게 됨.
    // 위젯이 자기를 소유한 액터 정보를 얻었을 때
    // 그 액터 정보로부터 멤버함수를 등록해야하는데
    // 이 때 이를 위해 ABCharacterBase의 클래스 정보를 
    // 직접 참고하면 의존성이 발생함.
    // 이러한 위젯 컴포넌트들은 캐릭터와 무관하게,
    // 다양한 캐릭터에 적용할 수 있게 하는 것이 좋음.
    // 그렇기 때문에 인터페이스 사용.
    IABCharacterWidgetInterface* CharacterWidget = Cast<IABCharacterWidgetInterface>(OwningActor);
    if (CharacterWidget)
    {
        // 캐릭터 위젯에 있는 SetupCharacterWidget에
        // 자기 자신을 넘겨주는 것으로 바인딩 완성
        CharacterWidget->SetupCharacterWidget(this);
    }

}

void UABHpBarWidget::UpdateHpBar(float NewCurrentHp)
{
    // 현재 Hp에 따라 HpBar의 비율을 계산해서 업데이트
    // MaxHp의 상태 확실하게 검사
    ensure(MaxHp > 0.0f);
    if (HpProgressBar)
    {
        HpProgressBar->SetPercent(NewCurrentHp / MaxHp);
    }

}
