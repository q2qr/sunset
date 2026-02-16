param(
    [Parameter(Mandatory = $true)]
    [string]$Sprx,

    [Parameter(Mandatory = $true)]
    [string]$MetadataJson,

    [Parameter(Mandatory = $false)]
    [string]$PreviewImage,

    [Parameter(Mandatory = $true)]
    [string]$Output
)

if (!(Test-Path $Sprx)) { throw "SPRX file not found: $Sprx" }
if (!(Test-Path $MetadataJson)) { throw "Metadata JSON not found: $MetadataJson" }

$magic = [System.Text.Encoding]::ASCII.GetBytes("SUNSETPK")
$version = [UInt32]1

$entries = @()
$entries += @{ Type = [UInt32]1; Name = [IO.Path]::GetFileName($Sprx); Data = [IO.File]::ReadAllBytes($Sprx) }
$entries += @{ Type = [UInt32]2; Name = [IO.Path]::GetFileName($MetadataJson); Data = [IO.File]::ReadAllBytes($MetadataJson) }

if ($PreviewImage -and (Test-Path $PreviewImage)) {
    $entries += @{ Type = [UInt32]3; Name = [IO.Path]::GetFileName($PreviewImage); Data = [IO.File]::ReadAllBytes($PreviewImage) }
}

$outDir = Split-Path -Parent $Output
if ($outDir -and !(Test-Path $outDir)) {
    New-Item -ItemType Directory -Path $outDir | Out-Null
}

$fs = [IO.File]::Open($Output, [IO.FileMode]::Create, [IO.FileAccess]::Write)
$bw = New-Object IO.BinaryWriter($fs)

try {
    $bw.Write($magic)
    $bw.Write($version)
    $bw.Write([UInt32]$entries.Count)

    foreach ($entry in $entries) {
        $nameBytes = [System.Text.Encoding]::UTF8.GetBytes($entry.Name)
        $dataBytes = $entry.Data

        $bw.Write([UInt32]$entry.Type)
        $bw.Write([UInt32]$nameBytes.Length)
        $bw.Write([UInt32]$dataBytes.Length)
        $bw.Write($nameBytes)
        $bw.Write($dataBytes)
    }
}
finally {
    $bw.Dispose()
    $fs.Dispose()
}

Write-Host "Created package: $Output"
