<#
Serve one program from ghidra\THPS.gpr over the GhidraMCP REST API (127.0.0.1:8090),
so the `ghidra` MCP server in .mcp.json works without the Ghidra GUI open.

  .\scripts\start_headless_mcp.ps1                       # serves /PROSKATE.EXE (the demo)
  .\scripts\start_headless_mcp.ps1 -ProgramPath /SLUS_008.60
  .\scripts\stop_headless_mcp.ps1

Only one of GUI / headless can hold the project at a time. Port 8090 (Hydro uses 8089).
#>
param(
    [string]$ProgramPath = '/PROSKATE.EXE',
    [int]$Port = 8090,
    [string]$MaxMem = '4G',
    [string]$Ghidra = 'D:\Tools\ghidra'
)
$ErrorActionPreference = 'Stop'
$root = Split-Path $PSScriptRoot -Parent
$gpr  = Join-Path $root 'ghidra\THPS.gpr'
$log  = Join-Path $root 'build\headless_mcp.log'

if (Get-NetTCPConnection -LocalPort $Port -State Listen -ErrorAction SilentlyContinue) {
    try {
        $r = Invoke-RestMethod "http://127.0.0.1:$Port/check_connection" -TimeoutSec 3
        Write-Host "Already serving on ${Port}: $r"; return
    } catch { throw "Port $Port is in use by something that isn't GhidraMCP." }
}
if (Test-Path (Join-Path $root 'ghidra\THPS.lock')) {
    Write-Warning 'THPS.lock exists: the GUI may have the project open, or a prior server was killed.'
}

$cmdFile = Join-Path $root 'build\headless_mcp.cmd'
Set-Content -Encoding ascii $cmdFile @(
    '@echo off',
    "call `"$Ghidra\support\launch.bat`" fg jdk GhidraMCP-Headless `"$MaxMem`" `"-XX:ParallelGCThreads=4`" com.xebyte.headless.GhidraMCPHeadlessServer --port $Port --project `"$gpr`" --program $ProgramPath > `"$log`" 2>&1")
Start-Process -WindowStyle Hidden cmd -ArgumentList '/c', "`"$cmdFile`""

for ($i = 0; $i -lt 90; $i++) {
    Start-Sleep 2
    try {
        $r = Invoke-RestMethod "http://127.0.0.1:$Port/check_connection" -TimeoutSec 2
        Write-Host "$r (log: $log)"; return
    } catch {}
}
throw "Server did not come up within 180s; see $log"
