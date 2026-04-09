const { test, expect } = require("@playwright/test");

test("checkboxes stay editable on localhost", async ({ page }) => {
  await page.goto("/");

  const checkbox = page.locator("#dsa-task-3");

  await expect(checkbox).toBeEnabled();

  await checkbox.check();
  await expect(checkbox).toBeChecked();
});

test("checkboxes are locked on non-local hosts", async ({ page }) => {
  await page.goto("http://dsa-test.invalid:4173/");

  const checkbox = page.locator("#dsa-task-3");

  await expect(checkbox).toBeDisabled();
  await expect(checkbox).toHaveAttribute(
    "title",
    "Checkboxes are editable only in a local copy of this site."
  );
});
