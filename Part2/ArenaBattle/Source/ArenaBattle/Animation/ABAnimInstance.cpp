// Fill out your copyright notice in the Description page of Project Settings.


#include "ABAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UABAnimInstance::UABAnimInstance()
{
    MovingThreshold = 3.0f;
    JumpingThreshold = 100.0f;
}

void UABAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    // 오브젝트에 대한 포인트 값 초기화
    // GetOwningActor는 Actor로 반환되어 캐릭터인지 알 수 없음.
    // 캐릭터로 형 변환
    Owner = Cast<ACharacter>(GetOwningActor());
    if (Owner)
    {
        Movement = Owner->GetCharacterMovement();
    }
}

void UABAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    // NativeInitializeAnimation에서 얻어온
    // Movement 객체로부터 원하는 값 얻기
    if (Movement)
    {
        Velocity = Movement->Velocity;
        // Velocity에서 z제외 x,y값
        GroundSpeed = Velocity.Size2D();
        bIsIdle = GroundSpeed < MovingThreshold;
        bIsFalling = Movement->IsFalling();
        bIsJumping = bIsFalling & (Velocity.Z > JumpingThreshold);
    }
}
