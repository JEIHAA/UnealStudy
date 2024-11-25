// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ABCharacterPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
// 입력 설정 관련 헤더
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h" // Subsystem's'임
#include "ABCharacterControlData.h"


AABCharacterPlayer::AABCharacterPlayer()
{
    // 카메라
    // 뼈대 오브젝트 생성
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    // 루트 컴포넌트에 부착
    CameraBoom->SetupAttachment(RootComponent);
    // 4미터 길이로 설정
    CameraBoom->TargetArmLength = 400.0f;
    // 회전 설정
    CameraBoom->bUsePawnControlRotation = true;

    // 카메라 생성
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    // 스프링 암에 부착
    // 부착할 때 특정 위치를 지정하는 것이 아니라 소켓이라는 특별한 이름 지시자를 지정하면
    // 스프링 암의 끝에 자동으로 붙음
    // F12로 확인해보면 스프링 암의 소켓이름은 SpringEndpoint.
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    // 회전 설정
    FollowCamera->bUsePawnControlRotation = false;

    // Input(입력)
    // 기존에 매핑했던 애셋들은 Jump를 제외하고 모두 바뀌었기 때문에 재조정
    static ConstructorHelpers::FObjectFinder<UInputAction> InputActionJumpRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ArenaBattle/Input/Actions/IA_Jump.IA_Jump'"));
    if (InputActionJumpRef.Object)
    {
        JumpAction = InputActionJumpRef.Object;
    }

    static ConstructorHelpers::FObjectFinder<UInputAction> InputActionChangeControlRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ArenaBattle/Input/Actions/IA_ChangeControl.IA_ChangeControl'"));
    if (InputActionChangeControlRef.Object)
    {
        ChangeControlAction = InputActionChangeControlRef.Object;
    }

    static ConstructorHelpers::FObjectFinder<UInputAction> InputActionShoulderMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ArenaBattle/Input/Actions/IA_ShoulderMove.IA_ShoulderMove'"));
    if (InputActionShoulderMoveRef.Object)
    {
        ShoulderMoveAction = InputActionShoulderMoveRef.Object;
    }

    static ConstructorHelpers::FObjectFinder<UInputAction> InputActionShoulderLookRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ArenaBattle/Input/Actions/IA_ShoulderLook.IA_ShoulderLook'"));
    if (InputActionShoulderLookRef.Object)
    {
        ShoulderLookAction = InputActionShoulderLookRef.Object;
    }

    static ConstructorHelpers::FObjectFinder<UInputAction> InputActionQuaterMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ArenaBattle/Input/Actions/IA_QuaterMove.IA_QuaterMove'"));
    if (InputActionQuaterMoveRef.Object)
    {
        QuaterMoveAction  = InputActionQuaterMoveRef.Object;
    }

    static ConstructorHelpers::FObjectFinder<UInputAction> InputActionAttackRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ArenaBattle/Input/Actions/IA_Attack.IA_Attack'"));
    if (InputActionQuaterMoveRef.Object)
    {
        AttackAction = InputActionAttackRef.Object;
    }

    CurrentCharacterControlType = ECharacterControlType::Quater;


}

void AABCharacterPlayer::BeginPlay()
{
    Super::BeginPlay();

    SetCharacterControl(CurrentCharacterControlType);
}

// V키를 눌러 컨트롤러를 변경하는 함수
void AABCharacterPlayer::ChangeCharacterControl()
{
    if (CurrentCharacterControlType == ECharacterControlType::Quater)
    {
        SetCharacterControl(ECharacterControlType::Shoulder);
    }
    else if (CurrentCharacterControlType == ECharacterControlType::Shoulder)
    {
        SetCharacterControl(ECharacterControlType::Quater);
    }
}


// 컨트롤러가 변경됐을 때 모든 설정을 진행하는 함수
void AABCharacterPlayer::SetCharacterControl(ECharacterControlType NewCharacterControlType)
{
    // 상위 클래스에 선언된 ControlManager에 있는 컨트롤 데이터 애셋 가져오기
    UABCharacterControlData* NewCharacterControl = CharacterControlManager[NewCharacterControlType];
    check(NewCharacterControl);

    // 기본 속성 호출
    SetCharacterControlData(NewCharacterControl);

    // 컨트롤러가 플레이어를 대상으로 설계된 전용 캐릭터 클래스이기 때문에 CastChecked 사용
    APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
    // Subsystem이라는 InputSystem을 가져와서 매핑 컨텍스트 애셋을 추가
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
    {
        // 기존에 있던 모든 Input Mapping Context를 모두 제거
        Subsystem->ClearAllMappings();

        // 새로 ControlManager에서 가져온 데이터 애셋으로 MappingContext를 바꾸기
        UInputMappingContext* NewMappingContext = NewCharacterControl->InputMappingContext;
        if (NewMappingContext)
        {
            // 우선순위를 지정해 입력이 서로 겹칠 때도 우선순위가 높은 입력에 대해
            // 액션들이 바인딩에서 수행할 수 있도록 지정할 수 있음
            Subsystem->AddMappingContext(NewMappingContext, 0);

            // 언제든지 자유롭게 RemoveMappingContext를 사용해 런타임에서 빼거나 추가할 수 있다.
            //Subsystem->RemoveMappingContext(DefaultMappingContext);
        }
    }

    // 모든 변경이 완료되면 현재의 컨트롤 데이터 타입을 변경
    CurrentCharacterControlType = NewCharacterControlType;
}

// 컨트롤 데이터 세팅
void AABCharacterPlayer::SetCharacterControlData(const UABCharacterControlData* CharacterControlData)
{
    Super::SetCharacterControlData(CharacterControlData);

    // SpringArm
    CameraBoom->TargetArmLength = CharacterControlData->TargetArmLength;
    CameraBoom->SetRelativeRotation(CharacterControlData->RelativeRotation);
    CameraBoom->bUsePawnControlRotation = CharacterControlData->bUsePawnControlRotation;
    CameraBoom->bInheritPitch = CharacterControlData->bInheritPitch;
    CameraBoom->bInheritYaw = CharacterControlData->bInheritYaw;
    CameraBoom->bInheritRoll = CharacterControlData->bInheritRoll;
    CameraBoom->bDoCollisionTest = CharacterControlData->bDoCollisionTest;

}


// 입력 설정
void AABCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    // 헤더 추가
    // EnhancedInputComponent를 사용하지 않은 경우 에러를 발생시키도록 CastChecked 함수 사용
    // 반드시 EnhancedInputComponent를 사용하도록 함.
    UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

    // 정상적으로 캐스팅되었다면 함수와 바인딩
    // Move와 Look은 직접 구현, Jump와 StopJumping은 캐릭터가 제공하는 함수와 연결
    EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
    EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
    EnhancedInputComponent->BindAction(ChangeControlAction, ETriggerEvent::Triggered, this, &AABCharacterPlayer::ChangeCharacterControl);
    EnhancedInputComponent->BindAction(ShoulderMoveAction, ETriggerEvent::Triggered, this, &AABCharacterPlayer::ShoulderMove);
    EnhancedInputComponent->BindAction(ShoulderLookAction, ETriggerEvent::Triggered, this, &AABCharacterPlayer::ShoulderLook);
    EnhancedInputComponent->BindAction(QuaterMoveAction, ETriggerEvent::Triggered, this, &AABCharacterPlayer::QuaterMove);
    EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AABCharacterPlayer::Attack);
}

// InputActionValue에서 XY값을 가져와 무브먼트 컴포넌트와 연결
// 실질적으로 캐릭터를 이동
void AABCharacterPlayer::ShoulderMove(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();

    // 업데이트된 컨트롤 로테이션 값을 가져와서
    const FRotator Rotation = Controller->GetControlRotation();

    const FRotator YawRotation(0, Rotation.Yaw, 0);

    // 해당 로테이션을 기점으로 전진 방향(ForwardDirection)과 오른쪽 방향(RightDirection)을 얻어옴
    const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    // 얻은 방향값으로 AddMovementInput 함수를 통해 캐릭터를 이동시킴.
    AddMovementInput(ForwardDirection, MovementVector.X);
    AddMovementInput(RightDirection, MovementVector.Y);

}

// 컨트롤러의 회전을 설정함으로써 스프링암이 해당 컨트롤러를 바라보도록 설정
void AABCharacterPlayer::ShoulderLook(const FInputActionValue& Value)
{
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    // 입력값으로 컨트롤러의 Control Rotation 속성을 업데이트함.
    AddControllerYawInput(LookAxisVector.X);
    AddControllerPitchInput(LookAxisVector.Y);
}

void AABCharacterPlayer::QuaterMove(const FInputActionValue& Value)
{
    // 현재 MovementVector를 받아옴
    FVector2D MovementVector = Value.Get<FVector2D>();

    // 크기가 1이 되도록 조정
    float InputSizeSquared = MovementVector.SquaredLength();
    float MovementVectorSize = 1.0f;
    float MovementVectorSizeSquared = MovementVector.SquaredLength();
    if (MovementVectorSizeSquared > 1.0f)
    {
        MovementVector.Normalize();
        MovementVectorSizeSquared = 1.0f;
    }
    else
    {
        MovementVectorSize = FMath::Sqrt(MovementVectorSizeSquared);
    }

    FVector MoveDirection = FVector(MovementVector.X, MovementVector.Y, 0.0f);
    // ControlRotation을 Forward 방향을 사용해 지정해주면
    // 무브먼트 컴포넌트에서 설정한 옵션에 의해 캐릭터가 자동으로 이동하는 방향을 향해 회전함.
    GetController()->SetControlRotation(FRotationMatrix::MakeFromX(MoveDirection).Rotator());
    AddMovementInput(MoveDirection, MovementVectorSize);



}

void AABCharacterPlayer::Attack()
{   
    ProcessComboCommand();
}


