//! One exhaustive mapping from typed statistics to mutable player fields.
use crate::{Engine, KeyColor, Stat, campaign::MAX_STAT};

impl Engine {
    pub(crate) fn key_mut(&mut self, color: KeyColor) -> &mut i64 {
        let keys = &mut self.state.player.keys;
        match color {
            KeyColor::Yellow => &mut keys.yellow,
            KeyColor::Blue => &mut keys.blue,
            KeyColor::Red => &mut keys.red,
        }
    }

    pub(crate) fn stat_value(&self, stat: Stat) -> i64 {
        let p = &self.state.player;
        match stat {
            Stat::Hp => p.hp,
            Stat::Attack => p.attack,
            Stat::Defense => p.defense,
            Stat::Gold => p.gold,
            Stat::Yellow => p.keys.yellow,
            Stat::Blue => p.keys.blue,
            Stat::Red => p.keys.red,
        }
    }

    pub(crate) fn set_stat(&mut self, stat: Stat, amount: i64) {
        let p = &mut self.state.player;
        let value = match stat {
            Stat::Hp => &mut p.hp,
            Stat::Attack => &mut p.attack,
            Stat::Defense => &mut p.defense,
            Stat::Gold => &mut p.gold,
            Stat::Yellow => &mut p.keys.yellow,
            Stat::Blue => &mut p.keys.blue,
            Stat::Red => &mut p.keys.red,
        };
        *value = amount.clamp(0, MAX_STAT);
    }

    pub(crate) fn add_stat(&mut self, stat: Stat, amount: i64) {
        self.set_stat(stat, self.stat_value(stat).saturating_add(amount));
    }
}
