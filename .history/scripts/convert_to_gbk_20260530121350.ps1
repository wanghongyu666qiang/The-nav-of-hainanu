$exts = @('*.cpp','*.h','*.hpp','*.c','*.txt','*.md')
Get-ChildItem -Recurse -File -Include $exts | ForEach-Object {
    $p = $_.FullName
    try {
        $t = Get-Content -Raw -LiteralPath $p
        [System.IO.File]::WriteAllText($p, $t, [System.Text.Encoding]::GetEncoding(936))
        Write-Output "Converted: $p"
    } catch {
        Write-Output "Failed: $p => $_"
    }
}