#!/usr/bin/env sh
set -e

PROJECT_ROOT="$(cd "$(dirname "$0")/.." && pwd)"

echo "Running clang-format on all c++ files..."

find "$PROJECT_ROOT/src" \
  -type f \( -name "*.cpp" -o -name "*.hpp" \) \
  -print \
  -exec clang-format -i {} + 

echo "clang-format completed successfully ✓"  
