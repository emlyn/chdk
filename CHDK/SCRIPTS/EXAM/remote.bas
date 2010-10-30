rem http://chdk.wikia.com/wiki/USB_Remote_Cable
rem Simple USB Remote Shoot script
rem Usage: Select "Enable Remote" in "Remote parameters" and start this script.
@title Remote button

while 1
    wait_click 1
    if is_key "remote" then shoot
wend

end
