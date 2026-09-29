<#
Import a PSX-EXE into ghidra\THPS.gpr with the PSX loader, auto-analyze, and (optionally)
apply a symbol TSV as a post-script.

  .\scripts\build_project.ps1 -Program PROSKATE_demo -Exe extern\demo\PROSKATE.EXE `
        -Tsv build\demo_syms.tsv
  .\scripts\build_project.ps1 -Program SLUS_00860 -Exe extern\thps1_retail\SLUS_008.60 `
        -Tsv build\retail_names.tsv

analyzeHeadless.bat hardcodes MAXMEM=2G, so (like the Hydro project) we call launch.bat
directly through a .cmd file. Pass -Force to overwrite an existing program in the project.
#>
param(
    [Parameter(Mandatory)][string]$Program,
    [Parameter(Mandatory)][string]$Exe,
    [string]$Tsv,
    [switch]$Force,
    [string]$MaxMem = '6G',
    [string]$Ghidra = 'D:\Tools\ghidra'
)
$ErrorActionPreference = 'Stop'
$root = Split-Path $PSScriptRoot -Parent
$proj = Join-Path $root 'ghidra'
$name = 'THPS'
$exe  = Join-Path $root $Exe
if (-not (Test-Path $exe)) { throw "missing exe: $exe" }
New-Item -ItemType Directory -Force $proj, (Join-Path $root 'build') | Out-Null

$argv = @($proj, $name, '-import', $exe,
          '-loader', 'PsxLoader',
          '-scriptPath', (Join-Path $root 'ghidra_scripts'))
if ($Force) { $argv += '-overwrite' }
if ($Tsv) {
    $argv += @('-postScript', (Join-Path $root 'ghidra_scripts\ApplyPsxSym.java'),
               (Join-Path $root $Tsv))
}
$argv += @('-log', (Join-Path $root "build\analyze_$Program.log"),
           '-scriptlog', (Join-Path $root "build\script_$Program.log"))
$argvq = $argv | ForEach-Object { "`"$_`"" }

$launch  = Join-Path $Ghidra 'support\launch.bat'
$cmdFile = Join-Path $root 'build\analyze.cmd'
Set-Content -Encoding ascii $cmdFile @(
    '@echo off',
    "call `"$launch`" fg jdk Ghidra-Headless `"$MaxMem`" `"-XX:ParallelGCThreads=4`" ghidra.app.util.headless.AnalyzeHeadless $($argvq -join ' ')")
Write-Host "Importing $Program from $Exe ..."
& $cmdFile
if ($LASTEXITCODE) { throw "analyzeHeadless exited with $LASTEXITCODE" }
Write-Host "Done. Program '/$([IO.Path]::GetFileName($exe))' is in $proj\$name.gpr"
