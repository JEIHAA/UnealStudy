// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ABWidgetComponent.h"
#include "ABUserWidget.h"

void UABWidgetComponent::InitWidget()
{
    Super::InitWidget();
    // InitWidget이 호출될 때는 위젯에 대한 인스턴스가 생성된 직후.
    // 위젯에 관련된 UI 요소들이 모두 다 준비되면 NativeConstruct함수가 호출됨.
    // 위젯에 대한 인스턴스가 생성됐을 때, 관련된 액터 정보를 얻어서
    // 위젯의 OwningActor에 넣음

    // InitWidget 함수가 호출되면
    // 내부의 CreateWidget이라는 함수가 내부적으로 호출되면서 그 때 인스턴스가 만들어짐
    // 즉, Super 이후에 InitWidget가 실행되면서 
    // 위젯에 대한 인스턴스가 생성되었기 때문에 객체가 존재하는 상태라 볼 수 있음.
    UABUserWidget* ABUserWidget = Cast<UABUserWidget>(GetWidget()); 
    if (ABUserWidget)
    {
        // SetOwningActor 정보를 가져오되, 컴포넌트 정보이기 때문에
        // GetOwner함수를 사용해 자신을 소유하고 있는 액터 정보를 얻어올 수 있음.
        ABUserWidget->SetOwningActor(GetOwner());

        // 이렇게 값을 넘겨주면 ABUserWidget에서는 해당 값을 OwningActor에 집어 넣을 수 있게 되고
        // 이후에 진행되는 초기화 단계, ABHpBarWidget의 NativeConstruct에서는
        // ABUserWidget을 상속받게 되면 거기에 있는 OwningActor 값을 사용할 수 있게 됨.
        // 따라서 HpBarWidget의 부모 클래스를 UUserWidget에서 
        // UABUserWidget을 상속받도록 변경하고 헤더 추가.
    }

}
