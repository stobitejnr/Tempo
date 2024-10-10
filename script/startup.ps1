# Check if BurntToast is installed, install it if not
if (-not (Get-Module -ListAvailable -Name BurntToast)) {
    Install-Module -Name BurntToast -Scope CurrentUser -Force -AllowClobber
}