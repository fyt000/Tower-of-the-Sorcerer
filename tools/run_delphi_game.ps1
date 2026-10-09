param(
    [string]$Assets = 'D:\Program Files (x86)\Tower of the Sorcerer',
    [string]$SaveDirectory = '',
    [switch]$SkipIntro
)
$ErrorActionPreference = 'Stop'
$projectDirectory = Split-Path -Parent $PSScriptRoot
$gameExecutable = Join-Path $projectDirectory 'build\delphi-game\game\Tower.exe'
if (-not (Test-Path -LiteralPath $gameExecutable -PathType Leaf)) {
    throw 'Build the game first: C:\Python314\python.exe tools\build_delphi_game.py'
}
$gameArguments = @('--assets', $Assets)
if ($SaveDirectory -ne '') { $gameArguments += @('--save-dir', $SaveDirectory) }
if ($SkipIntro) { $gameArguments += '--no-intro' }
& $gameExecutable @gameArguments
