<#
Save and stop the headless GhidraMCP server started by start_headless_mcp.ps1.
#>
param([int]$Port = 8090)
$ErrorActionPreference = 'SilentlyContinue'
try { Invoke-RestMethod "http://127.0.0.1:$Port/save_program" -TimeoutSec 10 | Out-Null; Write-Host 'saved' } catch {}
try { Invoke-RestMethod "http://127.0.0.1:$Port/exit_ghidra" -TimeoutSec 10 | Out-Null; Write-Host 'exit requested' } catch {}
Start-Sleep 2
if (Get-NetTCPConnection -LocalPort $Port -State Listen -ErrorAction SilentlyContinue) {
    Write-Warning "Port $Port still listening; you may need to kill the java process."
} else { Write-Host "stopped." }
