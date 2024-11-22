// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ABCharacterPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
// 입력 설정 관련 헤더
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h" // Subsystem's'임


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
    static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/ArenaBattle/Input/IMC_Default.IMC_Default'"));
    if (nullptr != InputMappingContextRef.Object)
    {
        DefaultMappingContext = InputMappingContextRef.Object;
    }

    static ConstructorHelpers::FObjectFinder<UInputAction> InputActionMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ArenaBattle/Input/Actions/IA_Move.IA_Move'"));
    if (InputActionMoveRef.Object)
    {
        MoveAction = InputActionMoveRef.Object;
    }

    static ConstructorHelpers::FObjectFinder<UInputAction> InputActionJumpRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ArenaBattle/Input/Actions/IA_Jump.IA_Jump'"));
    if (InputActionJumpRef.Object)
    {
        JumpAction = InputActionJumpRef.Object;
    }

    static ConstructorHelpers::FObjectFinder<UInputAction> InputActionLookRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ArenaBattle/Input/Actions/IA_Look.IA_Look'"));
    if (InputActionLookRef.Object)
    {
        LookAction = InputActionLookRef.Object;
    }

}

void AABCharacterPlayer::BeginPlay()
{
    Super::BeginPlay();

    // 컨트롤러가 플레이어를 대상으로 설계된 전용 캐릭터 클래스이기 때문에 CastChecked 사용
    APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
    // Subsystem이라는 InputSystem을 가져와서 매핑 컨텍스트 애샛을 추가
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
    {
        // 우선순위를 지정해 입력이 서로 겹칠 때도 우선순위가 높은 입력에 대해
        // 액션들이 바인딩에서 수행할 수 있도록 지정할 수 있음
        Subsystem->AddMappingContext(DefaultMappingContext, 0);

        // 언제든지 자유롭게 RemoveMappingContext를 사용해 런타임에서 빼거나 추가할 수 있다.
        //Subsystem->RemoveMappingContext(DefaultMappingContext);
    }
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
    EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AABCharacterPlayer::Move);
    EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AABCharacterPlayer::Look);
}

// InputActionValue에서 XY값을 가져와 무브먼트 컴포넌트와 연결
// 실질적으로 캐릭터를 이동
void AABCharacterPlayer::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();

    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation(0, Rotation.Yaw, 0);

    const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    AddMovementInput(ForwardDirection, MovementVector.X);
    AddMovementInput(RightDirection, MovementVector.Y);

}

// 컨트롤러의 회전을 설정함으로써 스프링암이 해당 컨트롤러를 바라보도록 설정
void AABCharacterPlayer::Look(const FInputActionValue& Value)
{
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    AddControllerYawInput(LookAxisVector.X);
    AddControllerPitchInput(LookAxisVector.Y);
}
