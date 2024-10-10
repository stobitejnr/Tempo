param (
    [string]$title = "Notification",
    [string]$message = "This is a notification",
    [string]$imagePath = "C:\Path\To\Your\Image.png"
)

# Load Windows Runtime namespaces for toast notifications
[Windows.UI.Notifications.ToastNotificationManager, Windows.UI.Notifications, ContentType = WindowsRuntime] > $null
[Windows.Data.Xml.Dom.XmlDocument, Windows.Data.Xml.Dom.XmlDocument, ContentType = WindowsRuntime] > $null

# Create the XML content for the toast notification
$toastXmlString = @"
<toast>
    <visual>
        <binding template="ToastText02">
            <text id="1">$title</text>
            <text id="2">$message</text>
        </binding>
    </visual>
</toast>
"@

# Convert the XML string into an XmlDocument object
$toastXml = New-Object Windows.Data.Xml.Dom.XmlDocument
$toastXml.LoadXml($toastXmlString)

# Create the toast notification using the XML
$toast = [Windows.UI.Notifications.ToastNotification]::new($toastXml)
[Windows.UI.Notifications.ToastNotificationManager]::CreateToastNotifier("Tempo").Show($toast)
