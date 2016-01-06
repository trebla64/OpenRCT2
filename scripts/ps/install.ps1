#########################################################
# Script to install the latest dependencies for OpenRCT2
#########################################################
param (
    [switch]$Force,
    [switch]$Quiet
)
Write-Host "Installing OpenRCT2 development environment for Windows" -ForegroundColor Cyan

# Setup
$ErrorActionPreference = "Stop"
$scriptsPath = Split-Path $Script:MyInvocation.MyCommand.Path
Import-Module "$scriptsPath\common.psm1" -DisableNameChecking

# Constants
$libsUrl = "https://openrct2.website/files/orctlibs-vs.zip"
$libsVersion = 4

# Get paths
$rootPath        = Get-RootPath
$libsPath        = Join-Path $rootPath "lib"
$zipPath         = Join-Path $libsPath "orctlibs.zip"
$libsVersionPath = Join-Path $libsPath "libversion"

# Check if we need to update the dependencies
$currentLibsVersion = 0
$updateLibs = $true
if (Test-Path $libsVersionPath)
{
    $currentLibsVersion = [IO.File]::ReadAllText($libsVersionPath)
}
if ($currentLibsVersion -ge $libsVersion)
{
    $updateLibs = $false
}

# Check if user needs to download dependencies
$libsPathExists = Test-Path $libsPath
if ($libsPathExists -and -not $updateLibs -and -not $Force)
{
    if (-not $Quiet -and (Prompt-User "Dependencies already exists, reinstall?"))
    {
        $updateLibs = $true
    }
}
else
{
    $updateLibs = $true
}

# Download latest version of the dependencies
if ($updateLibs) {
    Write-Host "Updating dependencies..." -ForegroundColor Cyan

    Remove-Item -Force -Recurse $libsPath -ErrorAction SilentlyContinue
    New-Item -Force -ItemType Directory $libsPath > $null

    Invoke-WebRequest $libsUrl -OutFile $zipPath
    [System.Reflection.Assembly]::LoadWithPartialName('System.IO.Compression.FileSystem') > $null
    [System.IO.Compression.ZipFile]::ExtractToDirectory($zipPath, $libsPath)
    Remove-Item $zipPath -Force -ErrorAction SilentlyContinue
    $libsVersion | Set-Content $libsVersionPath
}
