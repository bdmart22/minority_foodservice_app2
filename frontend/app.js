let lang = "en";

document.getElementById("lang-toggle").addEventListener("click", () => {
  lang = lang === "en" ? "es" : "en";
  updateLanguage();
  loadMenu();
});

function updateLanguage() {
  document.getElementById("lang-toggle").textContent = lang === "en" ? "Español" : "English";
  document.getElementById("menu-title").textContent = lang === "en" ? "Menu Items" : "Menú";
  document.getElementById("updates-title").textContent = lang === "en" ? "Real-Time Order Updates" : "Actualizaciones en Tiempo Real";
}

async function loadMenu() {
  const res = await fetch("http://localhost:8080/menu");
  const items = await res.json();

  const container = document.getElementById("menu");
  container.innerHTML = "";
  items.forEach(item => {
    const div = document.createElement("div");
    div.textContent = `${item.name} — $${item.price}`;
    container.appendChild(div);
  });
}

// WebSocket for live updates
const ws = new WebSocket("ws://localhost:8080/ws");
ws.onmessage = (event) => {
  const updates = document.getElementById("updates");
  const msg = document.createElement("div");
  msg.textContent = "📦 " + event.data;
  updates.appendChild(msg);
};

// Load menu on startup
loadMenu();
