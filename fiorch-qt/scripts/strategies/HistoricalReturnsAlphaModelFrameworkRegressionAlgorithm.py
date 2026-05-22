# ============================================================================
# Financial Orchestrator - Strategy Engine
# Licensed under the MIT License.
# https://github.com/Archsec-Emman/FinancialOrchestrator
#
# Strategy ID: FCT-649F439A
# Category: Alpha Model
# Description: Regression algorithm to assert the behavior of <see cref="HistoricalReturnsAlphaModel"/>
# Compatibility: Backtesting | Paper Trading | Live Deployment
# ============================================================================
from AlgorithmImports import *
from BaseFrameworkRegressionAlgorithm import BaseFrameworkRegressionAlgorithm
from Alphas.HistoricalReturnsAlphaModel import HistoricalReturnsAlphaModel

### <summary>
### Regression algorithm to assert the behavior of <see cref="HistoricalReturnsAlphaModel"/>.
### </summary>
class HistoricalReturnsAlphaModelFrameworkRegressionAlgorithm(BaseFrameworkRegressionAlgorithm):

    def initialize(self):
        super().initialize()
        self.set_alpha(HistoricalReturnsAlphaModel())

    def on_end_of_algorithm(self):
        expected = 78
        if self.insights.total_count != expected:
            raise Exception(f"The total number of insights should be {expected}. Actual: {self.insights.total_count}")
