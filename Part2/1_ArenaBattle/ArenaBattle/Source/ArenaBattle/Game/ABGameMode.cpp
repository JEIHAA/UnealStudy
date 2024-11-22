// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/ABGameMode.h"
#include "ABGameMode.h"
//#include "Player/ABPlayerController.h"
// PlayerController 클래스 정보 가져오기
// 애셋으로부터 직접 참조를 받으면 헤더를 추가하지 않아도 됨

AABGameMode::AABGameMode()
{
    // 멤버 변수 값 설정
    // DefaultPawnClass 지정
    // 애셋에 담긴 클래스 정보를 얻어와서 설정해줌
    // 생성자 코드이기 때문에 ConstructorHelpers 함수를 사용해서 애셋 정보를 가져올 수 있음.
    // Pawn 클래스로 상속을 받았기 때문에 APawn으로 찾음
    // 경로 /Script/Engine.Blueprint'/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter' 에서
    // 앞부분과 따옴표는 지우고 애셋 경로만 사용하며,
    // 클래스 정보를 가져올 것이기 때문에 애셋 이름 뒤에 _C를 붙여줌
    static ConstructorHelpers::FClassFinder<APawn> ThirdPersonClassRef(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter_C"));
    if (ThirdPersonClassRef.Class) 
    {
        // 해당 레퍼런트 안에 있는 클래스 정보가 null이 아니라면
        // DefaultPawnClass 값을 ThirdPersonClassRef.Class로 지정
        DefaultPawnClass = ThirdPersonClassRef.Class;
    }

    // PlayerControllerClass에 AABPlayerController 클래스 설정
    // AABPlayerControllerClassRef는 클래스 정보가 바로 복사된 것이기 때문에 _C를 붙이지 않음
    static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/ArenaBattle.ABPlayerController"));
    if (PlayerControllerClassRef.Class)
    {
        PlayerControllerClass = PlayerControllerClassRef.Class;
    }
    //PlayerControllerClass = AABPlayerController::StaticClass();
}
