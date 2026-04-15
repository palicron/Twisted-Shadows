# Twisted Shadows 🌑✨

**A technical prototype focusing on dual-character coordination and decoupled UI architecture.**

---

## 📋 Project Overview
**Twisted Shadows** is a puzzle-platformer where the core mechanic revolves around "Soul Splitting." Players must manifest and control a shadow/magical duplicate to reach inaccessible locations and solve environmental puzzles.

* **Status:** Early Development (Core Mechanics & Game Flow)
* **Objective:** Complete bite-sized, logic-based levels by utilizing both the player and the shadow.
* **Current Milestone:** Establishing a robust "Game Flow" and refining the character-swapping architecture.

---

## 🛠️ Technical Stack
| Category | Technology |
| :--- | :--- |
| **Engine** | Unreal Engine 5 |
| **Language** | C++ (Vanilla / Clean Code focus) |
| **Architecture** | MVVM (Model-View-ViewModel) for UI |
| **Scripting** | Hybrid (C++ for Core Logic / Blueprints for Tuning) |

---

## 🚀 Key Systems & Implementation

### 👥 Dual-Entity Control System
Implemented a decoupled control system that allows for seamless switching between the primary player character and their magical shadow.
* **Input Handling:** Cleanly separated player input logic to handle state changes when swapping control.
* **Shadow Logic:** Developed the foundation for "Shadow Projection" mechanics, ensuring the duplicate interacts correctly with puzzle triggers.

### 🖼️ UI Architecture (MVVM)
Utilized the **MVVM (Model-View-ViewModel)** pattern for all widgets and HUD elements to ensure a clean separation between gameplay data and visual representation.
* **Data Binding:** Leveraged the MVVM plugin to bind character stats (mana/cooldowns) directly to the UI without tight coupling.
* **Performance:** Reduced UI overhead by avoiding traditional "tick-based" polling.

### 🧩 Puzzle & Interaction Framework
Created a modular interaction system to handle various puzzle elements.
* **Interacts:** Standardized interfaces for levers, pressure plates, and magical gates.
* **State Management:** Developed a game flow controller to track puzzle completion and level transitions.

---

## 🕹️ Controls (Current Build)
* **WASD:** Movement

---

## 📈 Roadmap & Versioning
* **Phase 1 (Current):** Refine core character movement and "Split" mechanic.
* **Phase 2:** Implement advanced environmental logic (light/shadow puzzles).
* **Phase 3:** Full UI implementation using the MVVM pattern.

> [!NOTE]
> This project is a work-in-progress focused on **scalable systems** and **clean C++ architecture**.

---

