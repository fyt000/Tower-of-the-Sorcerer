//! Original mechanics and remake presentation defaults. Campaign rules override
//! the configurable values; import/save bounds live in their own modules.

/// The second tower multiplies monster stats and stat pickups by 44.
pub(crate) const BACKSIDE_MULTIPLIER: i64 = 44;
/// Potion/gem/shop scaling advances once per ten-floor region.
pub(crate) const FLOORS_PER_AREA: i32 = 10;
/// Elixir grants attack × 10 + defense × 5 HP, rather than a fixed heal.
pub(crate) const ELIXIR_ATTACK_FACTOR: i64 = 10;
pub(crate) const ELIXIR_DEFENSE_FACTOR: i64 = 5;
pub(crate) const WARP_STAFF_CHARGES: u32 = 3;
/// Source tile ID distinguishes ordinary brick from decorative wall variants.
pub(crate) const BRICK_WALL_TILE: u16 = 8;
/// Only these original monster families can be removed by the bomb.
pub(crate) const BOMB_TILE_RANGES: [(u16, u16); 4] = [(61, 90), (93, 96), (133, 144), (147, 158)];

/// Original combat uses three 150 ms phases at High speed (sound, overlay,
/// damage). The remake defaults to that 450 ms strike; campaigns can tune it.
pub(crate) const COMBAT_STRIKE_MS: u64 = 450;
/// Renderer fallback for the spiral wipe; the recovered cell order is exact,
/// while this portable wall-clock duration is a tunable approximation.
pub(crate) const FLOOR_TRANSITION_MS: u64 = 450;
/// Visual travel interpolation only; headless movement has no elapsed time.
pub(crate) const WALK_STEP_MS: u64 = 110;
pub(crate) const CROSS_MULTIPLIER: i64 = 2;
pub(crate) const DRAGON_SLAYER_MULTIPLIER: i64 = 2;
pub(crate) const MAGICIAN_A_DAMAGE: i64 = 200;
pub(crate) const MAGICIAN_B_DAMAGE: i64 = 100;

/// Altar price is base × (visits² + visits + 2); rewards scale by area/cycle.
pub(crate) const ALTAR_BASE_COST: i64 = 10;
pub(crate) const ALTAR_HP_GAIN: i64 = 100;
pub(crate) const ALTAR_ATTACK_GAIN: i64 = 2;
pub(crate) const ALTAR_DEFENSE_GAIN: i64 = 4;
