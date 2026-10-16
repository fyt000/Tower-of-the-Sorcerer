#pragma once
#include <utility>

namespace tsw {
// Op::Dialogue uses one-based speech IDs, catalogs use zero-based text indices,
// and the original save records continuation stages at speech ID + 10.
enum class SpeechId : int {
    Unconscious = 1,
    ThiefCallsHero = 2,
    ThiefWakesHero = 3,
    ThiefOpensPrison = 4,
    ThiefFirstDeparture = 5,
    ThiefReturnsToPrison = 6,
    ThiefPromisesToFollow = 7,
    OldManRescueReward = 8,
    MerchantRescueReward = 9,
    ZenoCaptureChallenge = 10,
    HeroCaptured = 11,
    OldManHeroOrb = 12,
    SkeletonLordChallenge = 13,
    SkeletonLordBattle = 14,
    SkeletonLordDefeated = 15,
    FairyFloor10 = 16,
    ThiefSecondDeparture = 17,
    ThiefOctopusTunnel = 18,
    OldManElixir = 19,
    VampireChallenge = 20,
    VampireDefeated = 21,
    FairyFloor20 = 22,
    RockChallenge = 23,
    FairyFloor25 = 24,
    TimeGateInvitation = 25,
    HeroFindsDoll = 26,
    ThiefUnfinishedTunnel = 27,
    ThiefFinishedTunnel = 28,
    ThiefWarnsAboutBoss = 29,
    GreatMagicMasterChallenge = 30,
    GreatMagicMasterRetreat = 31,
    ThiefDragonTunnel = 32,
    ThiefGoldenKnightAdvice = 33,
    GreatMagicMasterFinalChallenge = 34,
    GreatMagicMasterSummonsSoldiers = 35,
    GreatMagicMasterSummonsSwordsmen = 36,
    GreatMagicMasterSummonsKnights = 37,
    GreatMagicMasterBattle = 38,
    GreatMagicMasterDefeated = 39,
    FairyFloor40 = 40,
    GoldenKnightReportsFailure = 41,
    ZenoRebukesGoldenKnight = 42,
    GoldenKnightPleads = 43,
    ZenoPromisesFairFight = 44,
    ZenoFinalChallenge = 45,
    ZenoDefeated = 46,
    FairyFloor49 = 47,
    HeroFindsThief = 48,
    ThiefRevealsDisguise = 49,
    HeroRecognizesZeno = 50,
    ZenoExplainsTest = 51,
    HeroQuestionsTest = 52,
    ZenoExplainsLegend = 53,
    HeroQuestionsLegend = 54,
    ZenoRevealsPlan = 55,
    HeroQuestionsPrincessRumor = 56,
    ZenoOffersAlliance = 57,
    OldManFloor23 = 61,
    BacksideZenoDefeated = 62,
    ThiefTimeGate = 264,
};
enum class DialogueId : int {
    First = 0,
    ThiefFirstEquipmentAdvice = 57,  // Final paragraph of speech 5.
    ThiefSecondEquipmentAdvice = 58, // Final paragraph of speech 17.
    ZenoPlan = 59,                   // Final paragraph of speech 55.
    WisdomHintBase = 62,             // Add the saved wisdom_hints index.
    ZenoDefeated = 61,
    OldManFinished = 86,
    OldManRescueReward = 87,
    OldManHeroOrb = 88,
    OldManElixir = 89,
    NoMoreAdvice = 90,
    MerchantRescueThanks = 91,
    MonsterNameBase = 94,    // Add a monster row index.
    MerchantOfferBase = 246, // Add the merchant table row (0..11).
    StatusOffset = 127,      // Add an Op::Message code.
    YellowKeyFound = 128,
    BlueKeyFound = 129,
    RedKeyFound = 130,
    SecretPassage = 137,
    IronSwordFound = 152,
    SilverSwordFound = 153,
    KnightSwordFound = 154,
    HolySwordFound = 155,
    SacredSwordFound = 156,
    IronShieldFound = 157,
    SilverShieldFound = 158,
    KnightShieldFound = 159,
    HolyShieldFound = 160,
    SacredShieldFound = 161,
    EquipmentPickupBase = IronSwordFound, // Add the sword/shield acquisition index (0..9).
    RedPotionFound = 162,
    BluePotionFound = 163,
    RedGemFound = 164,
    BlueGemFound = 165,
    AltarHitPoints = 181,
    AltarAttack = 182,
    AltarDefense = 183,
    ElixirUsed = 186,
    BombUsed = 188,
    SnowCrystalUsed = 192,
    BattleWon = 199,

    // Fairy evaluation fragments from yousei (0x478F0C). The title is distinct from
    // the numeric leaderboard rank, which appears only when the score places.
    FairyScorePrefix = 220,
    FairyScoreSuffix = 221,
    FairyReconsider = 222,   // Score below 50.
    FairyBelowAverage = 223, // 50..59.
    FairyOrdinary = 224,     // 60..79.
    FairyDoingFine = 225,    // 80..99.
    FairyGreatScore = 226,   // 100..140.
    FairyContinue = 227,     // 141..9999.
    FairyTitlePrefix = 228,
    FairyFighter = 229,      // 100..120.
    FairyBrave = 230,        // 121..140.
    FairyHero = 231,         // 141..160.
    FairySwordEmperor = 232, // 161..200.
    FairyFighterGod = 233,   // 201..9999.
    FairyTitleSuffix = 234,  // Punctuation, or the CJK title clause.
    FairyKeepGoing = 235,    // First three Fairy visits.
    FairyFarewell = 236,     // Fourth and subsequent visits.
    FairyRankPrefix = 244,
    FairyRankSuffix = 245,
    Count = 268,
};
enum class ContinuationStage : int {
    None = 0,
    Altar = 2,
    WakeUpComplete = 13,
    ThiefOpensPrison = 14,
    ThiefFirstDeparture = 15,
    ThiefMovesToFloor35 = 16,
    Capture = 20,
    FairyFloor10 = 26,
    FairyFloor20 = 32,
    FairyFloor25 = 34,
    FairyFloor40 = 50,
    FairyFloor49 = 57,
    LastSaved = 67,
    LastValid = 300
};

constexpr ContinuationStage continuation_for(SpeechId id) {
    return static_cast<ContinuationStage>(std::to_underlying(id) + 10);
}

constexpr DialogueId dialogue_for(SpeechId id) {
    return static_cast<DialogueId>(std::to_underlying(id) - 1);
}

constexpr DialogueId operator+(DialogueId base, int offset) {
    return static_cast<DialogueId>(std::to_underlying(base) + offset);
}

constexpr bool valid_dialogue(DialogueId id) {
    return id >= DialogueId::First && id < DialogueId::Count;
}

constexpr bool is_fairy_speech(SpeechId id) {
    return id == SpeechId::FairyFloor10 || id == SpeechId::FairyFloor20 || id == SpeechId::FairyFloor25 ||
           id == SpeechId::FairyFloor40 || id == SpeechId::FairyFloor49;
}

constexpr bool is_fairy_continuation(ContinuationStage stage) {
    return stage == ContinuationStage::FairyFloor10 || stage == ContinuationStage::FairyFloor20 ||
           stage == ContinuationStage::FairyFloor25 || stage == ContinuationStage::FairyFloor40 ||
           stage == ContinuationStage::FairyFloor49;
}
} // namespace tsw
