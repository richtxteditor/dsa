const plans = document.querySelectorAll(".tab-content");
const buttons = document.querySelectorAll(".tab-button");
const checkboxes = document.querySelectorAll('input[type="checkbox"]');

function showPlan(planId) {
  // Hide all plans, remove active class from buttons
  plans.forEach((plan) => plan.classList.remove("active"));
  buttons.forEach((button) => button.classList.remove("active"));

  // Show the selected plan and set its button to active
  document.getElementById(planId).classList.add("active");
  document
    .querySelector(`.tab-button[onclick="showPlan('${planId}')"]`)
    .classList.add("active");
}

// --- State Persistence ---

// Load state from localStorage when the page loads
function loadState() {
  checkboxes.forEach((checkbox) => {
    const isChecked = localStorage.getItem(checkbox.id) === "true";
    checkbox.checked = isChecked;
  });
}

// Save state to localStorage whenever a checkbox is changed
function saveState(event) {
  localStorage.setItem(event.target.id, event.target.checked);
}

// Attach event listeners
checkboxes.forEach((checkbox) => {
  checkbox.addEventListener("change", saveState);
});

// Initial load
document.addEventListener("DOMContentLoaded", loadState);
