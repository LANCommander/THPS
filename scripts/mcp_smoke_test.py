#!/usr/bin/env python3
"""
End-to-end GhidraMCP chain check for the THPS project.

Talks to the GhidraMCP REST API directly (the same API the stdio bridge in .mcp.json wraps),
served by either the Ghidra GUI plugin or scripts\start_headless_mcp.ps1, on 127.0.0.1:8090.

  python scripts\mcp_smoke_test.py                      # decompiles a known demo function
  python scripts\mcp_smoke_test.py 0x800181b8           # decompile a specific address

Exit code 0 on success.
"""
import sys
import json
import urllib.request

BASE = "http://127.0.0.1:8090"
# GetFaceFlags__FP9SLineInfo in PROSKATE.EXE (from MAIN.SYM)
DEFAULT_ADDR = "0x800181b8"


def get(path, **params):
    q = "&".join(f"{k}={v}" for k, v in params.items())
    url = f"{BASE}/{path}" + (f"?{q}" if q else "")
    with urllib.request.urlopen(url, timeout=15) as r:
        return r.read().decode("utf-8", "replace")


def main():
    addr = sys.argv[1] if len(sys.argv) > 1 else DEFAULT_ADDR
    try:
        print("check_connection:", get("check_connection").strip())
    except Exception as e:
        print("FAIL: cannot reach GhidraMCP on", BASE, "->", e)
        print("Start it with scripts\\start_headless_mcp.ps1 or open the project in Ghidra.")
        sys.exit(2)
    try:
        dec = get("decompile_function", address=addr)
        print(f"--- decompile {addr} ---")
        print(dec[:1200])
        ok = "{" in dec and "}" in dec
        print("\nRESULT:", "OK" if ok else "no body returned")
        sys.exit(0 if ok else 1)
    except Exception as e:
        print("FAIL: decompile_function ->", e)
        sys.exit(1)


if __name__ == "__main__":
    main()
