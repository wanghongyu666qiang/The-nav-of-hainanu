$exts = @('*.cpp','*.h','*.hpp','*.c')
Get-ChildItem -Recurse -File -Include $exts | ForEach-Object {
    $p = $_.FullName
    try {
        $t = [System.IO.File]::ReadAllText($p, [System.Text.Encoding]::GetEncoding(936))
        [System.IO.File]::WriteAllText($p, $t, [System.Text.Encoding]::UTF8)
        Write-Output "Restored UTF8: $p"
    } catch {
        Write-Output "Failed restore: $p => $_"
    }
}