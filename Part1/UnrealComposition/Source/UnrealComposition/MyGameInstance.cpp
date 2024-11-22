// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "Person.h"
#include "Student.h"
#include "Teacher.h"
#include "Staff.h"
#include "Card.h"

UMyGameInstance::UMyGameInstance() //생성자
{
	SchoolName = TEXT("기본학교"); //CDO 기본값 설정
}

void UMyGameInstance::Init()
{
	Super::Init(); //원래 로직 실행

	UE_LOG(LogTemp, Log, TEXT("======================================"));
	//UPerson 부모 객체 포인터의 배열
	TArray<UPerson*> Persons = { NewObject<UStudent>(), NewObject<UTeacher>(), NewObject<UStaff>() };

	for (const auto Person : Persons)
	{

		const UCard* OwnCard = Person->GetCard();
		//if (OwnCard) {} 포함 관계이기 때문에 당연히 있음, 코드가 복잡해짐
		check(OwnCard); //if문 대신 check를 써줘도 됨

		ECardType CardType = OwnCard->GetCardType();
		//UE_LOG(LogTemp, Log, TEXT("%s님이 소유한 카드 종류 %d"), *Person->GetName(), CardType);

		//CardType이 가지고 있는 메타 데이터를 가져오기		
		const UEnum* CardEnumType = FindObject<UEnum>(nullptr, TEXT("/Script/UnrealComposition.ECardType")); 
		//두번째 인자 TEXT, TEXT에 들어가는 절대 주소값을 사용해 원하는 타입 정보를 가져올 수 있음
		// /Script(절대 주소값)/모듈이름.타입이름
		//보통 C++에 생성된 언리얼 객체들은 Script라고 하는 절대 주소를 가짐
		//UnrealComposition(프로젝트 이름)이 모듈 이름이 됨

		if (CardEnumType)
		{
			//타입 정보가 있다면 그것을 활용해서 GetDisplayNameTextByValue으로 메타데이터 추출
			//GetDisplayNameTextByValue은 int64만 받음
			FString CardMetaData = CardEnumType->GetDisplayNameTextByValue((int64)CardType).ToString();
			//int64로 형변환해서 넣어줌, FText로 반환됨
			//다국어 지원 문자열이기 때문에 출력할 때 String으로 변환
			UE_LOG(LogTemp, Log, TEXT("%s님이 소유한 카드 종류 %s"), *Person->GetName(), *CardMetaData);
		}
	}

	UE_LOG(LogTemp, Log, TEXT("======================================"));
}