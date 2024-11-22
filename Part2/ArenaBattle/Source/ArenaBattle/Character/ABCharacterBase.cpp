// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ABCharacterBase.h"
#include "Components/CapsuleComponent.h"
// Component's'임
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AABCharacterBase::AABCharacterBase()
{
    // Pawn 기본 설정
    // 폰의 회전을 지정하기 위한 값
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // 루트 컴포넌트, 캡슐(Capsule) 설정
    // GetCapsuleComponent를 사용해 가져올 수 있음, 헤더 추가
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
    GetCapsuleComponent()->SetCollisionProfileName(TEXT(""));

    // 움직임(Movement) 설정
    // 점프의 크기, 이동 속도 등
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 700.f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

    // 메쉬(Mesh) 설정
    // 애니메이션 모드와 캐릭터들의 모델링 파일을 진행방향에 맞춰 상대 위치와 회전을 지정해주어야 함.
    GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f));
    GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
    GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh"));

    // 스켈레탈 메쉬 컴포넌트의 실제 애셋 부착
    // ThirdPersonCharacter에서 제공하는 메쉬와 클래스 사용
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Quinn_Simple.SKM_Quinn_Simple'"));
    if (CharacterMeshRef.Object)
    {
        // 스켈레탈에는 메쉬를 가져와서 등록
        GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
    }

    static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/Characters/Mannequins/Animations/ABP_Quinn.ABP_Quinn_C"));
    if (AnimInstanceClassRef.Class)
    {
        // 애니메이션에는 메쉬가 아니라 클래스 등록
        GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
    }


}
