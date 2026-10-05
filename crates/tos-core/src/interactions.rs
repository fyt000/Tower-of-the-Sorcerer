//! Conversations and shop transactions consume the compiled campaign script.
use crate::{
    Engine, Stat, TileDef, TileKind,
    events::{Effect, Offer, TriggerKind},
};
use serde_json::{Value, json};

impl Engine {
    fn interaction_def(
        &self,
        floor: i32,
        x: usize,
        y: usize,
        def: &TileDef,
    ) -> crate::content::InteractionView {
        let tile = self
            .tile_at(floor, x, y)
            .expect("validated interaction location");
        self.scripts.interaction_view(floor, x, y, tile, def)
    }

    fn altar_offers(&self, floor: i32) -> Vec<Offer> {
        let visits = self.state.shop_visits.get("altar").copied().unwrap_or(0);
        // Original quadratic pricing: base × (n² + n + 2).
        let cost = self.rules.altar_base_cost.saturating_mul(
            visits
                .saturating_mul(visits)
                .saturating_add(visits)
                .saturating_add(2),
        );
        let area = self.area_multiplier(floor);
        let cycle = self.cycle_multiplier();
        let hp = self
            .rules
            .altar_hp_gain
            .saturating_mul(visits.saturating_add(1))
            .saturating_mul(cycle);
        let attack = self
            .rules
            .altar_attack_gain
            .saturating_mul(area)
            .saturating_mul(cycle);
        let defense = self
            .rules
            .altar_defense_gain
            .saturating_mul(area)
            .saturating_mul(cycle);
        [
            (Stat::Hp, hp),
            (Stat::Attack, attack),
            (Stat::Defense, defense),
        ]
        .into_iter()
        .map(|(stat, amount)| Offer {
            id: Some(stat.to_string()),
            label: format!("+{amount} {stat}"),
            cost,
            cost_increment: 0,
            once: false,
            conditions: vec![],
            effects: vec![Effect::AddStat { stat, amount }.into()],
        })
        .collect()
    }

    pub(crate) fn open_interaction(&mut self, floor: i32, x: usize, y: usize, base: &TileDef) {
        let def = self.interaction_def(floor, x, y, base);
        let tile = self
            .tile_at(floor, x, y)
            .expect("interaction is on a validated map square");
        let key = if def.kind == TileKind::Altar {
            "altar".into()
        } else {
            format!("{floor}:{x}:{y}")
        };
        let visits = self.state.shop_visits.get(&key).copied().unwrap_or(0);
        let offers = if def.kind == TileKind::Altar {
            self.altar_offers(floor)
        } else {
            self.scripts.interaction_script(floor, x, y, tile).1
        };
        let choices: Vec<Value> = offers.iter().enumerate()
            .filter(|(index, offer)| {
                (!offer.once || !self.state.shop_visits.contains_key(&format!("{key}:offer:{}", offer.id_at(*index))))
                    && self.conditions_pass(&offer.conditions)
            }).map(|(index, offer)| {
                let cost = offer.cost_at(visits);
                json!({"id":offer.id_at(index),"label":format!("{} · {} gold",offer.label,cost),"cost":cost})
            }).chain(std::iter::once(json!({"id":"leave","label":"Continue"}))).collect();
        let after_text = def
            .after_text
            .as_ref()
            .filter(|entry| self.state.flags.contains(&entry.flag))
            .map(|entry| entry.text.as_str());
        let text = after_text.unwrap_or(&def.text);
        let dialogue_id = if after_text.is_some() {
            def.dialogue_ids.last()
        } else {
            def.dialogue_ids.first()
        }
        .copied();
        self.record_journal(floor, x, y, &def.name, text, dialogue_id);
        self.state.pending_interaction =
            Some(json!({"title":def.name,"text":text,"choices":choices}));
        self.state.pending_tile = Some((floor, x, y));
    }

    pub(crate) fn choose(&mut self, choice: &str) -> Result<(), String> {
        let Some((floor, x, y)) = self.state.pending_tile else {
            return self.block("There is no conversation to respond to.");
        };
        let id = self
            .tile_at(floor, x, y)
            .ok_or("Interaction location is invalid")?;
        let base = self.campaign.tiles[&id.to_string()].clone();
        let def = self.interaction_def(floor, x, y, &base);
        let (effects, scripted_offers) = self.scripts.interaction_script(floor, x, y, id);
        if choice == "leave" {
            if scripted_offers.is_empty() {
                self.apply_effects(&effects);
                self.run_events(TriggerKind::Interact, floor, x, y, Some(id));
                if def.disappear {
                    self.clear(floor, x, y);
                }
            }
            self.state.pending_interaction = None;
            self.state.pending_tile = None;
            return Ok(());
        }
        let offers = if def.kind == TileKind::Altar {
            self.altar_offers(floor)
        } else {
            scripted_offers
        };
        let Some(offer) = offers
            .into_iter()
            .enumerate()
            .find_map(|(index, offer)| (offer.id_at(index) == choice).then_some(offer))
        else {
            return self.block("Unknown offer");
        };
        let key = if def.kind == TileKind::Altar {
            "altar".into()
        } else {
            format!("{floor}:{x}:{y}")
        };
        let offer_key = format!("{key}:offer:{choice}");
        if offer.once && self.state.shop_visits.contains_key(&offer_key) {
            return self.block("This offer has already been purchased.");
        }
        let visits = self.state.shop_visits.get(&key).copied().unwrap_or(0);
        let cost = offer.cost_at(visits);
        if self.state.player.gold < cost {
            return self.block("You do not have enough gold.");
        }
        if !self.conditions_pass(&offer.conditions) {
            return self.block("You do not meet the requirements for this trade.");
        }
        self.state.player.gold -= cost;
        self.apply_effects(&offer.effects);
        self.state.shop_visits.insert(key, visits.saturating_add(1));
        self.log(format!("{} purchased for {cost} gold.", offer.label));
        if offer.once {
            self.state.shop_visits.insert(offer_key, 1);
        }
        self.open_interaction(floor, x, y, &base);
        Ok(())
    }
}
