// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ABCharacterNonPlayer.h"

AABCharacterNonPlayer::AABCharacterNonPlayer()
{
}

void AABCharacterNonPlayer::SetDead()
{
    Super::SetDead();

    // 딜레이 시간 이후 없어지는 기능
    FTimerHandle DeadTimerHandle;
    // 월드로부터 GetTimerManager를 호출해 서비스를 받음
    // SetTimer함수로 호출, 핸들을 지정해주고
    // 딜레이 시간이 지난 이후에 어떤 함수를 실행할 지 함수를 호출할 수 있음
    // 멤버 함수를 선언해서 매핑할 수도 있지만
    // 액터를 없애는 함수를 구현할텐데 이것을 위해 멤버함수를 또 만드는 것은 번거로움
    // 간편하게 만들 수 있는 람다 함수를 즉석에서 만들어 타이머 델리게이트 구조체에 부착시켜 바로 넘길 것.
    // 함수 안에서 바로 구조체 생성, CreateLamda함수로 람다함수를 만들어 바로 호출
    GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda(
        [&]() // 본문 캡처
        {
            Destroy();
        }
        // 위의 본문을 가진 람다 함수와 연결된 타이머 델리게이트를 즉석에서 만들어서 연결
    ), DeadEventDelayTime, false);
}


