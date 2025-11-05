Param(
    [string]$TemplatesPath = (Join-Path $PSScriptRoot 'Templates'),
    [string]$OutputPath = (Join-Path $PSScriptRoot 'Templates-Combined.md')
)

# Validate Templates folder
if (-not (Test-Path -Path $TemplatesPath -PathType Container)) {
    Write-Error "Templates folder not found: $TemplatesPath"
    exit 1
}

# Gather all .cpp files recursively
$files = Get-ChildItem -Path $TemplatesPath -Filter '*.cpp' -Recurse -File | Sort-Object -Property FullName

# Prepare UTF-8 (no BOM) encoding instance
$utf8NoBom = New-Object System.Text.UTF8Encoding($false)

if (-not $files -or $files.Count -eq 0) {
    Write-Warning "No .cpp files found under $TemplatesPath"
    # Still create/clear the output file
    [System.IO.File]::WriteAllText($OutputPath, "", $utf8NoBom)
    exit 0
}

$sb = New-Object System.Text.StringBuilder

# Encodings
$utf8Strict = New-Object System.Text.UTF8Encoding($true)   # throws on invalid bytes
$defaultEnc = [System.Text.Encoding]::Default

foreach ($file in $files) {
    # Heading: filename with extension as H1
    [void]$sb.AppendLine("# $($file.Name)")
    [void]$sb.AppendLine()
    [void]$sb.AppendLine('```cpp')

    # Read file content as UTF-8 if valid; otherwise fallback to system default (e.g., GBK on zh-CN)
    $bytes = [System.IO.File]::ReadAllBytes($file.FullName)
    try {
        $code = $utf8Strict.GetString($bytes)
    } catch {
        $code = $defaultEnc.GetString($bytes)
    }

    # Normalize line endings to CRLF for Windows printing
    $code = $code -replace "`r?`n", "`r`n"

    # Avoid extra blank lines at the end inside the code block
    $trimmed = $code.TrimEnd("`r", "`n")
    [void]$sb.AppendLine($trimmed)

    [void]$sb.AppendLine('```')
    [void]$sb.AppendLine()
}

# Write UTF-8 without BOM for broad compatibility
[System.IO.File]::WriteAllText($OutputPath, $sb.ToString(), $utf8NoBom)

Write-Host "Markdown generated: $OutputPath" -ForegroundColor Green