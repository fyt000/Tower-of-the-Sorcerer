//! Data-driven labels and original dialogue, with safe English custom-content fallback.
use serde_json::Value;
use std::sync::OnceLock;

fn english() -> &'static Value {
    static VALUE: OnceLock<Value> = OnceLock::new();
    VALUE.get_or_init(|| {
        serde_json::from_str(include_str!("../../../data/locales/en.json"))
            .expect("bundled English locale is valid JSON")
    })
}
fn chinese() -> &'static Value {
    static VALUE: OnceLock<Value> = OnceLock::new();
    VALUE.get_or_init(|| {
        serde_json::from_str(include_str!("../../../data/locales/zh-CN.json"))
            .expect("bundled Chinese locale is valid JSON")
    })
}
fn bundle(locale: &str) -> &'static Value {
    if locale.to_lowercase().starts_with("zh") {
        chinese()
    } else {
        english()
    }
}

pub fn tr(locale: &str, key: &str) -> String {
    bundle(locale)["ui"][key]
        .as_str()
        .or_else(|| english()["ui"][key].as_str())
        .unwrap_or(key)
        .to_owned()
}

/// Localize known original definitions only. A custom entity whose canonical
/// English name was changed keeps its own name, even if its numeric ID overlaps.
pub fn entity_name(locale: &str, category: &str, id: &str, fallback: &str) -> String {
    let category = match category {
        "items" => "item",
        "tiles" => "tile",
        "enemies" => "enemy",
        other => other,
    };
    let baseline = english()["entities"][category][id].as_str();
    let known = baseline.is_some_and(|name| {
        name.eq_ignore_ascii_case(fallback) || fallback.is_empty() || fallback == id
    });
    if known {
        bundle(locale)["entities"][category][id]
            .as_str()
            .or(baseline)
            .unwrap_or(fallback)
            .to_owned()
    } else {
        fallback.to_owned()
    }
}

pub fn dialogue(locale: &str, id: usize) -> String {
    let key = id.to_string();
    bundle(locale)["dialogue"][&key]
        .as_str()
        .or_else(|| english()["dialogue"][&key].as_str())
        .unwrap_or("")
        .to_owned()
}

/// Original event messages may concatenate two dialogue strings. Match the
/// exact message first, then replace complete original clauses longest first.
/// Unknown custom narrative is kept as authored.
pub fn translate_text(locale: &str, text: &str) -> String {
    if !locale.to_lowercase().starts_with("zh") {
        return text.to_owned();
    }
    if let Some(translated) = chinese()["text"][text].as_str() {
        return translated.to_owned();
    }
    if let Some(labels) = english()["ui"].as_object()
        && let Some((key, _)) = labels
            .iter()
            .find(|(_, value)| value.as_str() == Some(text))
    {
        return tr(locale, key);
    }
    if let Some(entries) = english()["dialogue"].as_object()
        && let Some((id, _)) = entries
            .iter()
            .find(|(_, value)| value.as_str() == Some(text))
        && let Some(value) = chinese()["dialogue"][id].as_str()
    {
        return value.to_owned();
    }
    let mut matches: Vec<(&str, &str)> = english()["dialogue"]
        .as_object()
        .into_iter()
        .flat_map(|entries| entries.iter())
        .filter_map(|(id, value)| Some((value.as_str()?, chinese()["dialogue"][id].as_str()?)))
        .filter(|(source, _)| {
            source.len() >= 20 && source.contains(['.', '!', '?']) && text.contains(source)
        })
        .collect();
    matches.sort_by_key(|(source, _)| std::cmp::Reverse(source.len()));
    let mut translated = text.to_owned();
    for (source, target) in matches {
        translated = translated.replace(source, target);
    }
    if let Some(patterns) = chinese()["patterns"].as_array() {
        for pattern in patterns {
            if let (Some(source), Some(target)) =
                (pattern["source"].as_str(), pattern["translation"].as_str())
            {
                if let Some(captures) = match_template(source, text) {
                    let mut output = target.to_owned();
                    for (name, value) in captures {
                        output =
                            output.replace(&format!("{{{name}}}"), &translate_names(locale, value));
                    }
                    return output;
                }
                continue;
            }
            let prefix = pattern["prefix"].as_str().unwrap_or("");
            let suffix = pattern["suffix"].as_str().unwrap_or("");
            if let Some(body) = text
                .strip_prefix(prefix)
                .and_then(|body| body.strip_suffix(suffix))
            {
                return format!(
                    "{}{}{}",
                    pattern["translation_prefix"].as_str().unwrap_or(""),
                    translate_names(locale, body),
                    pattern["translation_suffix"].as_str().unwrap_or("")
                );
            }
        }
    }
    translated
}

/// Templates describe only known engine messages. Literal delimiters prevent
/// generic substitutions from altering unrelated custom campaign narrative.
fn match_template<'a>(mut template: &'a str, mut text: &'a str) -> Option<Vec<(&'a str, &'a str)>> {
    let mut captures = Vec::new();
    while let Some(open) = template.find('{') {
        text = text.strip_prefix(&template[..open])?;
        template = &template[open + 1..];
        let close = template.find('}')?;
        let name = &template[..close];
        template = &template[close + 1..];
        let next = template.find('{').unwrap_or(template.len());
        let delimiter = &template[..next];
        let end = if delimiter.is_empty() {
            if next != template.len() {
                return None;
            }
            text.len()
        } else {
            text.find(delimiter)?
        };
        captures.push((name, &text[..end]));
        text = &text[end..];
    }
    (text == template).then_some(captures)
}

fn translate_names(locale: &str, text: &str) -> String {
    // A captured name must match the full canonical name. Replacing a substring
    // such as "Knight" would also alter a custom campaign's "Custom Knight".
    if let Some(categories) = english()["entities"].as_object() {
        for (category, entries) in categories {
            if let Some(entries) = entries.as_object() {
                for (id, value) in entries {
                    if let Some(name) = value.as_str()
                        && name.eq_ignore_ascii_case(text)
                    {
                        return entity_name(locale, category, id, name);
                    }
                }
            }
        }
    }
    if let Some(value) = chinese()["text"][text].as_str() {
        return value.to_owned();
    }
    // Engine fields can themselves contain a generated altar offer label.
    // Every template consumes literal text, so matching recursively shrinks it.
    translate_text(locale, text)
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn all_original_strings_have_a_chinese_entry() {
        for id in 0..268 {
            assert!(
                chinese()["dialogue"][id.to_string()].is_string(),
                "Missing original dialogue {id}"
            );
        }
        assert_eq!(english()["dialogue"].as_object().unwrap().len(), 268);
    }
    #[test]
    fn original_content_translates_but_custom_content_survives() {
        assert_eq!(
            entity_name("zh-CN", "enemy", "green_slime", "Green Slime"),
            "绿色史莱姆"
        );
        assert_eq!(
            entity_name("zh-CN", "enemy", "green_slime", "Custom Goblin"),
            "Custom Goblin"
        );
        assert_eq!(
            translate_text("zh-CN", "A custom author's unlisted sentence."),
            "A custom author's unlisted sentence."
        );
        assert_eq!(translate_text("zh-CN", "Old man"), "老人");
        assert_eq!(translate_text("zh-CN", "Key merchant"), "钥匙商人");
        assert_eq!(
            translate_text("zh-CN", "Accept the gift · 0 gold"),
            "接受礼物 · 0金币"
        );
        assert_eq!(translate_text("zh-CN", "Custom Old man"), "Custom Old man");
        let combined = format!("{} {}", dialogue("en", 4), dialogue("en", 57));
        let translated = translate_text("zh-CN", &combined);
        assert!(translated.contains("武器"));
        assert!(translated.contains("第5层"));
    }
    #[test]
    fn every_english_ui_label_has_a_chinese_label() {
        for key in english()["ui"].as_object().unwrap().keys() {
            assert!(chinese()["ui"][key].is_string(), "Missing UI label {key}");
        }
    }
    #[test]
    fn journal_templates_translate_names_and_numeric_results() {
        assert_eq!(
            translate_text("zh-CN", "Defeated Golden Knight: −240 HP, +80 gold."),
            "击败黄金骑士：生命减少240，获得80金币。"
        );
        assert_eq!(
            translate_text("zh-CN", "Ambush: defeated Green Slime (−12 HP, +1 gold)."),
            "遭遇伏击：击败绿色史莱姆（生命减少12，获得1金币）。"
        );
        assert_eq!(
            translate_text("zh-CN", "Collected Red crystal: +3 attack."),
            "收集了红宝石：攻击增加3。"
        );
        assert_eq!(
            translate_text("zh-CN", "Defeated Custom Goblin: −20 HP, +4 gold."),
            "击败Custom Goblin：生命减少20，获得4金币。"
        );
        assert_eq!(
            translate_text("zh-CN", "Defeated Custom Golden Knight: −20 HP, +4 gold."),
            "击败Custom Golden Knight：生命减少20，获得4金币。"
        );
        assert_eq!(
            translate_text("zh-CN", "+100 hp purchased for 20 gold."),
            "花费20金币购买了+100 生命。"
        );
        assert_eq!(
            entity_name("zh-CN", "items", "sword_5", "Sacred sword"),
            "圣剑"
        );
        assert_eq!(
            entity_name("zh-CN", "tiles", "61", "Green Slime"),
            "绿色史莱姆"
        );
        assert_eq!(translate_text("zh-CN", "Floor 1"), "第1层");
        assert_eq!(
            translate_text(
                "zh-CN",
                "Your journey begins. Every battle is deterministic; plan your route carefully."
            ),
            "冒险开始了。每场战斗的结果都由属性决定，请仔细规划路线。"
        );
    }
}
