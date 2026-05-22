#!/usr/bin/env python3
"""
"""

import sys
import json
from pathlib import Path

# Add base directory to path
BASE_DIR = Path(__file__).resolve().parent.parent / "base"
sys.path.insert(0, str(BASE_DIR))



def run_fiorch_strategy(strategy_id: str, params_dict: dict) -> dict:
    """

    Args:
        params_dict: Backtest parameters

    Returns:
        dict: Backtesting.py-format results
    """
    result = runner.execute_strategy(strategy_id, params_dict)

    if not result.get('success'):
        return result

    # Convert to Backtesting.py format (already compatible)
    return result


if __name__ == '__main__':
    if len(sys.argv) < 3:
        print(json.dumps({
            'success': False,
            'error': 'Usage: btp_fiorch_bridge.py <strategy_id> <params_json>'
        }))
        sys.exit(1)

    strategy_id = sys.argv[1]
    params = json.loads(sys.argv[2])

    result = run_fiorch_strategy(strategy_id, params)
    print(json.dumps(result, indent=2))
