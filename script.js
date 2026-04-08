// script.js

// ─── Theme Toggle ──────────────────────────────────────────
const themeToggle = document.getElementById("theme-toggle");
const themeIcon = document.getElementById("theme-icon");
const themeLabel = document.getElementById("theme-label");

const themes = ["auto", "light", "dark"];
const icons = { auto: "\u25D0", light: "\u2600", dark: "\u263E" };
const labels = { auto: "Auto", light: "Light", dark: "Dark" };

function readStorage(key, fallback = null) {
  try {
    const value = localStorage.getItem(key);
    return value === null ? fallback : value;
  } catch {
    return fallback;
  }
}

function writeStorage(key, value) {
  try {
    localStorage.setItem(key, value);
  } catch {
    // Ignore storage failures so the UI remains usable.
  }
}

function getStoredTheme() {
  return readStorage("theme", "auto");
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
  themeToggle.setAttribute(
    "aria-label",
    `Theme: ${labels[theme]}. Activate to switch to ${labels[themes[(themes.indexOf(theme) + 1) % themes.length]]}.`
  );
  writeStorage("theme", theme);
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
    hamburger.setAttribute("aria-expanded", "false");
  }
}

hamburger.addEventListener("click", () => {
  const expanded = hamburger.classList.toggle("active");
  navOverflow.hidden = !expanded;
  hamburger.setAttribute("aria-expanded", String(expanded));
});

// Close overflow when a link is clicked
document.addEventListener("click", (e) => {
  if (e.target.matches(".nav-overflow a")) {
    hamburger.classList.remove("active");
    navOverflow.hidden = true;
    hamburger.setAttribute("aria-expanded", "false");
  }
});

// Close overflow when clicking outside nav
document.addEventListener("click", (e) => {
  if (!e.target.closest(".nav") && !navOverflow.hidden) {
    hamburger.classList.remove("active");
    navOverflow.hidden = true;
    hamburger.setAttribute("aria-expanded", "false");
  }
});

// Run on load and resize
const ro = new ResizeObserver(() => updateNav());
ro.observe(navBar);
updateNav();

// ─── Tag Filtering ─────────────────────────────────────────
const filterButtons = Array.from(document.querySelectorAll(".filter-btn"));
const sections = Array.from(document.querySelectorAll(".section"));
const collapseToggle = document.getElementById("collapse-toggle");

// Map filter values to tag class substrings
const FILTER_TO_TAG_CLASS = {
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
const SECTION_COLLAPSE_STORAGE_PREFIX = "section-collapsed:";

let activeFilter = "all";

function getVisibleSections() {
  return sections.filter((section) => !section.classList.contains("filter-empty"));
}

function getSectionHeader(section) {
  return section.querySelector(".section-header");
}

function getSectionTitle(section) {
  return getSectionHeader(section)?.querySelector(".section-title")?.textContent?.trim() || "section";
}

function getSectionStorageKey(section) {
  return `${SECTION_COLLAPSE_STORAGE_PREFIX}${section.id}`;
}

function isSectionCollapsed(section) {
  return section.classList.contains("collapsed");
}

function syncSectionHeaderState(section, collapsed) {
  const header = getSectionHeader(section);
  const title = getSectionTitle(section);

  if (!header) {
    return;
  }

  header.setAttribute("aria-expanded", String(!collapsed));
  header.setAttribute("aria-controls", `${section.id}-table`);
  header.setAttribute("aria-label", `${collapsed ? "Expand" : "Collapse"} ${title}`);
}

function setSectionCollapsed(section, collapsed, { persist = true } = {}) {
  section.classList.toggle("collapsed", collapsed);
  syncSectionHeaderState(section, collapsed);

  if (persist && section.id) {
    writeStorage(getSectionStorageKey(section), String(collapsed));
  }
}

function updateCollapseToggleState() {
  if (!collapseToggle) {
    return;
  }

  const visibleSections = getVisibleSections();
  const hasVisibleSections = visibleSections.length > 0;
  const shouldExpandAll =
    hasVisibleSections && visibleSections.every((section) => isSectionCollapsed(section));

  collapseToggle.disabled = !hasVisibleSections;
  collapseToggle.textContent = shouldExpandAll ? "Expand All" : "Collapse All";
  collapseToggle.setAttribute(
    "aria-label",
    shouldExpandAll ? "Expand all visible sections" : "Collapse all visible sections"
  );
}

function initializeSectionCollapse() {
  sections.forEach((section) => {
    const header = getSectionHeader(section);

    if (!header) {
      return;
    }

    const toggleSection = () => {
      setSectionCollapsed(section, !isSectionCollapsed(section));
      updateCollapseToggleState();
    };

    header.addEventListener("click", toggleSection);

    const table = section.querySelector("table");
    if (table && section.id) {
      table.id = `${section.id}-table`;
    }

    const savedState = readStorage(getSectionStorageKey(section));

    if (savedState !== null) {
      setSectionCollapsed(section, savedState === "true", { persist: false });
    } else {
      setSectionCollapsed(section, false, { persist: false });
    }
  });

  if (collapseToggle) {
    collapseToggle.addEventListener("click", () => {
      const visibleSections = getVisibleSections();

      if (visibleSections.length === 0) {
        return;
      }

      const shouldCollapse = visibleSections.some(
        (section) => !isSectionCollapsed(section)
      );

      visibleSections.forEach((section) => {
        setSectionCollapsed(section, shouldCollapse);
      });

      updateCollapseToggleState();
    });
  }

  updateCollapseToggleState();
}

function applyFilter(filter) {
  activeFilter = filter;

  // Update button states
  filterButtons.forEach((btn) => {
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
        const matches = tag && tag.classList.contains(FILTER_TO_TAG_CLASS[filter]);
        row.classList.toggle("filter-hidden", !matches);
        if (matches) visibleCount++;
      }
    });

    // Hide entire section if no visible rows
    section.classList.toggle("filter-empty", visibleCount === 0);
  });

  updateCollapseToggleState();
}

function initializeFilters() {
  filterButtons.forEach((btn) => {
    btn.addEventListener("click", () => {
      if (btn.dataset.filter === activeFilter) {
        applyFilter("all");
      } else {
        applyFilter(btn.dataset.filter);
      }
    });
  });
}

initializeFilters();
initializeSectionCollapse();

// ─── Scroll to Top ─────────────────────────────────────────
const scrollTopBtn = document.getElementById("scroll-top");

window.addEventListener("scroll", () => {
  const isVisible = window.scrollY > 400;
  scrollTopBtn.classList.toggle("visible", isVisible);
  scrollTopBtn.hidden = !isVisible;
});

scrollTopBtn.addEventListener("click", () => {
  window.scrollTo({ top: 0, behavior: "smooth" });
});

// ─── Checkbox Persistence ──────────────────────────────────
const checkboxes = Array.from(document.querySelectorAll('input[type="checkbox"]'));

function initializeCheckboxes() {
  checkboxes.forEach((checkbox) => {
    const savedState = readStorage(checkbox.id);

    if (savedState !== null) {
      checkbox.checked = savedState === "true";
    }

    checkbox.addEventListener("change", (event) => {
      writeStorage(event.target.id, event.target.checked);
    });
  });
}

initializeCheckboxes();
