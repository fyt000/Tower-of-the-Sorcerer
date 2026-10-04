import { chromium } from "@playwright/test";
import assert from "node:assert/strict";
import { mkdir, readFile, writeFile } from "node:fs/promises";
import { resolve } from "node:path";

const root = resolve(import.meta.dirname, "..");
const output = resolve(root, "test-results");
const url = process.env.TOS_TEST_URL || "http://127.0.0.1:8080";
await mkdir(output, { recursive: true });
const browser = await chromium.launch({ headless: true });
const failures = [];
const checks = [];
const check = (name) => {
  checks.push(name);
  console.log(`✓ ${name}`);
};
const original = JSON.parse(
  await readFile(resolve(root, "data/campaign.json"), "utf8"),
);

async function ready(page) {
  await page.waitForFunction(() => window.tower?.isReady(), null, {
    timeout: 20000,
  });
  await page.locator("#loading-overlay").waitFor({ state: "hidden" });
  await page.evaluate(() => document.fonts.ready);
}
async function snapshot(page) {
  return page.evaluate(() => window.tower.state());
}
async function inspect(page, x, y) {
  const box = await page.locator("#game-canvas").boundingBox();
  const state = await snapshot(page);
  await page.mouse.move(
    box.x + ((x + 0.5) * box.width) / state.width,
    box.y + ((y + 0.5) * box.height) / state.height,
  );
}
async function upload(page, input, name, value) {
  await page.locator(input).setInputFiles({
    name,
    mimeType: "application/json",
    buffer: Buffer.from(
      typeof value === "string" ? value : JSON.stringify(value),
    ),
  });
}
function watch(page) {
  page.on("pageerror", (error) =>
    failures.push(`JavaScript: ${error.message}`),
  );
  page.on("console", (message) => {
    if (message.type() === "error") failures.push(`Console: ${message.text()}`);
  });
  page.on("response", (response) => {
    if (response.url().startsWith(url) && response.status() >= 400)
      failures.push(`HTTP ${response.status()}: ${response.url()}`);
  });
  page.on("requestfailed", (request) => {
    if (request.url().startsWith(url))
      failures.push(
        `Network: ${request.url()} ${request.failure()?.errorText}`,
      );
  });
}

try {
  const context = await browser.newContext({
    viewport: { width: 1440, height: 1080 },
    deviceScaleFactor: 1,
    acceptDownloads: true,
  });
  const page = await context.newPage();
  watch(page);
  await page.goto(url);
  await ready(page);
  let state = await snapshot(page);
  assert.equal(state.width, 11);
  assert.equal(state.height, 11);
  assert.equal(state.floor, original.start.floor);
  assert.equal(state.tiles.length, 121);
  assert.deepEqual(state.player.keys, original.start.keys);
  assert.equal(state.player.hp, original.start.hp);
  assert.equal(
    await page.locator("#attack-value").textContent(),
    original.start.attack.toLocaleString("en-US"),
  );
  assert.equal(
    await page.locator("#game-canvas").evaluate((canvas) => canvas.width),
    704,
  );
  const passive = state.inventory_items?.filter((item) => !item.usable) || [];
  assert.equal(
    await page.locator(".inventory-slot.passive").count(),
    passive.length,
  );
  for (const item of passive)
    assert.equal(
      await page
        .getByRole("button", {
          name: `${item.name}, always active`,
          exact: true,
        })
        .isDisabled(),
      true,
    );
  check(
    "Original campaign boots in actual Rust WebAssembly and renders its stats and board",
  );

  const enemy = state.enemies[0];
  assert.ok(enemy, "Original floor contains enemies");
  await inspect(page, enemy.x, enemy.y);
  await page.locator(".encounter-stats").waitFor();
  assert.ok(
    (await page.locator("#encounter-content").textContent()).includes(
      String(enemy.hp),
    ),
  );
  assert.equal(
    await page.locator(".damage-preview strong").textContent(),
    enemy.damage == null
      ? "—"
      : Number(enemy.damage) === 0
        ? "0"
        : `−${enemy.damage.toLocaleString("en-US")}`,
  );
  check("Monster inspector displays the combat forecast returned by Rust");

  await page.locator("#help-button").click();
  assert.equal(
    await page.locator("#help-dialog").evaluate((dialog) => dialog.open),
    true,
  );
  await page.locator("#help-dialog [data-close-dialog]").first().click();
  await page.locator("#floor-map-button").click();
  assert.equal(
    await page.locator(".map-floor").count(),
    original.floors.length,
  );
  assert.equal(await page.locator(".map-floor.current").count(), 1);
  await page.locator("#map-dialog [data-close-dialog]").click();
  check("Help and discovered tower map are accessible native dialogs");

  const checkpointPlayer = structuredClone((await snapshot(page)).player);
  assert.equal(
    await page.locator("#restore-checkpoint-button").isDisabled(),
    true,
  );
  await page.locator("#save-button").click();
  await page.keyboard.press("ArrowRight");
  assert.notDeepEqual((await snapshot(page)).player, checkpointPlayer);
  await page.locator("#settings-button").click();
  await page.locator("#restore-checkpoint-button").click();
  assert.deepEqual((await snapshot(page)).player, checkpointPlayer);
  check(
    "Save game creates a separate checkpoint and its menu action restores Rust state",
  );

  const startX = state.player.x,
    startY = state.player.y;
  await page.keyboard.press("ArrowRight");
  state = await snapshot(page);
  assert.equal(state.player.x, startX + 1);
  assert.equal(state.player.y, startY);
  assert.equal(
    await page.locator("#turn-count").textContent(),
    `TURN ${String(state.steps).padStart(4, "0")}`,
  );
  const moved = structuredClone(state.player);
  await page.reload();
  await ready(page);
  assert.deepEqual((await snapshot(page)).player, moved);
  assert.equal(
    await page.locator("#restore-checkpoint-button").isDisabled(),
    false,
  );
  check(
    "Keyboard movement uses Rust and survives a page reload through local persistence",
  );

  await page.locator("#settings-button").click();
  const downloadEvent = page.waitForEvent("download");
  await page.locator("#download-save-button").click();
  const download = await downloadEvent;
  await download.saveAs(resolve(output, "browser-save.json"));
  const save = await readFile(resolve(output, "browser-save.json"), "utf8");
  assert.ok(JSON.parse(save));
  await page.keyboard.press("ArrowLeft");
  assert.notDeepEqual((await snapshot(page)).player, moved);
  await upload(page, "#save-file-input", "restore.json", save);
  await page.waitForFunction(
    (x) => window.tower.state().player.x === x,
    moved.x,
  );
  assert.deepEqual((await snapshot(page)).player, moved);
  check(
    "Exported saves import back into the same Rust engine with identical player state",
  );

  await page.locator("#toast").waitFor({ state: "hidden", timeout: 5000 });
  await inspect(page, enemy.x, enemy.y);
  await page.screenshot({
    path: resolve(output, "desktop.png"),
    fullPage: true,
  });
  assert.ok(await page.locator("#game-canvas").isVisible());
  assert.equal(
    await page.evaluate(
      () => document.documentElement.scrollWidth > innerWidth,
    ),
    false,
  );
  check("Desktop layout fits the viewport and a visual QA screenshot is saved");

  const fixture = structuredClone(original);
  fixture.id = "browser-smoke-campaign";
  fixture.title = "The Testing Tower";
  fixture.start = {
    ...fixture.start,
    floor: 1,
    x: 5,
    y: 5,
    hp: 1000,
    attack: 100,
    defense: 100,
    gold: 10,
    keys: { yellow: 1, blue: 0, red: 0 },
    inventory: ["flying_orb"],
  };
  fixture.events = [];
  fixture.interactions = [];
  fixture.rules.save_requires_hero_orb = false;
  const tiles = Array(121).fill(fixture.rules.empty_tile || 6);
  tiles[5 * 11 + 6] = 1; // Door: assertions verify presentation follows the engine.
  tiles[5 * 11 + 7] = 1; // A second door checks feedback after the only key is spent.
  tiles[5 * 11 + 4] = 21; // A configured conversation next to the hero.
  tiles[4 * 11 + 5] = 61;
  tiles[6 * 11 + 5] = 11;
  fixture.tiles["21"] = {
    ...fixture.tiles["21"],
    name: "A friendly guide",
    text: "The path is yours to choose.",
    offers: [],
    effects: [],
  };
  const upstairs = Array(121).fill(fixture.rules.empty_tile || 6);
  upstairs[5 * 11 + 5] = 12;
  fixture.floors = [
    { id: 1, title: "The Test Chamber", tiles, arrival_down: { x: 5, y: 6 } },
    {
      id: 2,
      title: "The Upper Chamber",
      tiles: upstairs,
      arrival_up: { x: 5, y: 5 },
    },
  ];
  await upload(page, "#campaign-file-input", "testing-campaign.json", fixture);
  await page.waitForFunction(
    () => window.tower.state().campaign_id === "browser-smoke-campaign",
  );
  assert.equal(
    await page.locator("#campaign-label").textContent(),
    fixture.title,
  );
  assert.equal(
    await page.locator("#floor-name").textContent(),
    "The Test Chamber",
  );
  assert.equal(
    await page.locator("#restore-checkpoint-button").isDisabled(),
    true,
  );
  check("A custom JSON campaign is loaded and drives the browser presentation");

  await page.keyboard.press("ArrowRight");
  state = await snapshot(page);
  assert.equal(state.player.keys.yellow, 0);
  assert.equal(state.player.x, 6);
  assert.equal(await page.locator("#yellow-keys").textContent(), "0");
  await page.keyboard.press("ArrowRight");
  assert.equal((await snapshot(page)).player.x, 6);
  assert.match(await page.locator("#toast-text").textContent(), /yellow key/i);
  check(
    "Rejected movement displays Rust’s reason and preserves the hero’s position",
  );
  await page.keyboard.press("ArrowLeft");
  await page.keyboard.press("ArrowLeft");
  await page.locator("#choice-dialog").waitFor({ state: "visible" });
  assert.equal(
    await page.locator("#choice-title").textContent(),
    "A friendly guide",
  );
  await page.locator("#choice-options button").last().click();
  await page.locator("#choice-dialog").waitFor({ state: "hidden" });
  assert.equal((await snapshot(page)).pending_interaction, null);
  check(
    "Key spending and NPC choices render the state changes produced by Rust",
  );

  await page.keyboard.press("ArrowLeft");
  await page.locator("#choice-dialog").waitFor({ state: "visible" });
  await page.keyboard.press("Escape");
  await page.locator("#choice-dialog").waitFor({ state: "hidden" });
  assert.equal((await snapshot(page)).pending_interaction, null);
  await page.keyboard.press("ArrowLeft");
  await page.locator("#choice-dialog").waitFor({ state: "visible" });
  await page.keyboard.press("Enter");
  await page.locator("#choice-dialog").waitFor({ state: "hidden" });
  assert.equal((await snapshot(page)).pending_interaction, null);
  check(
    "Escape dismisses a Rust conversation and Enter activates its focused choice",
  );

  await page.keyboard.press("ArrowDown");
  assert.equal((await snapshot(page)).floor, 2);
  const flyingName = Object.values(fixture.tiles).find(
    (tile) => tile.item === "flying_orb",
  ).name;
  await page
    .getByRole("button", { name: `Use ${flyingName}`, exact: true })
    .click();
  await page.locator("#map-dialog").waitFor({ state: "visible" });
  assert.equal(await page.locator(".map-floor.can-travel").count(), 1);
  await page.locator(".map-floor.can-travel").click();
  assert.equal((await snapshot(page)).floor, 1);
  assert.ok((await snapshot(page)).player.inventory.includes("flying_orb"));
  check(
    "Original Orb of Flying opens its destination picker and delegates travel to Rust",
  );

  const beforeInvalid = await snapshot(page);
  await upload(page, "#campaign-file-input", "invalid-campaign.json", {
    id: "invalid",
    width: 0,
  });
  await page.waitForFunction(() =>
    document.getElementById("toast").classList.contains("error"),
  );
  assert.deepEqual((await snapshot(page)).player, beforeInvalid.player);
  assert.equal((await snapshot(page)).campaign_id, beforeInvalid.campaign_id);
  await upload(
    page,
    "#save-file-input",
    "invalid-save.json",
    "{ definitely not valid JSON",
  );
  await page.waitForFunction(() =>
    document
      .getElementById("toast-text")
      .textContent.includes("Could not import save"),
  );
  assert.deepEqual((await snapshot(page)).player, beforeInvalid.player);
  check(
    "Invalid campaign and save files report errors while preserving the active adventure",
  );
  await page.reload();
  await ready(page);
  assert.equal((await snapshot(page)).campaign_id, fixture.id);
  assert.deepEqual((await snapshot(page)).player, beforeInvalid.player);
  check("Custom campaign and its progress persist together across reloads");
  await page.locator("#settings-button").click();
  await page.locator("#original-campaign-button").click();
  await page.locator("#confirm-dialog").waitFor({ state: "visible" });
  await page.locator("#confirm-restart-button").click();
  assert.equal((await snapshot(page)).campaign_id, original.id);
  assert.equal(
    await page.evaluate(() => localStorage.getItem("tos-rust:campaign:v1")),
    null,
  );
  check(
    "The campaign menu returns to the original tower after a custom adventure",
  );
  await context.close();

  const mobile = await browser.newContext({
    viewport: { width: 390, height: 844 },
    deviceScaleFactor: 1,
    isMobile: true,
    hasTouch: true,
  });
  const mobilePage = await mobile.newPage();
  watch(mobilePage);
  await mobilePage.goto(url);
  await ready(mobilePage);
  assert.equal(
    await mobilePage.evaluate(
      () => document.documentElement.scrollWidth > innerWidth,
    ),
    false,
  );
  assert.ok(await mobilePage.locator(".touch-controls").isVisible());
  const beforeTouch = await snapshot(mobilePage);
  await mobilePage.locator('[data-direction="right"]').tap();
  assert.equal((await snapshot(mobilePage)).player.x, beforeTouch.player.x + 1);
  const mobileEnemy = (await snapshot(mobilePage)).enemies[0];
  const board = await mobilePage.locator("#game-canvas").boundingBox();
  const touchSession = await mobile.newCDPSession(mobilePage);
  const touchX = board.x + board.width / 2,
    touchY = board.y + board.height / 2;
  await touchSession.send("Input.dispatchTouchEvent", {
    type: "touchStart",
    touchPoints: [{ x: touchX, y: touchY }],
  });
  await touchSession.send("Input.dispatchTouchEvent", {
    type: "touchMove",
    touchPoints: [{ x: touchX - 60, y: touchY }],
  });
  await touchSession.send("Input.dispatchTouchEvent", {
    type: "touchEnd",
    touchPoints: [],
  });
  await mobilePage.waitForFunction(
    (x) => window.tower.state().player.x === x,
    beforeTouch.player.x,
  );
  await mobilePage.touchscreen.tap(
    board.x + ((mobileEnemy.x + 0.5) * board.width) / 11,
    board.y + ((mobileEnemy.y + 0.5) * board.height) / 11,
  );
  assert.ok(await mobilePage.locator(".encounter-stats").isVisible());
  await mobilePage.screenshot({
    path: resolve(output, "mobile.png"),
    fullPage: true,
  });
  check(
    "Mobile layout fits at 390px; touch buttons, swipes, and tap inspection work",
  );
  await mobile.close();

  assert.deepEqual(
    failures,
    [],
    "No browser JavaScript errors or failed local requests",
  );
  check(
    "No JavaScript exceptions, console errors, or local HTTP/network failures",
  );
  await writeFile(
    resolve(output, "browser-report.json"),
    JSON.stringify({ url, checks, failures }, null, 2),
  );
  console.log(
    `\n${checks.length} browser integration checks passed. Screenshots: test-results/desktop.png and mobile.png`,
  );
} finally {
  await browser.close();
}
