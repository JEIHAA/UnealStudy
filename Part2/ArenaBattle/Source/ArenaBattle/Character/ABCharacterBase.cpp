// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ABCharacterBase.h"
#include "Components/CapsuleComponent.h"
// Component's'임
#include "ABCharacterControlData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimMontage.h"
#include "ABComboActionData.h"

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
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard'"));
    if (CharacterMeshRef.Object)
    {
        // 스켈레탈에는 메쉬를 가져와서 등록
        GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
    }

    static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/ArenaBattle/Animation/ABP_ABCharacter.ABP_ABCharacter_C"));
    if (AnimInstanceClassRef.Class)
    {
        // 애니메이션에는 메쉬가 아니라 클래스 등록
        GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
    }

    // CharacterControlManager(Map)에 두 가지 컨트롤 데이터 추가
    static ConstructorHelpers::FObjectFinder<UABCharacterControlData> ShoulderDataRef(TEXT("/Script/ArenaBattle.ABCharacterControlData'/Game/ArenaBattle/CharacterControl/ABC_Shoulder.ABC_Shoulder'"));
    if (ShoulderDataRef.Object)
    {
        CharacterControlManager.Add(ECharacterControlType::Shoulder, ShoulderDataRef.Object);
    }

    static ConstructorHelpers::FObjectFinder<UABCharacterControlData> QuaterDataRef(TEXT("/Script/ArenaBattle.ABCharacterControlData'/Game/ArenaBattle/CharacterControl/ABC_Quarter.ABC_Quarter'"));
    if (QuaterDataRef.Object)
    {
        CharacterControlManager.Add(ECharacterControlType::Quater, QuaterDataRef.Object);
    }

}

// 컨트롤 데이터 세팅
void AABCharacterBase::SetCharacterControlData(const UABCharacterControlData* CharacterControlData)
{
    
    // Pawn
    bUseControllerRotationYaw = CharacterControlData->bUseControllerRotationYaw;

    // CharacterMovement
    GetCharacterMovement()->bOrientRotationToMovement = CharacterControlData->bOrientRotationToMovement;
    GetCharacterMovement()->bUseControllerDesiredRotation = CharacterControlData->bUseControllerDesiredRotation;
    GetCharacterMovement()->RotationRate = CharacterControlData->RotationRate;
}

void AABCharacterBase::ProcessComboCommand()
{
    // 콤보가 시작되지 않았다면
    if (CurrentCombo == 0)
    {
        // 콤보가 시작되고 리턴
        ComboActionBegin();
        return;
    }

    // 만약 타이머가 설정되어 있지 않을 때 입력이 들어온다면
    // (이미 타이머가 발동되어 시기를 놓쳤거나 더 이상 진행할 필요가 없다면)
    if (!ComboTimerHandle.IsValid())
    {
        HasNextComboCommand = false;
    }
    // 만약 타이머가 유효하다면
    // 체크하기 전에 다음 섹션으로 이동시킬 커맨드가 발동했다는 뜻
    else
    {
        HasNextComboCommand = true;
    }
}

void AABCharacterBase::ComboActionBegin()
{
    // Combo Status
    CurrentCombo = 1;

    // Movement Setting
    // MovementMode::MOVE_None - 이동기능이 없어짐
    // 온전하게 콤보 기능
    GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

    // Animation Setting
    // 재생 속도 지정
    const float AttackSpeedRate = 1.0f;

    // 몽타주를 재생하기 위해서는 AnimInstance의 포인터를 가져와야함.
    UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
    // Montage_Play()에 몽타주 애셋을 지정해서 특정한 몽타주를 재생하도록 설정할 수 있음.
    AnimInstance->Montage_Play(ComboActionMontage, AttackSpeedRate);

    // 몽타주가 시작되자마자 몽타주가 종료될 때 ComboActionEnd함수가 호출되도록 함
    // 구조체처럼 선언하고 그 안에 관련된 함수 정보를 넣음
    FOnMontageEnded EndDelegate;
    // 구조체에 바인딩할 정보 추가
    // 현재 인스턴스의 ComboActionEnd 맵핑
    EndDelegate.BindUObject(this, &AABCharacterBase::ComboActionEnd);
    // 첫번째 인자에 바인드까지 시킨 구조체를 연결
    // 두번째 인자에 몽타주 지정
    AnimInstance->Montage_SetEndDelegate(EndDelegate, ComboActionMontage);

    // 콤보가 시작될 때 타이머 발동
    // 타이머를 초기화해준 뒤
    ComboTimerHandle.Invalidate();
    SetComboCheckTimer();

}

void AABCharacterBase::ComboActionEnd(UAnimMontage* TargetMontage, bool IsProperlyEnded)
{
    // 콤보가 종료될 때 CurrentCombo는 절대 0이 될 수 없음
    // Assertion함수를 사용해서 검증
    ensure(CurrentCombo != 0);
    CurrentCombo = 0;
    // 캐릭터 무브먼트 값 복원
    GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void AABCharacterBase::SetComboCheckTimer()
{
    // 배열에 선언되어있는 타이머 정보를, 프레임 정보를 얻기 위한 인덱스
    int32 ComboIndex = CurrentCombo - 1;
    // 애셋 액션에 설정되어 있는 각 프레임 정보(인덱스)가 유효한지 검사
    ensure(ComboActionData->EffectiveFrameCount.IsValidIndex(ComboIndex));

    const float AttackSpeedRate = 1.0f;
    // 정상속도로 진행했을 때 소요될 시간 계산
    // ComboActionData에 설정된 값을 가져와서 ComboActionData에 설정된 FrameRate로 나눈 뒤, 그 값을 AttackSpeed로 나눔
    // 발동할 시간을 알 수 있게 됨
    float ComboEffectiveTime = (ComboActionData->EffectiveFrameCount[ComboIndex] / ComboActionData->FrameRate) / AttackSpeedRate;
    if (ComboEffectiveTime > 0.0f)
    {
        // 월드로부터 시간 서비스 받기
        // SetTimer(타이머핸들, 현재 클래스, ComboCheck함수, 시간, 반복X)
        GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &AABCharacterBase::ComboCheck, ComboEffectiveTime, false);
    }
}

void AABCharacterBase::ComboCheck()
{
    // 타이머가 발동되면 타이머 핸들 초기화
    ComboTimerHandle.Invalidate();
    // 타이머 발동 전에 들어온 ComboCommand가 있다면
    if (HasNextComboCommand)
    {
        // 몽타주의 다음 섹션으로 넘기기
        UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

        // MaxComboCount를 벗어나지 않도록 Clamp 걸기
        CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, ComboActionData->MaxComboCount);

        // 다음 섹션에 대한 이름 정보 가져오기
        // String을 조합하기 때문에 Printf 사용
        // 에셋에 선언한 MontageSectionNameProfix(접두사)정보와 콤보값을 조합해서 
        // 네임으로 변환, 섹션이름으로 지정
        FName NextSection = *FString::Printf(TEXT("%s%d"), *ComboActionData->MontageSectionNameProfix, CurrentCombo);
        // Montage_JumpToSection 해당 이름 섹션으로 바로 점프해서 재생
        AnimInstance->Montage_JumpToSection(NextSection, ComboActionMontage);

        // 바로 타이머 다시 걸기
        SetComboCheckTimer();
        HasNextComboCommand = false;

    }
}
