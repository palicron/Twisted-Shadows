#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"


#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FActivatorTestPresurePlate,
	"TwistedShadows.Activators.PresurePlate",
	EAutomationTestFlags::EditorContext |
	EAutomationTestFlags::ProductFilter
)

bool FActivatorTestPresurePlate::RunTest(const FString& Parameters)
{
    return true;
 }
#endif
