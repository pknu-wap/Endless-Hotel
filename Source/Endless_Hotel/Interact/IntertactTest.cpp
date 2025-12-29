// Copyright by 2025-2 WAP Game 2 team

#include "Interact/IntertactTest.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"          // 삽입해야 하는 헤더1
#include "UI/Base/InGame/Interact/UI_Interact.h" // 삽입해야 하는 헤더2
#include "Component/LookAt/LookAtComponent.h"    // 삽입해야 하는 헤더3

// define으로 선언된 LOCTEXT_NAMESPACE 네임스페이스 지역내에서 에디터가 텍스트를 수집함
#define LOCTEXT_NAMESPACE "TestNameSpace"

#pragma region Base

AInteractTest::AInteractTest(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer)
{
    CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
    SetRootComponent(CubeMesh);

    // 위젯(UI)을 관리하는 컴포넌트
    WC = CreateDefaultSubobject<UWidgetComponent>(TEXT("WC"));
    WC->SetupAttachment(RootComponent);

    // 위젯(UI)의 회전을 담당하는 컴포넌트 -> 플레이어를 바라보게
    LAC = CreateDefaultSubobject<ULookAtComponent>(TEXT("LAC"));
}

void AInteractTest::BeginPlay()
{
    Super::BeginPlay();

/*  위젯 컴포넌트가 생성한 UI 인스턴스를 가져와서 캐싱
    그 후 LOCTEXT 매크로를 통해 수집 대상을 등록하여 에디터에 노출시킴
    LOCTEXT의 파라미터는 키값(네임스페이스 내에서 중복X) + 텍스트값으로 이루어짐 */
    UI_Interact = Cast<UUI_Interact>(WC->GetUserWidgetObject());
    UI_Interact->SetDescription(LOCTEXT("Key1", "쓰레기 값"));

    // 위젯 컴포넌트를 넘겨줘서 회전을 하게 설정
    LAC->SettingWidgetComponent(WC);
}

#pragma endregion

#undef LOCTEXT_NAMESPACE
// 여기까지가 수집 범위

#pragma region Interact

// 실제 상호작용 시 작동해야하는 기능 구현
void AInteractTest::Interacted_Implementation()
{
    RootComponent->AddLocalRotation(FRotator(0, 45, 0));
}

// UI를 노출시키기 위해 필요한 기능 (복붙 ㄱㄱ)
void AInteractTest::ShowInteractWidget_Implementation(bool bIsShow)
{
    UI_Interact->ShowDescription(bIsShow);
}

#pragma endregion