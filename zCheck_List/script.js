// script.js

// ─── Theme Toggle ──────────────────────────────────────────
const themeToggle = document.getElementById("theme-toggle");
const themeIcon = document.getElementById("theme-icon");
const themeLabel = document.getElementById("theme-label");

const themes = ["auto", "light", "dark"];
const icons = { auto: "\u25D0", light: "\u2600", dark: "\u263E" };
const labels = { auto: "Auto", light: "Light", dark: "Dark" };

function getStoredTheme() {
  return localStorage.getItem("theme") || "auto";
}

function applyTheme(theme) {
  const root = document.documentElement;

  if (theme === "auto") {
    root.removeAttribute("data-theme");
  } else {
    root.setAttribute("data-theme", theme);
  }

  themeIcon.textContent = icons[theme];
  themeLabel.textContent = labels[theme];
  localStorage.setItem("theme", theme);
}

// Apply saved theme immediately
applyTheme(getStoredTheme());

themeToggle.addEventListener("click", () => {
  const current = getStoredTheme();
  const next = themes[(themes.indexOf(current) + 1) % themes.length];
  applyTheme(next);
});

// ─── Priority Nav (progressive collapse) ──────────────────
const navBar = document.querySelector(".nav-bar");
const navLinks = document.getElementById("nav-links");
const navOverflow = document.getElementById("nav-overflow");
const hamburger = document.getElementById("nav-hamburger");
const allNavItems = Array.from(navLinks.querySelectorAll("a[data-nav]"));

function updateNav() {
  // 1. Show all links in the main bar to measure
  allNavItems.forEach((a) => {
    if (a.parentElement === navOverflow) {
      navLinks.appendChild(a);
    }
    a.hidden = false;
  });

  // 2. Calculate available space
  const barWidth = navBar.clientWidth;
  const hamburgerWidth = 44; // approximate width of hamburger + gap
  const themeWidth = themeToggle.offsetWidth + 8;
  const available = barWidth - themeWidth - 32; // 32 for padding

  // 3. Measure each link and find which ones fit
  let used = 0;
  let overflowed = false;
  const visible = [];
  const hidden = [];

  for (const link of allNavItems) {
    const linkWidth = link.offsetWidth + 4; // 4 for gap
    if (!overflowed && used + linkWidth <= available - (overflowed ? 0 : hamburgerWidth)) {
      used += linkWidth;
      visible.push(link);
    } else {
      overflowed = true;
      // Recheck: once we know we need the hamburger, account for its width
      if (hidden.length === 0 && used + linkWidth > available - hamburgerWidth) {
        // May need to pop the last visible to make room for hamburger
        while (visible.length > 0 && used + hamburgerWidth > available) {
          const popped = visible.pop();
          used -= popped.offsetWidth + 4;
          hidden.unshift(popped);
        }
      }
      hidden.push(link);
    }
  }

  // 4. Hide overflowed links from bar, move to overflow dropdown
  hidden.forEach((a) => {
    a.hidden = true;
    navOverflow.appendChild(a);
    a.hidden = false;
  });

  // 5. Toggle hamburger and overflow visibility
  if (hidden.length > 0) {
    hamburger.hidden = false;
  } else {
    hamburger.hidden = true;
    hamburger.classList.remove("active");
    navOverflow.hidden = true;
  }
}

hamburger.addEventListener("click", () => {
  hamburger.classList.toggle("active");
  navOverflow.hidden = !navOverflow.hidden;
});

// Close overflow when a link is clicked
document.addEventListener("click", (e) => {
  if (e.target.matches(".nav-overflow a")) {
    hamburger.classList.remove("active");
    navOverflow.hidden = true;
  }
});

// Close overflow when clicking outside nav
document.addEventListener("click", (e) => {
  if (!e.target.closest(".nav") && !navOverflow.hidden) {
    hamburger.classList.remove("active");
    navOverflow.hidden = true;
  }
});

// Run on load and resize
const ro = new ResizeObserver(() => updateNav());
ro.observe(navBar);
updateNav();

// ─── Tag Filtering ─────────────────────────────────────────
const filterBtns = document.querySelectorAll(".filter-btn");
const sections = document.querySelectorAll(".section");

// Map filter values to tag class substrings
const filterToClass = {
  mit: "tag--mit",
  clrs: "tag--clrs",
  udemy: "tag--udemy",
  ctci: "tag--ctci",
  leetcode: "tag--leetcode",
  cpp: "tag--cpp",
  project: "tag--project",
  array: "tag--array",
  testing: "tag--testing",
  algorithm: "tag--algorithm",
};

let activeFilter = "all";

function applyFilter(filter) {
  activeFilter = filter;

  // Update button states
  filterBtns.forEach((btn) => {
    btn.classList.toggle("active", btn.dataset.filter === filter);
  });

  // Filter rows
  sections.forEach((section) => {
    const rows = section.querySelectorAll("tbody tr");
    let visibleCount = 0;

    rows.forEach((row) => {
      if (filter === "all") {
        row.classList.remove("filter-hidden");
        visibleCount++;
      } else {
        const tag = row.querySelector(".tag");
        const matches = tag && tag.classList.contains(filterToClass[filter]);
        row.classList.toggle("filter-hidden", !matches);
        if (matches) visibleCount++;
      }
    });

    // Hide entire section if no visible rows
    section.classList.toggle("filter-empty", visibleCount === 0);
  });
}

filterBtns.forEach((btn) => {
  btn.addEventListener("click", () => {
    if (btn.dataset.filter === activeFilter) {
      applyFilter("all");
    } else {
      applyFilter(btn.dataset.filter);
    }
  });
});

// ─── Scroll to Top ─────────────────────────────────────────
const scrollTopBtn = document.getElementById("scroll-top");

window.addEventListener("scroll", () => {
  scrollTopBtn.classList.toggle("visible", window.scrollY > 400);
});

scrollTopBtn.addEventListener("click", () => {
  window.scrollTo({ top: 0, behavior: "smooth" });
});

// ─── Checkbox Persistence ──────────────────────────────────
const checkboxes = document.querySelectorAll('input[type="checkbox"]');

function loadState() {
  checkboxes.forEach((checkbox) => {
    const savedState = localStorage.getItem(checkbox.id);
    if (savedState !== null) {
      checkbox.checked = savedState === "true";
    }
  });
}

function saveState(event) {
  localStorage.setItem(event.target.id, event.target.checked);
}

checkboxes.forEach((checkbox) => {
  checkbox.addEventListener("change", saveState);
});

document.addEventListener("DOMContentLoaded", loadState);
