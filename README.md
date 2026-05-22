# Financial Orchestrator

<p align="center">
  <img src="https://raw.githubusercontent.com/Archsec-Emman/Financial-Orchestrator/master/financial%20orch.png" alt="FINANCIAL ORCHESTRATOR Banner" width="800">
</p>


[![Language](https://img.shields.io/badge/C%2B%2B-20-blue)](https://isocpp.org/)
[![Qt](https://img.shields.io/badge/Qt-6.8.3-brightgreen)](https://www.qt.io/)
[![Python](https://img.shields.io/badge/Python-3.11.9-yellow)](https://www.python.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Platform](https://img.shields.io/badge/platform-windows%20%7C%20linux%20%7C%20macos-lightgrey)](https://github.com/Archsec-Emman/Financial-Orchestrator)

**Your Thinking is the Only Limit. The Data Isn't.**  
A state‑of‑the‑art financial intelligence platform with institutional-grade analytics, AI automation, and unlimited data connectivity. Completely free and open‑source.

---

## 📖 Overview

Financial Orchestrator is a pure‑native C++20 desktop application. It uses **Qt6** for UI and rendering while embedding **Python 3.11.9** for analytics, delivering Bloomberg‑class performance in a single binary. It is designed for retail investors, quantitative analysts, researchers, and financial professionals who require deep analytical tools without proprietary data dependencies.

---

## ✨ Features

### 📊 Multi‑Asset Analytics
DCF models, portfolio optimization, risk metrics (VaR, Sharpe), derivatives pricing across equity, fixed income, derivatives, portfolio, and alternatives.

### 🤖 AI Agents
37 agents across Trader/Investor frameworks (Buffett, Graham, Lynch, Munger, Klarman, Marks, …), plus Economic and Geopolitics frameworks. Supports local LLMs and multi‑provider integrations (OpenAI, Anthropic, Gemini, Groq, DeepSeek, MiniMax, OpenRouter, Ollama).

### 🔌 100+ Data Connectors
Connects to DBnomics, Polygon, Kraken, Yahoo Finance, FRED, IMF, World Bank, AkShare, government APIs, and optional alternative‑data overlays.

### 💹 Real‑Time Trading
Crypto (Kraken/HyperLiquid WebSocket), equity, algo trading, paper trading engine, and 16 broker integrations.

### 📈 QuantLib Suite
18 quantitative analysis modules — pricing, risk, stochastic, volatility, fixed income.

### 🌍 Global Intelligence
Maritime tracking, geopolitical analysis, relationship mapping, satellite data.

### 🧩 Visual Workflows
Node editor for automation pipelines and MCP tool integration.

### 🧠 AI Quant Lab
ML models, factor discovery, HFT, reinforcement learning trading.

---

## 🚀 Installation

### Option 1 — Download Installer (Recommended)
Download the latest installer for your platform from the [Releases](https://github.com/Archsec-Emman/Financial-Orchestrator/releases) page.

| Platform | Download |
|----------|----------|
| **Windows x64** | [FinancialOrchestrator‑Windows‑x64‑setup.exe](https://github.com/Archsec-Emman/Financial-Orchestrator/releases/download/v4.0.3/FinancialOrchestrator-4.0.3-windows-x64-setup.exe) |
| **Linux x64** | [FinancialOrchestrator‑Linux‑x64.run](https://github.com/Archsec-Emman/Financial-Orchestrator/releases/download/v4.0.3/FinancialOrchestrator-4.0.3-linux-x64-setup.run) |
| **macOS Apple Silicon** | [FinancialOrchestrator‑macOS‑arm64.dmg](https://github.com/Archsec-Emman/Financial-Orchestrator/releases/download/v4.0.3/FinancialOrchestrator-4.0.3-macos-arm64-setup.dmg) |

### Option 2 — Quick Start (One‑Click Build)
Clone and run the setup script — it installs all dependencies and builds the app automatically:
```bash
# Linux / macOS
git clone https://github.com/Archsec-Emman/Financial-Orchestrator.git
cd Financial-Orchestrator
chmod +x setup.sh && ./setup.sh
```
The script handles: compiler check, CMake, Qt6, Python, build, and launch.

> **Windows:** No setup script — use the manual build steps in Option 4 below.

### Option 3 — Docker (CI / Developer Environments)
> **Note:** Docker is intended for CI/CD testing and development environments only. Linux with X11 is required; Windows and macOS are not supported.
```bash
# Build from source (Linux + X11 required)
git clone https://github.com/Archsec-Emman/Financial-Orchestrator.git
cd Financial-Orchestrator
docker build -t fiorch-terminal .
docker run --rm -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix fiorch-terminal
```

### Option 4 — Build from Source (Manual)
> **Versions are pinned.** Use the exact versions below. Newer or older versions are unsupported and may fail to build.

#### Prerequisites (exact versions)
| Tool | Pinned Version |
|------|----------------|
| **CMake** | 3.27.7 |
| **Ninja** | 1.11.1 |
| **C++ compiler** | MSVC 19.38 (VS 2022 17.8) / GCC 12.3 / Apple Clang 15.0 (Xcode 15.2) |
| **Qt** | 6.8.3 |
| **Python** | 3.11.9 |

#### Install Qt 6.8.3
- **Windows:** Qt Online Installer → select `Qt 6.8.3 > MSVC 2022 64‑bit` (install path: `C:/Qt/6.8.3/msvc2022_64`)
- **Linux:** Qt Online Installer → `Qt 6.8.3 > Desktop gcc 64‑bit` (install path: `~/Qt/6.8.3/gcc_64`)
- **macOS:** Qt Online Installer → `Qt 6.8.3 > macOS` (install path: `~/Qt/6.8.3/macos`)

#### Build (using CMake presets — recommended)
```bash
git clone https://github.com/Archsec-Emman/Financial-Orchestrator.git
cd Financial-Orchestrator/fiorch-qt

# Configure (one‑time, or after CMakeLists.txt changes)
cmake --preset win-release   # Windows
cmake --preset linux-release # Linux
cmake --preset macos-release # macOS

# Build
cmake --build build/win-release    # Windows
cmake --build build/linux-release  # Linux
cmake --build build/macos-release  # macOS
```

#### Run
```bash
# Linux / macOS (preset build)
./build/*/FinancialOrchestrator

# Windows (preset build)
.\build\*\FinancialOrchestrator.exe
```

#### Troubleshooting
1. **"Could not find Qt6 6.8.3"** — verify `CMAKE_PREFIX_PATH` points to the Qt 6.8.3 install, not 6.5/6.6/6.8.
2. **MSVC version error** — use VS 2022 17.8+ (MSVC 19.38+). Check with `cl /?`.
3. **Need to unblock with a different Qt minor?** Pass `-DFINCEPT_ALLOW_QT_DRIFT=ON` (local testing only — never for releases or CI).
4. Clean rebuild: delete `build/*/` and re‑run configure.

---

## 🧑‍💻 Usage

After launching the application, you can:
- **Connect to data sources** via the 100+ built‑in connectors.
- **Run AI agents** to generate trade ideas and portfolio recommendations.
- **Execute paper trades** or connect to any of the 16 supported brokers for real trading.
- **Build visual pipelines** using the node editor for automation.
- **Analyze quantitative models** using the QuantLib Suite or the AI Quant Lab.

---

## 📁 Project Structure

```
Financial-Orchestrator/
├── fiorch-qt/               # Main C++20 / Qt6 application source
├── docs/                    # Documentation (ADRs, guides)
├── .github/                 # GitHub workflows and templates
├── images/                  # Assets and branding
├── setup.sh                 # One‑click build script (Linux/macOS)
├── Dockerfile               # Docker build definition
├── LICENSE                  # MIT License
└── README.md                # This file
```

---

## 🤝 Contributing

We welcome contributions: new data connectors, AI agents, analytics modules, C++ screens, and documentation. Please review the contributing guides:
- [General Contributing Guide](https://github.com/Archsec-Emman/Financial-Orchestrator/blob/master/docs/CONTRIBUTING.md)
- [C++ Contributing Guide](https://github.com/Archsec-Emman/Financial-Orchestrator/blob/master/fiorch-qt/CONTRIBUTING.md)
- [Python Contributor Guide](https://github.com/Archsec-Emman/Financial-Orchestrator/blob/master/docs/PYTHON_CONTRIBUTOR_GUIDE.md)

**Report Bugs:** [GitHub Issues](https://github.com/Archsec-Emman/Financial-Orchestrator/issues)  
**Request Features:** [Discussions](https://github.com/Archsec-Emman/Financial-Orchestrator/discussions)

---

## 📄 License

This project is licensed under the **MIT License** – see the [LICENSE](LICENSE) file for details.

---

## 📬 Contact & Support

- **GitHub Discussions:** [https://github.com/Archsec-Emman/Financial-Orchestrator/discussions](https://github.com/Archsec-Emman/Financial-Orchestrator/discussions)
- **Author:** [Archsec-Emman](https://github.com/Archsec-Emman)

---

## 🚧 Roadmap

| Timeline | Milestone |
|----------|-----------|
| **Shipped** | Real‑time streaming, 16 broker integrations, multi‑account trading, PIN authentication, theme system |
| **Q2 2026** | Options strategy builder, multi‑portfolio management, 50+ AI agents |
| **Q3 2026** | Programmatic API, ML training UI, institutional features |
| **Future** | Mobile companion, cloud sync, community marketplace |

---

*If you find Financial Orchestrator valuable for your research or trading, please consider starring the repository.* ⭐

---

**Your Thinking is the Only Limit. The Data Isn't.**
```
