# ============================================================================
# Financial Orchestrator - Strategy Engine
# Licensed under the MIT License.
# https://github.com/Archsec-Emman/FinancialOrchestrator
#
# Strategy ID: FCT-F9837218
# Category: Universe Selection
# Description: Example algorithm using the asynchronous universe selection functionality
# Compatibility: Backtesting | Paper Trading | Live Deployment
# ============================================================================
from AlgorithmImports import *
from FundamentalRegressionAlgorithm import FundamentalRegressionAlgorithm

### <summary>
### Example algorithm using the asynchronous universe selection functionality
### </summary>
class AsynchronousUniverseRegressionAlgorithm(FundamentalRegressionAlgorithm):

    def initialize(self):
        super().initialize()
        self.universe_settings.asynchronous = True
