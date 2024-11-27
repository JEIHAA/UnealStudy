// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_AttackHitCheck.h"
//#include "Character/ABCharacterBase.h" 직접 캐릭터 헤더 추가 말고 인터페이스 추가
#include "Interface/ABAnimationAttackInterface.h"

// 인자: 애니메이션을 관리하는 스켈레탈 메쉬 컴포넌트, 애니메이션 정보, 추가적인 레퍼런스 정보
void UAnimNotify_AttackHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
        
    // 인자로 들어온 정보들로부터 액터에 명령을 내려함.
    // 만약 메쉬 컴포넌트가 있다면 메쉬 컴포넌트를 소유하고 있는 오너 가져오기
    if (MeshComp)
    {
        //MeshComp->GetOwner();
        // 해당 Owner가 우리가 선언한 캐릭터인지 체크한 뒤
        // 캐릭터인 경우 공격을 판정하라고 명령을 내릴 수 있음.
        // 이렇게 캐릭터를 바로 사용하는 경우 캐릭터에 대한 헤더를 추가해줘야함.
        // 그런데 Animation 폴더가 아닌 Character 폴더.
        // 다른 폴더의 헤더를 추가하는 것은 의존성이 생긴다는 것을 의미함.
        // 노티파이 기능은 공용으로 여러 종류의 캐릭터가 있을 때 사용되는 것이 좋은데
        // 매번 헤더를 추가하는 것은 끔찍.
        // 좀 더 범용적으로 사용할 수 있게 만들기 위해서 인터페이스를 구현해주는 것이 좋음.

        // 인터페이스를 추가하고 나면
        // Mesh의 Owner가 인터페이스를 구현했는지를 체크해주면 됨
        IABAnimationAttackInterface* AttackPawn = Cast<IABAnimationAttackInterface>(MeshComp->GetOwner());
        if (AttackPawn)
        {
            AttackPawn->AttackHitCheck();
        }
    }
}
