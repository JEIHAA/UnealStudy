#include "UnrealBuildSystem.h"
#include "Modules/ModuleManager.h"

// 모듈의 뼈대를 구축할 클래스
// 주 게임 모듈
// IMPLEMENT_PRIMARY_GAME_MODULE에 모듈을 구현한 클래스를 지정해줘야 하는데
// 언리얼 엔진에서 이미 만들어놓은 게임 클래스가 있음.
// FDefaultGameModuleImpl: 언리얼 엔진이 제공하는 게임 모듈 기본 클래스
// IMPLEMENT_PRIMARY_GAME_MODULE(모듈 클래스, 모듈 이름, 게임 이름)
IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, UnrealBuildSystem, "UnrealBuildSystem");
// 위와 같이 지정해주면 이 모듈은 게임에 관련된 핵심적인 기능을 담당하는 C++ 모듈이 됨.