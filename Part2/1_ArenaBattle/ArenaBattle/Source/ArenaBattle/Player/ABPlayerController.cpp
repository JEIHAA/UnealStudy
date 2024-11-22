// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ABPlayerController.h"

void AABPlayerController::BeginPlay()
{
    // 상속 받았기 때문에 Super로 한번 실행
    Super::BeginPlay();

    // FInputModeGameOnly는 구조체,
    // SetInputMode 함수에 FInputModeGameOnly 구조체를 넘겨주면
    // 시작하자마자 포커스가 뷰 포트 안으로 들어감
    FInputModeGameOnly gameOnlyInputMode;
    SetInputMode(gameOnlyInputMode);
}
