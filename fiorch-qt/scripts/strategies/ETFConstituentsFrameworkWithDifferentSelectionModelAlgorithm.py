# ============================================================================
# Financial Orchestrator - Strategy Engine
# Licensed under the MIT License.
# https://github.com/Archsec-Emman/FinancialOrchestrator
#
# Strategy ID: FCT-A7B56E18
# Category: ETF
# Description: Demonstration of using the ETFConstituentsUniverseSelectionModel with simple ticker
# Compatibility: Backtesting | Paper Trading | Live Deployment
# ============================================================================
from AlgorithmImports import *
from Selection.ETFConstituentsUniverseSelectionModel import *
from ETFConstituentsFrameworkAlgorithm import ETFConstituentsFrameworkAlgorithm

### <summary>
### Demonstration of using the ETFConstituentsUniverseSelectionModel with simple ticker
### </summary>
class ETFConstituentsFrameworkWithDifferentSelectionModelAlgorithm(ETFConstituentsFrameworkAlgorithm):

    def initialize(self):
        super().initialize()
        
        self.set_universe_selection(ETFConstituentsUniverseSelectionModel("SPY", self.universe_settings, self.etf_constituents_filter))
