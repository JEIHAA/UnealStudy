// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ABItemBox.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Physics/ABCollision.h"
#include "Interface/ABCharacterItemInterface.h"

// Sets default values
AABItemBox::AABItemBox()
{
	// 각 포인터에 대한 객체 생성
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Effect"));

	// 액터 내부에 Scene 셋업
	RootComponent = Trigger;
	Mesh->SetupAttachment(Trigger);
	Effect->SetupAttachment(Trigger);

	// 트리거 설정
	// 설정해둔 콜리전 프로필 사용
	Trigger->SetCollisionProfileName(CPROFILE_ABTRIGGER);

	// 델리게이트 연결
	// 박스 컴포넌트에 델리게이트가 있으니 일단 사이즈 지정
	Trigger->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f));
	// 다이나믹 델리게이트이기 때문에 AddDynamic함수 사용
	// AddDymanic(this(현재 객체에 대해),&AABItemBox::OnOverlapBegin(AABItemBox클래스의 OnOverlapBegin함수를 바인딩))
	// 인텔리센스가 잘 동작하지 않을 수 있음. 그래도 그냥 진행
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AABItemBox::OnOverlapBegin);

	// 메쉬 컴포넌트 설정
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/ArenaBattle/Environment/Props/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1'"));
	if (BoxMeshRef.Object)
	{
		Mesh->SetStaticMesh(BoxMeshRef.Object);
	}
	// 위치 조절
	Mesh->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));
	// 충돌 사용 안함
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));

	// 파티클 설정
	static ConstructorHelpers::FObjectFinder<UParticleSystem> EffectRef(TEXT("/Script/Engine.ParticleSystem'/Game/ArenaBattle/Effect/P_TreasureChest_Open_Mesh.P_TreasureChest_Open_Mesh'"));
	if (EffectRef.Object)
	{
		// SetTemplate 함수로 이펙트 지정
		Effect->SetTemplate(EffectRef.Object);
		// 처음에 바로 발동하지 않도록 bAutoActivate 설정 끄기
		Effect->bAutoActivate = false;
	}
}

// 트리거가 발동하면 호출됨
void AABItemBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	// 상자를 열었는데 꽝일 경우
	if (nullptr == Item)
	{
		// 이펙트 없이 제거됨
		Destroy();
		return;
	}

	IABCharacterItemInterface* OverlappingPawn = Cast<IABCharacterItemInterface>(OtherActor);
	if (OverlappingPawn) 
	{
		// 상자에 아이템이 있었다면 닿은 캐릭터에게 인자로 넘겨줌
		OverlappingPawn->TakeItem(Item);
	}

	// 이펙트 재생
	Effect->Activate(true);
	// 메쉬 숨기기
	Mesh->SetHiddenInGame(true);
	// 액터에 대한 콜리전 모두 끄기
	SetActorEnableCollision(false);

	// 발동된 이벤트가 종료될 때,
	// 이펙트가 종료될 때 발동되는 델리게이트가 또 있음
	// 마찬가지로 AddDynamic으로 설정
	// Dynamic이기 때문에 헤더에서 연결할 UFUNCTION 함수 선언해줘야함
	Effect->OnSystemFinished.AddDynamic(this, &AABItemBox::OnEffectFinished);
}

void AABItemBox::OnEffectFinished(UParticleSystemComponent* ParticleSystem)
{
	// 액터가 스스로 없어지도록 설정
	Destroy();
}