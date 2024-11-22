// Fill out your copyright notice in the Description page of Project Settings.


#include "Person.h"
#include "Card.h"

UPerson::UPerson()
{
    Name = TEXT("홍길동");
    //CDO에서 구현할 때는 CreateDefaultSubobject라는 API를 사용
    //첫번째 인자는 반드시 FName 식별자, 고유한 이름이면 됨
    //일반적인 String이 아니기 때문에 FName인 것을 명시적으로 알리고 싶다면
    //보통 앞에 NAME 접두사를 넣어줌
    Card = CreateDefaultSubobject<UCard>(TEXT("NAME_Card"));
}
