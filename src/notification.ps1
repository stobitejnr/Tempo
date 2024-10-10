param (
    [string]$title = "Tempo",
    [string]$message = "This is your notification.",
    [string]$imagePath = "../logo.png"  # New parameter for the image path
)

# Check if BurntToast is installed, install it if not
if (-not (Get-Module -ListAvailable -Name BurntToast)) {
    Install-Module -Name BurntToast -Scope CurrentUser -Force -AllowClobber
}

Import-Module BurntToast

# Create the notification with an optional image
if ($imagePath) {
    New-BurntToastNotification -Text $title, $message -AppLogo $imagePath
} else {
    New-BurntToastNotification -Text $title, $message
}