// script.js

// ─── Theme Toggle ──────────────────────────────────────────
const themeToggle = document.getElementById("theme-toggle");
const themeIcon = document.getElementById("theme-icon");
const themeLabel = document.getElementById("theme-label");

const themes = ["auto", "light", "dark"];
const icons = { auto: "\u25D0", light: "\u2600", dark: "\u263E" };
const labels = { auto: "Auto", light: "Light", dark: "Dark" };

function normalizeTheme(theme) {
  return themes.includes(theme) ? theme : "auto";
}

function getNextTheme(theme) {
  return themes[(themes.indexOf(normalizeTheme(theme)) + 1) % themes.length];
}

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
  return normalizeTheme(readStorage("theme", "auto"));
}

function applyTheme(theme) {
  const normalizedTheme = normalizeTheme(theme);
  const root = document.documentElement;

  if (normalizedTheme === "auto") {
    root.removeAttribute("data-theme");
  } else {
    root.setAttribute("data-theme", normalizedTheme);
  }

  if (themeIcon) {
    themeIcon.textContent = icons[normalizedTheme];
  }

  if (themeLabel) {
    themeLabel.textContent = labels[normalizedTheme];
  }

  if (themeToggle) {
    const nextTheme = getNextTheme(normalizedTheme);

    themeToggle.setAttribute(
      "aria-label",
      `Theme: ${labels[normalizedTheme]}. Activate to switch to ${labels[nextTheme]}.`
    );
  }

  writeStorage("theme", normalizedTheme);
}

// Apply saved theme immediately
applyTheme(getStoredTheme());

themeToggle?.addEventListener("click", () => {
  const current = getStoredTheme();
  applyTheme(getNextTheme(current));
});

// ─── Filtering ─────────────────────────────────────────────
const topicFilterButtons = Array.from(
  document.querySelectorAll("[data-topic-filter]")
);
const statusFilterButtons = Array.from(
  document.querySelectorAll("[data-status-filter]")
);
const clearFiltersButton = document.getElementById("clear-filters");
const sections = Array.from(document.querySelectorAll(".section"));
const collapseToggle = document.getElementById("collapse-toggle");

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

const activeTopicFilters = new Set();
const activeStatusFilters = new Set();
const sectionRecords = sections.map((section) => ({
  section,
  visibleCount: 0,
}));
const rowRecords = [];
const sectionRecordByElement = new Map(
  sectionRecords.map((record) => [record.section, record])
);

function getVisibleSections() {
  return sectionRecords
    .filter((record) => !record.section.classList.contains("filter-empty"))
    .map((record) => record.section);
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

function getRowTopic(row) {
  const tag = row.querySelector(".tag");

  if (!tag) {
    return "";
  }

  return (
    Object.entries(FILTER_TO_TAG_CLASS).find(([, tagClass]) =>
      tag.classList.contains(tagClass)
    )?.[0] || ""
  );
}

function cacheFilterRows() {
  rowRecords.length = 0;

  sectionRecords.forEach((record) => {
    record.visibleCount = 0;
  });

  sections.forEach((section) => {
    const sectionRecord = sectionRecordByElement.get(section);

    section.querySelectorAll("tbody tr").forEach((row) => {
      const status =
        row.querySelector(".status[data-status]")?.dataset.status || "";

      rowRecords.push({
        row,
        section,
        sectionRecord,
        topic: getRowTopic(row),
        status,
      });
    });
  });
}

function hasActiveFilters() {
  return activeTopicFilters.size > 0 || activeStatusFilters.size > 0;
}

function updateTopicButtonStates() {
  topicFilterButtons.forEach((button) => {
    const active = activeTopicFilters.has(button.dataset.topicFilter);

    button.classList.toggle("active", active);
    button.setAttribute("aria-pressed", String(active));
  });
}

function updateStatusButtonStates() {
  statusFilterButtons.forEach((button) => {
    const active = activeStatusFilters.has(button.dataset.statusFilter);

    button.classList.toggle("active", active);
    button.setAttribute("aria-pressed", String(active));
  });
}

function updateClearFiltersState() {
  if (!clearFiltersButton) {
    return;
  }

  clearFiltersButton.disabled = !hasActiveFilters();
}

function toggleSetValue(set, value) {
  if (set.has(value)) {
    set.delete(value);
  } else {
    set.add(value);
  }
}

function rowMatchesFilters(record) {
  const topicMatches =
    activeTopicFilters.size === 0 || activeTopicFilters.has(record.topic);
  const statusMatches =
    activeStatusFilters.size === 0 || activeStatusFilters.has(record.status);

  return topicMatches && statusMatches;
}

function applyFilters({ updateTopics = false, updateStatuses = false } = {}) {
  sectionRecords.forEach((record) => {
    record.visibleCount = 0;
  });

  rowRecords.forEach((record) => {
    const visible = rowMatchesFilters(record);

    record.row.classList.toggle("filter-hidden", !visible);

    if (visible && record.sectionRecord) {
      record.sectionRecord.visibleCount++;
    }
  });

  sectionRecords.forEach((record) => {
    record.section.classList.toggle("filter-empty", record.visibleCount === 0);
  });

  if (updateTopics) {
    updateTopicButtonStates();
  }

  if (updateStatuses) {
    updateStatusButtonStates();
  }

  updateClearFiltersState();
  updateCollapseToggleState();
}

function clearFilters() {
  if (!hasActiveFilters()) {
    return;
  }

  activeTopicFilters.clear();
  activeStatusFilters.clear();
  applyFilters({ updateTopics: true, updateStatuses: true });
}

function initializeFilters() {
  cacheFilterRows();
  updateTopicButtonStates();
  updateStatusButtonStates();
  updateClearFiltersState();

  topicFilterButtons.forEach((button) => {
    button.addEventListener("click", () => {
      toggleSetValue(activeTopicFilters, button.dataset.topicFilter);
      applyFilters({ updateTopics: true });
    });
  });

  statusFilterButtons.forEach((button) => {
    button.addEventListener("click", () => {
      toggleSetValue(activeStatusFilters, button.dataset.statusFilter);
      applyFilters({ updateStatuses: true });
    });
  });

  clearFiltersButton?.addEventListener("click", clearFilters);
  applyFilters();
}

initializeFilters();
initializeSectionCollapse();

// ─── Scroll to Top ─────────────────────────────────────────
const scrollTopBtn = document.getElementById("scroll-top");

if (scrollTopBtn) {
  window.addEventListener("scroll", () => {
    const isVisible = window.scrollY > 400;

    scrollTopBtn.classList.toggle("visible", isVisible);
    scrollTopBtn.hidden = !isVisible;
  });

  scrollTopBtn.addEventListener("click", () => {
    window.scrollTo({ top: 0, behavior: "smooth" });
  });
}
