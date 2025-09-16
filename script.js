// script.js

const checkboxes = document.querySelectorAll('input[type="checkbox"]');

// --- State Persistence ---

// Load state from localStorage when the page loads
function loadState() {
  checkboxes.forEach((checkbox) => {
    // Check if an item exists in localStorage for this checkbox's ID
    const savedState = localStorage.getItem(checkbox.id);
    if (savedState !== null) {
      checkbox.checked = savedState === "true";
    }
  });
}

// Save state to localStorage whenever a checkbox is changed
function saveState(event) {
  localStorage.setItem(event.target.id, event.target.checked);
}

// --- Attach Event Listeners ---
checkboxes.forEach((checkbox) => {
  checkbox.addEventListener("change", saveState);
});

// Initial load when the page content is ready
document.addEventListener("DOMContentLoaded", loadState);
