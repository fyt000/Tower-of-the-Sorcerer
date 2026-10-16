param(
    [string]$Assets = '',
    [string]$SaveDirectory = '',
    [switch]$SkipIntro
)
$ErrorActionPreference = 'Stop'
$projectDirectory = Split-Path -Parent $PSScriptRoot
if ($Assets -eq '') {
    if ($env:TOS_ASSETS) { $Assets = $env:TOS_ASSETS }
    elseif ($env:TOS_ORIGINAL_EXE) { $Assets = Split-Path -Parent $env:TOS_ORIGINAL_EXE }
    else { $Assets = Join-Path $projectDirectory 'build\research' }
}
$gameExecutable = Join-Path $projectDirectory 'build\delphi-game\game\Tower.exe'
if (-not (Test-Path -LiteralPath $gameExecutable -PathType Leaf)) {
    throw 'Build the game first: python tools/build_delphi_game.py'
}
$gameArguments = @('--assets', $Assets)
if ($SaveDirectory -ne '') { $gameArguments += @('--save-dir', $SaveDirectory) }
if ($SkipIntro) { $gameArguments += '--no-intro' }
& $gameExecutable @gameArguments
