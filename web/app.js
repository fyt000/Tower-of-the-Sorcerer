/* Presentation and input only. The Rust engine owns every game rule. */
const $ = (id) => document.getElementById(id);
const STORAGE = {
  save: "tos-rust:save:v1",
  campaign: "tos-rust:campaign:v1",
  checkpoint: "tos-rust:checkpoint:v1",
};
const ui = {
  canvas: $("game-canvas"),
  ctx: $("game-canvas").getContext("2d"),
  portrait: $("portrait-canvas"),
  hover: null,
  selected: null,
  game: null,
  Game: null,
  campaign: null,
  campaignJson: "",
  originalCampaignJson: "",
  state: null,
  manifest: { tile_size: 40, columns: 11 },
  atlas: null,
  images: new Map(),
  maxHealth: 1000,
  log: [],
  ready: false,
  lastDirection: "down",
  toastTimer: null,
  choiceKey: "",
  dragStart: null,
  restartOriginal: false,
};

const escapeHtml = (value) =>
  String(value ?? "").replace(
    /[&<>"']/g,
    (c) =>
      ({ "&": "&amp;", "<": "&lt;", ">": "&gt;", '"': "&quot;", "'": "&#39;" })[
        c
      ],
  );
const format = (value) =>
  typeof value === "number"
    ? value.toLocaleString("en-US")
    : String(value ?? "—");
const pretty = (value) =>
  String(value ?? "")
    .replace(/[_-]/g, " ")
    .replace(/\b\w/g, (c) => c.toUpperCase());
const parse = (value) =>
  typeof value === "string" ? JSON.parse(value) : value;
const iconFor = (kind) =>
  ({
    enemy: "⚔",
    monster: "⚔",
    door: "⚿",
    key: "⚿",
    potion: "♥",
    gem: "◆",
    sword: "⚔",
    shield: "◇",
    stairs_up: "↗",
    stairs_down: "↙",
    stairs: "↗",
    npc: "✦",
    item: "✧",
    artifact: "✧",
    floor: "·",
    wall: "▥",
    shop: "◈",
  })[kind] || "✦";

function notify(message, error = false) {
  $("toast-text").textContent = message;
  $("toast").classList.toggle("error", error);
  $("toast").querySelector(".toast-symbol").textContent = error ? "!" : "✓";
  $("toast").hidden = false;
  clearTimeout(ui.toastTimer);
  ui.toastTimer = setTimeout(
    () => {
      $("toast").hidden = true;
    },
    error ? 6500 : 3200,
  );
}

function engineStatus(text, status) {
  $("engine-status").className = `engine-badge ${status || ""}`;
  $("engine-status").lastElementChild.textContent = text;
}

function closeMenu() {
  $("game-menu").hidden = true;
  $("settings-button").setAttribute("aria-expanded", "false");
}

function journalType(message) {
  if (/fight|battle|damage|defeat|killed/i.test(message)) return "combat";
  if (/key|potion|gem|gold|sword|shield|collect|treasure|obtain/i.test(message))
    return "treasure";
  if (/cannot|blocked|need|not enough|lost|died/i.test(message))
    return "warning";
  if (/floor|stair|save|welcome|restore|ascend/i.test(message))
    return "success";
  return "";
}

function renderJournal(log = []) {
  const messages = log.map((entry) =>
    typeof entry === "string"
      ? entry
      : entry.message || entry.text || JSON.stringify(entry),
  );
  if (messages.join("\n") === ui.log.join("\n")) return;
  ui.log = messages;
  const container = $("journal-log");
  const entries = [...messages].reverse().slice(0, 60);
  container.innerHTML = entries.length
    ? entries
        .map((message, index) => {
          const type = journalType(message);
          const mark =
            { combat: "⚔", treasure: "◆", warning: "!", success: "↗" }[type] ||
            "·";
          return `<div class="journal-entry ${type}"><span class="journal-mark">${mark}</span><div><p>${escapeHtml(message)}</p><span>${index === 0 ? "LATEST" : `ENTRY ${String(messages.length - index).padStart(2, "0")}`}</span></div></div>`;
        })
        .join("")
    : '<div class="journal-entry"><span class="journal-mark">✦</span><div><p>Welcome, adventurer.</p><span>Your story begins here.</span></div></div>';
  container.scrollTop = 0;
}

function floorEntries() {
  const floors = ui.campaign?.floors || [];
  if (Array.isArray(floors))
    return floors.map((floor, index) => ({
      ...floor,
      id: floor.id ?? floor.floor ?? index + 1,
    }));
  return Object.entries(floors).map(([id, floor]) => ({
    ...floor,
    id: Number(id),
  }));
}

function currentFloorInfo() {
  return (
    floorEntries().find(
      (floor) => Number(floor.id) === Number(ui.state?.floor),
    ) || {}
  );
}

function spriteRect(sprite) {
  if (sprite == null) return null;
  if (typeof sprite === "object") {
    if ("x" in sprite)
      return {
        x: sprite.x,
        y: sprite.y,
        w: sprite.w || sprite.width || ui.manifest.tile_size || 40,
        h: sprite.h || sprite.height || ui.manifest.tile_size || 40,
      };
    if ("index" in sprite) return spriteRect(sprite.index);
    if ("id" in sprite) return spriteRect(sprite.id);
  }
  const match = ui.manifest.tiles?.[sprite] || ui.manifest.sprites?.[sprite];
  if (match) return spriteRect(match);
  const index = Number(sprite) - 1;
  if (!Number.isFinite(index) || index < 0) return null;
  const size = ui.manifest.tile_size || 40;
  const columns = ui.manifest.columns || 11;
  return {
    x: (index % columns) * size,
    y: Math.floor(index / columns) * size,
    w: size,
    h: size,
  };
}

function drawSprite(context, sprite, x, y, width, height) {
  if (sprite?.source && ui.images.has(sprite.source)) {
    context.imageSmoothingEnabled = false;
    context.drawImage(ui.images.get(sprite.source), x, y, width, height);
    return true;
  }
  const rect = spriteRect(sprite);
  if (!ui.atlas || !rect || rect.y + rect.h > ui.atlas.height) return false;
  context.imageSmoothingEnabled = false;
  context.drawImage(
    ui.atlas,
    rect.x,
    rect.y,
    rect.w,
    rect.h,
    x,
    y,
    width,
    height,
  );
  return true;
}

function tileAt(x, y) {
  const state = ui.state;
  if (!state || x < 0 || y < 0 || x >= state.width || y >= state.height)
    return null;
  const id = Array.isArray(state.tiles[y])
    ? state.tiles[y][x]
    : state.tiles[y * state.width + x];
  const def =
    state.tile_defs?.[id] ||
    ui.campaign?.tile_defs?.[id] ||
    ui.campaign?.tiles?.[id] ||
    {};
  return { id, ...def, x, y };
}

function fallbackTile(context, tile, x, y, size) {
  const kind = tile.kind || "floor";
  context.fillStyle = ["wall", "rock", "blocked"].includes(kind)
    ? "#43433e"
    : "#262c2c";
  context.fillRect(x, y, size, size);
  if (["wall", "rock", "blocked"].includes(kind)) {
    context.strokeStyle = "#242a2a";
    context.lineWidth = 2;
    context.strokeRect(x + 1, y + 1, size - 2, size - 2);
    context.beginPath();
    context.moveTo(x, y + size / 2);
    context.lineTo(x + size, y + size / 2);
    context.moveTo(x + size / 2, y);
    context.lineTo(x + size / 2, y + size / 2);
    context.stroke();
  } else if (!["floor", "empty", "hidden"].includes(kind)) {
    context.fillStyle =
      {
        enemy: "#c89487",
        monster: "#c89487",
        key: "#d8bc76",
        door: "#b4a06c",
        potion: "#d88b98",
        gem: "#8fbbde",
        stairs_up: "#afb6bb",
        stairs_down: "#afb6bb",
        npc: "#cdbb87",
      }[kind] || "#b5c0c6";
    context.textAlign = "center";
    context.textBaseline = "middle";
    context.font = `${Math.round(size * 0.52)}px Georgia`;
    context.fillText(iconFor(kind), x + size / 2, y + size / 2 + 2);
  }
}

function renderBoard() {
  const state = ui.state;
  if (!state) return;
  const ctx = ui.ctx;
  const size = 64;
  const width = state.width || 11;
  const height = state.height || 11;
  if (ui.canvas.width !== width * size || ui.canvas.height !== height * size) {
    ui.canvas.width = width * size;
    ui.canvas.height = height * size;
    $("canvas-wrap").style.aspectRatio = `${width} / ${height}`;
  }
  ctx.imageSmoothingEnabled = false;
  ctx.fillStyle = "#1e2425";
  ctx.fillRect(0, 0, ui.canvas.width, ui.canvas.height);
  for (let y = 0; y < height; y++) {
    for (let x = 0; x < width; x++) {
      const tile = tileAt(x, y) || { kind: "floor", id: 6 };
      const px = x * size,
        py = y * size;
      drawSprite(ctx, ui.manifest.floor || 6, px, py, size, size);
      if (!drawSprite(ctx, tile.sprite ?? tile.id, px, py, size, size))
        fallbackTile(ctx, tile, px, py, size);
    }
  }
  const player = state.player;
  if (player) {
    const x = player.x * size,
      y = player.y * size;
    ctx.fillStyle = "#d6b46e25";
    ctx.fillRect(x, y, size, size);
    const heroSprite =
      ui.manifest.hero_directions?.[ui.lastDirection] ||
      ui.manifest.hero ||
      player.sprite ||
      185;
    if (!drawSprite(ctx, heroSprite, x, y, size, size)) {
      ctx.fillStyle = "#cfb981";
      ctx.beginPath();
      ctx.arc(x + size / 2, y + size / 2, size * 0.23, 0, Math.PI * 2);
      ctx.fill();
      ctx.fillStyle = "#152433";
      ctx.font = "bold 24px Georgia";
      ctx.textAlign = "center";
      ctx.textBaseline = "middle";
      ctx.fillText("♙", x + size / 2, y + size / 2 + 2);
    }
    ctx.strokeStyle = "#ebd495";
    ctx.lineWidth = 2;
    const inset = 4,
      edge = 10;
    ctx.beginPath();
    for (const [cx, cy, dx, dy] of [
      [x + inset, y + inset, 1, 1],
      [x + size - inset, y + inset, -1, 1],
      [x + inset, y + size - inset, 1, -1],
      [x + size - inset, y + size - inset, -1, -1],
    ]) {
      ctx.moveTo(cx + dx * edge, cy);
      ctx.lineTo(cx, cy);
      ctx.lineTo(cx, cy + dy * edge);
    }
    ctx.stroke();
  }
  const highlighted = ui.hover || ui.selected;
  if (highlighted) {
    const x = highlighted.x * size,
      y = highlighted.y * size;
    ctx.fillStyle = "#d8bc7c1c";
    ctx.fillRect(x, y, size, size);
    ctx.strokeStyle = "#e7cc8b";
    ctx.lineWidth = 2;
    ctx.strokeRect(x + 2, y + 2, size - 4, size - 4);
  }
  if (state.status === "won" || state.status === "lost") {
    ctx.fillStyle = "#07101cbb";
    ctx.fillRect(0, 0, ui.canvas.width, ui.canvas.height);
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillStyle = state.status === "won" ? "#e3c68c" : "#d39d9d";
    ctx.font = "38px Georgia";
    ctx.fillText(
      state.status === "won"
        ? "The tower is conquered"
        : "Your journey ends here",
      ui.canvas.width / 2,
      ui.canvas.height / 2 - 12,
    );
    ctx.fillStyle = "#a3aec0";
    ctx.font = "15px sans-serif";
    ctx.fillText(
      "Open the menu to begin a new adventure",
      ui.canvas.width / 2,
      ui.canvas.height / 2 + 35,
    );
  }
}

function makeSpriteCanvas(sprite, width = 40) {
  const canvas = document.createElement("canvas");
  canvas.width = width;
  canvas.height = width;
  drawSprite(canvas.getContext("2d"), sprite, 0, 0, width, width);
  return canvas;
}

function renderInventory() {
  const items = ui.state?.player?.inventory || [];
  const inventoryInfo = ui.state.inventory_items || [];
  const hasUsableItem = items.some(
    (item) => inventoryInfo.find((info) => info.id === item)?.usable !== false,
  );
  $("item-count").textContent = `${items.length} found`;
  const grid = $("inventory-grid");
  grid.replaceChildren();
  for (let i = 0; i < Math.max(4, items.length); i++) {
    const button = document.createElement("button");
    button.className = "inventory-slot";
    if (i < items.length) {
      const raw = items[i];
      const item = typeof raw === "object" ? raw.id || raw.name : raw;
      const info = inventoryInfo.find((entry) => entry.id === item);
      const def = Object.values(ui.state.tile_defs || {}).find(
        (tile) =>
          tile.item === item ||
          tile.id === item ||
          tile.name?.toLowerCase().replaceAll(" ", "_") ===
            String(item).toLowerCase(),
      );
      const name = info?.name || def?.name || pretty(item);
      const usable = info?.usable !== false;
      const sprite = info?.sprite || def?.sprite;
      button.classList.add("filled");
      button.title = usable ? name : `${name} · Always active`;
      button.setAttribute(
        "aria-label",
        usable ? `Use ${name}` : `${name}, always active`,
      );
      if (sprite && ui.atlas) button.append(makeSpriteCanvas(sprite));
      else button.textContent = iconFor(def?.kind || "artifact");
      if (usable) button.addEventListener("click", () => useItem(item));
      else {
        button.disabled = true;
        button.classList.add("passive");
      }
      if (Number(info?.charges) > 1) {
        const charges = document.createElement("span");
        charges.className = "inventory-charge";
        charges.textContent = String(info.charges);
        button.append(charges);
      }
    } else {
      button.textContent = "·";
      button.disabled = true;
      button.setAttribute("aria-label", "Empty artifact slot");
    }
    grid.append(button);
  }
  $("inventory-hint").textContent = !items.length
    ? "There are secrets in this tower."
    : hasUsableItem
      ? "Select an artifact to use its power."
      : "Equipped gear and passive artifacts.";
}

function renderJourney() {
  const state = ui.state;
  const floors = floorEntries();
  const floorIds = floors.length
    ? floors.map((floor) => Number(floor.id)).sort((a, b) => a - b)
    : Array.from({ length: 50 }, (_, i) => i + 1);
  const visited = new Set(state.visited_floors || [state.floor]);
  $("journey-track").innerHTML = floorIds
    .map(
      (id) =>
        `<span title="Floor ${id}" class="journey-segment${visited.has(id) ? " visited" : ""}${Number(state.floor) === id ? " current" : ""}"></span>`,
    )
    .join("");
  $("journey-progress").textContent =
    `${visited.size} / ${floorIds.length} explored`;
}

function renderState(rawState, { initial = false } = {}) {
  const previousFloor = ui.state?.floor;
  ui.state = parse(rawState);
  const state = ui.state,
    player = state.player;
  if (!player)
    throw new Error("The Rust engine returned a state without player data.");
  ui.maxHealth = Math.max(ui.maxHealth, player.hp, 1);
  $("hp-value").textContent = format(player.hp);
  $("health-fill").style.width =
    `${Math.max(0, Math.min(100, (player.hp / ui.maxHealth) * 100))}%`;
  $("attack-value").textContent = format(player.attack);
  $("defense-value").textContent = format(player.defense);
  $("gold-value").textContent = format(player.gold);
  for (const stat of ["hp", "attack", "defense", "gold"])
    $(`mobile-${stat}-value`).textContent = format(player[stat]);
  $("fourth-stat-label").textContent =
    player.level != null
      ? "Level"
      : player.experience != null
        ? "Experience"
        : "Floor";
  $("level-value").textContent = format(
    player.level ?? player.experience ?? state.floor,
  );
  const keys = player.keys || {};
  for (const color of ["yellow", "blue", "red"])
    $(`${color}-keys`).textContent = format(keys[color] || 0);
  const totalKeys = ["yellow", "blue", "red"].reduce(
    (sum, color) => sum + (keys[color] || 0),
    0,
  );
  $("key-total").textContent =
    `${totalKeys} ${totalKeys === 1 ? "key" : "keys"}`;
  const floorInfo = currentFloorInfo();
  $("floor-name").textContent =
    floorInfo.name ||
    (floorInfo.title && !/^Floor\s*\d+$/i.test(floorInfo.title)
      ? floorInfo.title
      : Number(state.floor) === 0
        ? "The beginning"
        : "The Sorcerer’s tower");
  $("floor-number").textContent = String(state.floor).padStart(2, "0");
  $("floor-description").textContent =
    floorInfo.subtitle ||
    floorInfo.description ||
    `Floor ${state.floor} · ${state.enemies?.length || 0} encounters await`;
  $("board-coordinate").textContent = `${state.width} × ${state.height}`;
  $("turn-count").textContent =
    `TURN ${String(state.steps ?? state.turn ?? state.turns ?? state.moves ?? 0).padStart(4, "0")}`;
  $("hero-subtitle").textContent =
    state.status === "won"
      ? "The promise is fulfilled."
      : state.status === "lost"
        ? "A brave journey, remembered."
        : "A promise. A tower. A way up.";
  $("campaign-label").textContent =
    ui.campaign.name || ui.campaign.title || "Original campaign";
  $("original-campaign-button").hidden =
    ui.campaignJson === ui.originalCampaignJson;
  updateCheckpointAvailability();
  renderInventory();
  renderJourney();
  renderJournal(state.log || []);
  if (previousFloor != null && previousFloor !== state.floor) {
    ui.hover = null;
    ui.selected = null;
    resetInspector();
  }
  renderBoard();
  if (ui.selected || ui.hover)
    inspectTile((ui.hover || ui.selected).x, (ui.hover || ui.selected).y);
  renderInteraction();
  if (!initial) autoSave();
}

function resetInspector() {
  $("encounter-content").className = "encounter-content";
  $("encounter-content").innerHTML =
    '<div class="empty-inspector-symbol" aria-hidden="true"><svg viewBox="0 0 52 52"><path d="M7 26s7-13 19-13 19 13 19 13-7 13-19 13S7 26 7 26Z"/><circle cx="26" cy="26" r="7"/><path d="M26 5v4M26 43v4M5 26h4M43 26h4"/></svg></div><h2>Know your opponent</h2><p>Hover over a monster to see its strength and the exact cost of battle.</p>';
}

function inspectTile(x, y) {
  if (!ui.ready) return;
  try {
    const inspection = parse(ui.game.inspect_json(x, y));
    const tile = tileAt(x, y);
    const enemy =
      inspection.enemy ||
      ui.state.enemies?.find((entry) => entry.x === x && entry.y === y);
    const kind = inspection.kind || tile?.kind || "floor";
    const content = $("encounter-content");
    content.className = "encounter-content populated";
    const name = inspection.name || tile?.name || pretty(kind);
    const enemyStats = enemy
      ? `<div class="encounter-stats"><span class="encounter-stat">Health<strong>${format(enemy.hp)}</strong></span><span class="encounter-stat">Attack<strong>${format(enemy.attack)}</strong></span><span class="encounter-stat">Defense<strong>${format(enemy.defense)}</strong></span><span class="encounter-stat">Gold<strong>${format(enemy.gold)}</strong></span></div>`
      : "";
    let forecast = "";
    if (enemy) {
      const safe = enemy.can_win !== false && Number(enemy.damage) === 0;
      const impossible = enemy.damage == null;
      const fatal = enemy.can_win === false && !impossible;
      forecast = `<div class="damage-preview${safe ? " safe" : ""}${impossible ? " blocked" : ""}"><span>${impossible ? "Battle unavailable" : fatal ? "A fatal battle" : safe ? "A flawless victory" : "Predicted health loss"}</span><strong>${impossible ? "—" : Number(enemy.damage) === 0 ? "0" : `−${format(enemy.damage)}`}</strong></div>`;
    }
    content.innerHTML = `<div class="encounter-heading"><div class="encounter-art" aria-hidden="true">${iconFor(kind)}</div><div><h2>${escapeHtml(name)}</h2><div class="encounter-type">${enemy ? "MONSTER" : pretty(kind).toUpperCase()} <span>· ${x + 1}, ${y + 1}</span></div></div></div>${enemyStats}${forecast}<div class="encounter-note">${escapeHtml(enemy?.reason || inspection.description || (enemy ? "Check the predicted health cost, then move into this square to enter battle." : "Explore the tower one step at a time."))}</div>`;
    const sprite = tile?.sprite ?? tile?.id;
    if (ui.atlas && sprite != null) {
      const art = content.querySelector(".encounter-art");
      art.replaceChildren(makeSpriteCanvas(sprite));
    }
  } catch (error) {
    console.warn("Tile inspection failed:", error);
  }
}

function renderInteraction() {
  const interaction = ui.state.pending_interaction;
  const dialog = $("choice-dialog");
  if (!interaction) {
    if (dialog.open) dialog.close();
    ui.choiceKey = "";
    return;
  }
  const key = JSON.stringify(interaction);
  if (key === ui.choiceKey) return;
  ui.choiceKey = key;
  $("choice-title").textContent = interaction.title || "A crossing of paths";
  $("choice-description").textContent =
    interaction.text || interaction.description || "";
  $("choice-options").replaceChildren();
  for (const choice of interaction.choices || []) {
    const button = document.createElement("button");
    button.className = "button button-subtle choice-option";
    const label = document.createElement("span");
    label.textContent = choice.label;
    const arrow = document.createElement("span");
    arrow.textContent = "→";
    button.append(label, arrow);
    button.disabled = choice.available === false || choice.disabled === true;
    button.addEventListener("click", () =>
      command({ type: "choose", choice: String(choice.id) }),
    );
    $("choice-options").append(button);
  }
  if (!dialog.open) dialog.showModal();
}

function autoSave() {
  if (!ui.game) return false;
  try {
    localStorage.setItem(STORAGE.save, ui.game.save_json());
    $("save-status").textContent = "Progress saved on this device";
    return true;
  } catch {
    $("save-status").textContent = "Export a file to keep your progress";
    return false;
  }
}

function readCheckpoint() {
  try {
    const checkpoint = JSON.parse(localStorage.getItem(STORAGE.checkpoint));
    return checkpoint?.campaign_id === ui.state?.campaign_id &&
      checkpoint?.campaign_json === ui.campaignJson &&
      typeof checkpoint.save === "string"
      ? checkpoint
      : null;
  } catch {
    return null;
  }
}

function updateCheckpointAvailability() {
  $("restore-checkpoint-button").disabled = !readCheckpoint();
}

function saveCheckpoint() {
  if (!ui.ready) return;
  try {
    const checkpoint = {
      campaign_id: ui.state.campaign_id,
      campaign_json: ui.campaignJson,
      save: ui.game.save_json(),
    };
    localStorage.setItem(STORAGE.checkpoint, JSON.stringify(checkpoint));
    autoSave();
    updateCheckpointAvailability();
    notify("Checkpoint saved. You can restore it from the game menu.");
  } catch {
    downloadSave();
  }
}

function restoreCheckpoint() {
  closeMenu();
  const checkpoint = readCheckpoint();
  if (!checkpoint)
    return notify("There is no saved checkpoint for this campaign.", true);
  try {
    const restored = ui.game.load_json(checkpoint.save);
    ui.hover = null;
    ui.selected = null;
    ui.choiceKey = "";
    ui.lastDirection = "down";
    resetInspector();
    renderState(restored);
    ui.canvas.focus({ preventScroll: true });
    notify("Your saved checkpoint has been restored.");
  } catch (error) {
    notify(`Could not restore checkpoint: ${error.message || error}`, true);
  }
}

function command(action) {
  if (!ui.ready) return;
  try {
    renderState(ui.game.command_json(JSON.stringify(action)));
    if (ui.state.last_action?.ok === false && ui.state.last_action.message) {
      notify(ui.state.last_action.message, true);
    }
    ui.canvas.focus({ preventScroll: true });
  } catch (error) {
    notify(error.message || String(error), true);
  }
}

function move(direction) {
  if (
    !ui.ready ||
    ui.state.pending_interaction ||
    ui.state.status !== "playing"
  )
    return;
  ui.lastDirection = direction;
  command({ type: "move", direction });
}

function useItem(item) {
  if (
    [
      "flying_orb",
      "orb_of_flying",
      "floor_wand",
      "fly",
      "floor_teleporter",
      "flying_wand",
      "teleporter",
      "floor_fly",
    ].includes(item)
  )
    openMap(true, item);
  else command({ type: "use_item", item });
}

function openMap(travel = false, item = null) {
  if (!ui.ready) return;
  const visited = new Set(ui.state.visited_floors || [ui.state.floor]);
  const floors = floorEntries();
  const floorIds = floors.length
    ? floors.map((floor) => Number(floor.id)).sort((a, b) => b - a)
    : Array.from({ length: 50 }, (_, i) => 50 - i);
  const map = $("tower-map");
  map.replaceChildren();
  for (const id of floorIds) {
    const known = visited.has(id),
      current = id === Number(ui.state.floor);
    const button = document.createElement("button");
    button.className = `map-floor${known ? " visited" : ""}${current ? " current" : ""}${travel && known && !current ? " can-travel" : ""}`;
    button.innerHTML = `${String(id).padStart(2, "0")}<span class="floor-caption">${current ? "YOU ARE HERE" : known ? "EXPLORED" : "UNKNOWN"}</span>`;
    button.title =
      floors.find((floor) => Number(floor.id) === id)?.name || `Floor ${id}`;
    button.disabled = !(travel && known && !current);
    if (travel && known && !current)
      button.addEventListener("click", () => {
        $("map-dialog").close();
        command({ type: "use_item", item, floor: id });
      });
    map.append(button);
  }
  $("map-description").textContent = travel
    ? "Select a discovered floor to travel there. The tower decides where this artifact can take you."
    : "Your discovered floors. Follow the stairs to continue your ascent.";
  $("map-dialog").showModal();
}

function startGame(save = undefined) {
  ui.game?.free?.();
  ui.game = new ui.Game(ui.campaignJson, save);
  ui.selected = null;
  ui.hover = null;
  ui.choiceKey = "";
  ui.log = [];
  ui.lastDirection = "down";
  ui.maxHealth = 1000;
  resetInspector();
  renderState(ui.game.state_json(), { initial: true });
  ui.ready = true;
  autoSave();
}

async function loadImage(url) {
  const image = new Image();
  await new Promise((resolve, reject) => {
    image.onload = resolve;
    image.onerror = reject;
    image.src = url;
  });
  return image;
}

async function loadAssets() {
  try {
    const response = await fetch("./assets/manifest.json");
    if (response.ok)
      ui.manifest = { ...ui.manifest, ...(await response.json()) };
  } catch {
    /* Original atlas can still be rendered with the known layout. */
  }
  try {
    let atlasUrl = ui.manifest.atlas || "./assets/original-atlas.png";
    if (atlasUrl.startsWith("assets/")) atlasUrl = `./${atlasUrl}`;
    ui.atlas = await loadImage(atlasUrl);
    const sources = [
      ...new Set(
        [ui.manifest.hero, ...Object.values(ui.manifest.hero_directions || {})]
          .map((sprite) => sprite?.source)
          .filter(Boolean),
      ),
    ];
    await Promise.all(
      sources.map(async (source) => {
        try {
          ui.images.set(source, await loadImage(source));
        } catch {
          console.warn(`Could not load hero sprite ${source}`);
        }
      }),
    );
    const context = ui.portrait.getContext("2d");
    if (drawSprite(context, ui.manifest.hero || 185, 5, 5, 62, 62))
      ui.portrait.parentElement.classList.add("has-sprite");
  } catch {
    console.warn(
      "Original sprite atlas unavailable; using accessible fallback symbols.",
    );
  }
}

async function boot() {
  try {
    const assetPromise = loadAssets();
    const [wasm, response] = await Promise.all([
      import("./pkg/tos_wasm.js"),
      fetch("./campaign.json"),
    ]);
    if (!response.ok)
      throw new Error(`Campaign could not be loaded (${response.status}).`);
    await wasm.default();
    ui.Game = wasm.Game;
    const originalJson = await response.text();
    ui.originalCampaignJson = originalJson;
    let storedCampaign = null,
      save = null;
    try {
      storedCampaign = localStorage.getItem(STORAGE.campaign);
      save = localStorage.getItem(STORAGE.save);
    } catch {
      /* Browser privacy settings may disable local storage. */
    }
    ui.campaignJson = storedCampaign || originalJson;
    ui.campaign = JSON.parse(ui.campaignJson);
    await assetPromise;
    try {
      startGame(save || undefined);
    } catch (error) {
      if (!save) throw error;
      startGame();
      notify(
        "The previous save could not be restored. A new adventure has begun.",
        true,
      );
    }
    $("loading-overlay").hidden = true;
    $("save-button").disabled = false;
    $("floor-map-button").disabled = false;
    engineStatus("Rust engine · ready", "ready");
    ui.canvas.focus({ preventScroll: true });
  } catch (error) {
    console.error(error);
    engineStatus("Engine unavailable", "error");
    $("loading-overlay").classList.add("error");
    $("loading-title").textContent = "The tower is waiting";
    $("loading-message").textContent =
      `${error.message || error} Build the browser package with the project’s web build script, then serve the web directory over HTTP.`;
  }
}

function boardPosition(event) {
  const rect = ui.canvas.getBoundingClientRect();
  return {
    x: Math.min(
      ui.state.width - 1,
      Math.max(
        0,
        Math.floor(((event.clientX - rect.left) / rect.width) * ui.state.width),
      ),
    ),
    y: Math.min(
      ui.state.height - 1,
      Math.max(
        0,
        Math.floor(
          ((event.clientY - rect.top) / rect.height) * ui.state.height,
        ),
      ),
    ),
  };
}

ui.canvas.addEventListener("pointermove", (event) => {
  if (!ui.ready || event.pointerType === "touch") return;
  const position = boardPosition(event);
  if (position.x === ui.hover?.x && position.y === ui.hover?.y) return;
  ui.hover = position;
  $("board-coordinate").textContent = `${position.x + 1}, ${position.y + 1}`;
  renderBoard();
  inspectTile(position.x, position.y);
});
ui.canvas.addEventListener("pointerleave", () => {
  ui.hover = null;
  if (ui.state)
    $("board-coordinate").textContent =
      `${ui.state.width} × ${ui.state.height}`;
  renderBoard();
  if (ui.selected) inspectTile(ui.selected.x, ui.selected.y);
});
ui.canvas.addEventListener("pointerdown", (event) => {
  if (!ui.ready) return;
  ui.dragStart = { clientX: event.clientX, clientY: event.clientY };
  if (event.pointerType === "touch")
    ui.canvas.setPointerCapture(event.pointerId);
});
ui.canvas.addEventListener("pointercancel", () => {
  ui.dragStart = null;
});
ui.canvas.addEventListener("pointerup", (event) => {
  if (!ui.ready) return;
  const dx = event.clientX - (ui.dragStart?.clientX ?? event.clientX),
    dy = event.clientY - (ui.dragStart?.clientY ?? event.clientY);
  ui.dragStart = null;
  if (
    event.pointerType === "touch" &&
    Math.max(Math.abs(dx), Math.abs(dy)) > 24
  )
    move(
      Math.abs(dx) > Math.abs(dy)
        ? dx > 0
          ? "right"
          : "left"
        : dy > 0
          ? "down"
          : "up",
    );
  else {
    ui.selected = boardPosition(event);
    inspectTile(ui.selected.x, ui.selected.y);
    renderBoard();
    ui.canvas.focus({ preventScroll: true });
  }
});

const keyDirections = {
  ArrowUp: "up",
  ArrowDown: "down",
  ArrowLeft: "left",
  ArrowRight: "right",
  w: "up",
  W: "up",
  s: "down",
  S: "down",
  a: "left",
  A: "left",
  d: "right",
  D: "right",
};
document.addEventListener("keydown", (event) => {
  if (event.key === "Escape") closeMenu();
  if (
    !keyDirections[event.key] ||
    event.ctrlKey ||
    event.metaKey ||
    event.altKey ||
    document.querySelector("dialog[open]") ||
    ["INPUT", "TEXTAREA", "SELECT"].includes(document.activeElement?.tagName)
  )
    return;
  event.preventDefault();
  move(keyDirections[event.key]);
});
document
  .querySelectorAll("[data-direction]")
  .forEach((button) =>
    button.addEventListener("click", () => move(button.dataset.direction)),
  );
document
  .querySelectorAll("[data-close-dialog]")
  .forEach((button) =>
    button.addEventListener("click", () => button.closest("dialog").close()),
  );
document.querySelectorAll("dialog").forEach((dialog) =>
  dialog.addEventListener("click", (event) => {
    if (event.target === dialog && dialog.id !== "choice-dialog") {
      const rect = dialog.getBoundingClientRect();
      if (
        event.clientX < rect.left ||
        event.clientX > rect.right ||
        event.clientY < rect.top ||
        event.clientY > rect.bottom
      )
        dialog.close();
    }
  }),
);
$("choice-dialog").addEventListener("cancel", (event) => {
  event.preventDefault();
  command({ type: "cancel" });
});
$("help-button").addEventListener("click", () => $("help-dialog").showModal());
$("floor-map-button").addEventListener("click", () => openMap());
$("clear-log-button").addEventListener("click", () => {
  $("journal-log").replaceChildren();
  ui.log = [];
});
$("settings-button").addEventListener("click", () => {
  $("game-menu").hidden = !$("game-menu").hidden;
  $("settings-button").setAttribute(
    "aria-expanded",
    String(!$("game-menu").hidden),
  );
});
document.addEventListener("click", (event) => {
  if (!event.target.closest(".header-actions")) closeMenu();
});
$("save-button").addEventListener("click", saveCheckpoint);
$("restore-checkpoint-button").addEventListener("click", restoreCheckpoint);

function downloadSave() {
  if (!ui.ready) return notify("The game engine is still starting.", true);
  const blob = new Blob([ui.game.save_json()], { type: "application/json" });
  const link = document.createElement("a");
  link.href = URL.createObjectURL(blob);
  link.download = `sorcerer-floor-${ui.state.floor}-save.json`;
  link.click();
  setTimeout(() => URL.revokeObjectURL(link.href), 1000);
  closeMenu();
  notify("Save file exported. Your journey can travel with you.");
}
$("download-save-button").addEventListener("click", downloadSave);
$("load-save-button").addEventListener("click", () => {
  closeMenu();
  $("save-file-input").click();
});
$("load-campaign-button").addEventListener("click", () => {
  closeMenu();
  $("campaign-file-input").click();
});
function confirmRestart(original = false) {
  closeMenu();
  if (!ui.ready) return;
  ui.restartOriginal = original;
  $("confirm-title").textContent = original
    ? "Return to the original tower?"
    : "Start a new adventure?";
  $("confirm-restart-button").textContent = original
    ? "Enter the original tower"
    : "Start again";
  $("confirm-dialog").showModal();
}
$("restart-button").addEventListener("click", () => confirmRestart());
$("original-campaign-button").addEventListener("click", () =>
  confirmRestart(true),
);
$("confirm-restart-button").addEventListener("click", () => {
  $("confirm-dialog").close();
  try {
    if (ui.restartOriginal) {
      ui.campaignJson = ui.originalCampaignJson;
      ui.campaign = JSON.parse(ui.campaignJson);
      try {
        localStorage.removeItem(STORAGE.campaign);
      } catch {
        /* This browser may disable local storage. */
      }
    }
    startGame();
    notify("A new adventure begins.");
  } catch (error) {
    notify(error.message || error, true);
  }
});
$("save-file-input").addEventListener("change", async (event) => {
  const file = event.target.files[0];
  if (!file || !ui.Game) return;
  try {
    const save = await file.text();
    JSON.parse(save);
    const candidate = new ui.Game(ui.campaignJson, save);
    parse(candidate.state_json());
    ui.game?.free?.();
    ui.game = candidate;
    ui.selected = null;
    ui.hover = null;
    ui.choiceKey = "";
    ui.log = [];
    ui.maxHealth = 1000;
    ui.lastDirection = "down";
    resetInspector();
    ui.ready = true;
    renderState(ui.game.state_json());
    notify("Your adventure has been restored.");
  } catch (error) {
    notify(`Could not import save: ${error.message || error}`, true);
  }
  event.target.value = "";
});
$("campaign-file-input").addEventListener("change", async (event) => {
  const file = event.target.files[0];
  if (!file || !ui.Game) return;
  try {
    const json = await file.text();
    const campaign = JSON.parse(json);
    const candidate = new ui.Game(json);
    parse(candidate.state_json());
    ui.game?.free?.();
    ui.game = candidate;
    ui.campaignJson = json;
    ui.campaign = campaign;
    ui.selected = null;
    ui.hover = null;
    ui.choiceKey = "";
    ui.log = [];
    ui.maxHealth = 1000;
    ui.lastDirection = "down";
    resetInspector();
    ui.ready = true;
    try {
      localStorage.setItem(STORAGE.campaign, json);
    } catch {
      /* File export remains available. */
    }
    renderState(ui.game.state_json());
    notify(
      `Loaded ${campaign.name || campaign.title || file.name}. A new adventure begins.`,
    );
  } catch (error) {
    notify(`Could not load campaign: ${error.message || error}`, true);
  }
  event.target.value = "";
});
window.addEventListener("beforeunload", autoSave);

/* A read-only bridge makes browser smoke tests and accessibility diagnostics simple. */
window.tower = {
  state: () => (ui.state ? structuredClone(ui.state) : null),
  isReady: () => ui.ready,
};
boot();
