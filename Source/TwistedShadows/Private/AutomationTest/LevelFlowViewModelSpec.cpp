// Twisted Shadow make by JSP

#include "Misc/AutomationTest.h"
#include "UI/ViewModel/MVVM_LevelFlow.h"

#if WITH_DEV_AUTOMATION_TESTS

/**
 * Unit tests for UMVVM_LevelFlow. The view model is created with NewObject, no world needed.
 */
BEGIN_DEFINE_SPEC(FTSLevelFlowViewModelSpec, "TwistedShadows.Unit.LevelFlowViewModel",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

	TObjectPtr<UMVVM_LevelFlow> ViewModel;
	int32 TextNotifyCount = 0;
	int32 SecondsNotifyCount = 0;

END_DEFINE_SPEC(FTSLevelFlowViewModelSpec)

void FTSLevelFlowViewModelSpec::Define()
{
	BeforeEach([this]()
	{
		ViewModel = NewObject<UMVVM_LevelFlow>(GetTransientPackage());
		TextNotifyCount = 0;
		SecondsNotifyCount = 0;

		ViewModel->AddFieldValueChangedDelegate(UMVVM_LevelFlow::FFieldNotificationClassDescriptor::LevelTimeText,
			INotifyFieldValueChanged::FFieldValueChangedDelegate::CreateLambda([this](UObject*, UE::FieldNotification::FFieldId)
			{
				++TextNotifyCount;
			}));

		ViewModel->AddFieldValueChangedDelegate(UMVVM_LevelFlow::FFieldNotificationClassDescriptor::LevelTimeInSeconds,
			INotifyFieldValueChanged::FFieldValueChangedDelegate::CreateLambda([this](UObject*, UE::FieldNotification::FFieldId)
			{
				++SecondsNotifyCount;
			}));
	});

	AfterEach([this]()
	{
		ViewModel = nullptr;
	});

	It("SetLevelTimeInSeconds stores the seconds and the formatted text", [this]()
	{
		ViewModel->SetLevelTimeInSeconds(75.f);

		TestEqual(TEXT("Seconds"), ViewModel->GetLevelTimeInSeconds(), 75.f);
		TestEqual(TEXT("Text"), ViewModel->GetLevelTimeText().ToString(), TEXT("01:15"));
	});

	It("notifies both fields once on the first change", [this]()
	{
		ViewModel->SetLevelTimeInSeconds(75.f);

		TestEqual(TEXT("Seconds notifications"), SecondsNotifyCount, 1);
		TestEqual(TEXT("Text notifications"), TextNotifyCount, 1);
	});

	It("does not notify the text again when the displayed second is the same", [this]()
	{
		ViewModel->SetLevelTimeInSeconds(75.f);
		ViewModel->SetLevelTimeInSeconds(75.4f);

		TestEqual(TEXT("Seconds notifications"), SecondsNotifyCount, 2);
		TestEqual(TEXT("Text notifications"), TextNotifyCount, 1);
	});

	It("does not notify anything when the same value is set again", [this]()
	{
		ViewModel->SetLevelTimeInSeconds(75.f);
		ViewModel->SetLevelTimeInSeconds(75.f);

		TestEqual(TEXT("Seconds notifications"), SecondsNotifyCount, 1);
		TestEqual(TEXT("Text notifications"), TextNotifyCount, 1);
	});
}

#endif
