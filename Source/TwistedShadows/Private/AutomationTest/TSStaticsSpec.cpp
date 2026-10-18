// Twisted Shadow make by JSP

#include "Misc/AutomationTest.h"
#include "GameplayTagContainer.h"
#include "Definitions/ActivableSystemDefinitions.h"
#include "Functions/TSStatics.h"

#if WITH_DEV_AUTOMATION_TESTS

/**
 * Unit tests for UTSStatics. No world needed.
 *
 * CanBeActivate cases pin the CURRENT behavior so any change to the matching rules is visible.
 * Matching rule today: the settings container must contain the payload tags (parent expansion on the settings side),
 * not the payload containing the settings tags.
 */
BEGIN_DEFINE_SPEC(FTSStaticsSpec, "TwistedShadows.Unit.Statics",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

	FGameplayTag PlateTag;
	FGameplayTag ForwardTag;
	FGameplayTag BackwardTag;

	bool AreTagsValid()
	{
		if (!PlateTag.IsValid() || !ForwardTag.IsValid() || !BackwardTag.IsValid())
		{
			AddError(TEXT("Missing InteractiveActor.Activator.PressurePlate(.Forward/.Backward) in DefaultGameplayTags.ini"));
			return false;
		}
		return true;
	}

	static FActivationSettings MakeSettings(const FGameplayTagContainer& Required, const bool bMatchAll = false,
	                                        const FGameplayTagContainer& Restrict = FGameplayTagContainer(), const bool bMatchAllRestrict = false)
	{
		FActivationSettings Settings{};
		Settings.RequiredTags = Required;
		Settings.RestrictTags = Restrict;
		Settings.bMatchAllTags = bMatchAll;
		Settings.bMatchAllRestrictTags = bMatchAllRestrict;
		return Settings;
	}

	static FGameplayTagContainer Tags(std::initializer_list<FGameplayTag> InTags)
	{
		FGameplayTagContainer Container;
		for (const FGameplayTag& Tag : InTags)
		{
			Container.AddTag(Tag);
		}
		return Container;
	}

END_DEFINE_SPEC(FTSStaticsSpec)

void FTSStaticsSpec::Define()
{
	BeforeEach([this]()
	{
		PlateTag = FGameplayTag::RequestGameplayTag(TEXT("InteractiveActor.Activator.PressurePlate"), false);
		ForwardTag = FGameplayTag::RequestGameplayTag(TEXT("InteractiveActor.Activator.PressurePlate.Forward"), false);
		BackwardTag = FGameplayTag::RequestGameplayTag(TEXT("InteractiveActor.Activator.PressurePlate.Backward"), false);
	});

	Describe("CanBeActivate", [this]()
	{
		It("returns true for an empty payload even when settings are empty", [this]()
		{
			TestTrue(TEXT("Empty settings, empty payload"), UTSStatics::CanBeActivate(MakeSettings({}), FGameplayTagContainer()));
		});

		It("ignores restrict tags when the payload is empty", [this]()
		{
			if (!AreTagsValid()) { return; }
			const FActivationSettings Settings = MakeSettings(Tags({ForwardTag}), false, Tags({ForwardTag}));
			TestTrue(TEXT("Restricted settings, empty payload"), UTSStatics::CanBeActivate(Settings, FGameplayTagContainer()));
		});

		It("returns true when the payload tag equals the required tag", [this]()
		{
			if (!AreTagsValid()) { return; }
			TestTrue(TEXT("Forward vs Forward"), UTSStatics::CanBeActivate(MakeSettings(Tags({ForwardTag})), Tags({ForwardTag})));
		});

		It("returns false when the payload tag is a sibling", [this]()
		{
			if (!AreTagsValid()) { return; }
			TestFalse(TEXT("Forward vs Backward"), UTSStatics::CanBeActivate(MakeSettings(Tags({ForwardTag})), Tags({BackwardTag})));
		});

		It("returns true for a parent payload when settings hold a child tag", [this]()
		{
			if (!AreTagsValid()) { return; }
			TestTrue(TEXT("Settings Forward, payload PressurePlate"), UTSStatics::CanBeActivate(MakeSettings(Tags({ForwardTag})), Tags({PlateTag})));
		});

		It("returns false for a child payload when settings hold the parent tag", [this]()
		{
			if (!AreTagsValid()) { return; }
			TestFalse(TEXT("Settings PressurePlate, payload Forward"), UTSStatics::CanBeActivate(MakeSettings(Tags({PlateTag})), Tags({ForwardTag})));
		});

		It("returns false when settings have no required tags and the payload is not empty", [this]()
		{
			if (!AreTagsValid()) { return; }
			TestFalse(TEXT("Empty settings, payload Forward"), UTSStatics::CanBeActivate(MakeSettings({}), Tags({ForwardTag})));
		});

		It("with bMatchAllTags, activates when settings cover every payload tag", [this]()
		{
			if (!AreTagsValid()) { return; }
			const FActivationSettings Settings = MakeSettings(Tags({ForwardTag, BackwardTag}), true);
			TestTrue(TEXT("Settings {Forward, Backward} match-all, payload {Forward}"), UTSStatics::CanBeActivate(Settings, Tags({ForwardTag})));
		});

		It("with bMatchAllTags, blocks when the payload has a tag the settings lack", [this]()
		{
			if (!AreTagsValid()) { return; }
			const FActivationSettings Settings = MakeSettings(Tags({ForwardTag}), true);
			TestFalse(TEXT("Settings {Forward} match-all, payload {Forward, Backward}"), UTSStatics::CanBeActivate(Settings, Tags({ForwardTag, BackwardTag})));
		});

		It("without bMatchAllTags, activates when any payload tag matches", [this]()
		{
			if (!AreTagsValid()) { return; }
			const FActivationSettings Settings = MakeSettings(Tags({ForwardTag}), false);
			TestTrue(TEXT("Settings {Forward} match-any, payload {Forward, Backward}"), UTSStatics::CanBeActivate(Settings, Tags({ForwardTag, BackwardTag})));
		});

		It("restrict tags win over required tags", [this]()
		{
			if (!AreTagsValid()) { return; }
			const FActivationSettings Settings = MakeSettings(Tags({ForwardTag}), false, Tags({ForwardTag}));
			TestFalse(TEXT("Required and restricted Forward"), UTSStatics::CanBeActivate(Settings, Tags({ForwardTag})));
		});

		It("restrict match-any blocks when one payload tag is restricted", [this]()
		{
			if (!AreTagsValid()) { return; }
			const FActivationSettings Settings = MakeSettings(Tags({ForwardTag}), false, Tags({BackwardTag}), false);
			TestFalse(TEXT("Restrict {Backward}, payload {Forward, Backward}"), UTSStatics::CanBeActivate(Settings, Tags({ForwardTag, BackwardTag})));
		});

		It("restrict match-all does not block when the payload has extra tags", [this]()
		{
			if (!AreTagsValid()) { return; }
			const FActivationSettings Settings = MakeSettings(Tags({ForwardTag}), false, Tags({BackwardTag}), true);
			TestTrue(TEXT("Restrict {Backward} match-all, payload {Forward, Backward}"), UTSStatics::CanBeActivate(Settings, Tags({ForwardTag, BackwardTag})));
		});
	});

	Describe("GetLevelTimeInTextFormat", [this]()
	{
		It("formats whole and fractional seconds as MM:SS", [this]()
		{
			TestEqual(TEXT("0"), UTSStatics::GetLevelTimeInTextFormat(0.f).ToString(), TEXT("00:00"));
			TestEqual(TEXT("59.9"), UTSStatics::GetLevelTimeInTextFormat(59.9f).ToString(), TEXT("00:59"));
			TestEqual(TEXT("60"), UTSStatics::GetLevelTimeInTextFormat(60.f).ToString(), TEXT("01:00"));
			TestEqual(TEXT("61.5"), UTSStatics::GetLevelTimeInTextFormat(61.5f).ToString(), TEXT("01:01"));
			TestEqual(TEXT("3599"), UTSStatics::GetLevelTimeInTextFormat(3599.f).ToString(), TEXT("59:59"));
		});

		It("keeps counting minutes past one hour", [this]()
		{
			TestEqual(TEXT("3600"), UTSStatics::GetLevelTimeInTextFormat(3600.f).ToString(), TEXT("60:00"));
			TestEqual(TEXT("6000"), UTSStatics::GetLevelTimeInTextFormat(6000.f).ToString(), TEXT("100:00"));
		});

		It("does not clamp negative input (current behavior)", [this]()
		{
			TestEqual(TEXT("-1"), UTSStatics::GetLevelTimeInTextFormat(-1.f).ToString(), TEXT("-1:-1"));
		});
	});

	Describe("Null world context", [this]()
	{
		It("GetLevelFlowViewModel returns nullptr", [this]()
		{
			TestNull(TEXT("ViewModel"), UTSStatics::GetLevelFlowViewModel(nullptr));
		});

		It("GetCurrentLevelProgress returns a default progress", [this]()
		{
			const FLevelProgress Progress = UTSStatics::GetCurrentLevelProgress(nullptr);
			TestEqual(TEXT("LevelID"), Progress.LevelID, 0);
			TestFalse(TEXT("bIsAlreadyFinish"), static_cast<bool>(Progress.bIsAlreadyFinish));
		});
	});
}

#endif
