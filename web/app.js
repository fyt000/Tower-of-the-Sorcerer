// Host boot only: all application behavior is shared Rust.
import init, { WebHandle } from './pkg/tos_ui.js';
const loading = document.getElementById('loading');
try {
  await init();
  const handle = new WebHandle();
  await handle.start(document.getElementById('game-canvas'));
  window.tower = handle;
  loading.hidden = true;
  document.getElementById('game-canvas').focus();
} catch (error) {
  loading.querySelector('p').textContent = `Could not start: ${error.message || error}`;
  console.error(error);
}
