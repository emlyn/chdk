Index:
	01 - Introduction & Camera Specific Notes

	02 - Installation

	03 - FAQ

	04 - Links, Urls

	05 - GPL, License


************************************


01 - Introduction

Hi, 

this is the small readme to CHDK. It provides just enough info to get you rolling, for more information use the links in the bottom.


CHDK is a firmware enhancement that operates on a number of Canon Cameras. CHDK gets loaded into your camera's memory upon bootup (either manually or automatically). It provides additional functionality beyond that currently provided by the native camera firmware.

CHDK is not a permanent firmware upgrade: you decide how it is loaded (manually or automatically) and you can always easily remove it. 

Main features:

    * Save images in RAW format
    * Ability to run "Scripts" to automate the camera
    * Live histogram (RGB, blended, luminance and for each RGB channel)
    * Zebra mode (blinking highlights and shadows to show over/under exposed areas)
    * An "always on" full range Battery indicator
    * Ability to turn off automatic dark-frame subtraction
    * a higher compression movie mode, and double the maximum video file size
    * exposure times as long as 65 seconds
    * exposure times as little as 1/10,000 of a second
    * ability to use the USB port for a remote trigger input 

Additional features:

    * a depth-of-field (DOF)-calculator
    * File browser
    * Text reader
    * Calendar
    * Some fun tools and games 

Why would I want to use CHDK?

    * To get Raw file capability on cameras that don't have that ability
    * To get the ability to use scripts
    * to be able to know the battery status at all times (not just when it's about to run out of power)
    * you want or need any of the other enhancement features that CHDK provides 

What are scripts? Scripts are BASIC language programs that give you the ability to control the operation of the camera under program control. They have been used to add or extend the native capability of the camera: more flexible intervalometers, extended-range exposure compensation, extended bracketing ability, lightning photography, etc. See the script pages for more details.

Beyond "Standard" CHDK

Several developers have extended the basic features of CHDK to add additional major functions. You'll find these extended features in "special builds".

There are several "Motion Detection" versions available that allow scripts to detect when motion (or any change in light intensity) occurs in one or more predefined regions of the images (the script can then take a photograph, a video, start a timer, etc) and there are some *very* cool applications based on this implementation.

There is a "Stereo Data Maker" (SDM) version, specifically geared to stereo image applications (which also incorporates the Motion Detection routines).

Additional video compression options (more or less), and the ability to go beyond the 1 Gbyte limit.

Use your USB port as a remote control / "cable release".

(to be expanded)

****************************************

Camera depending notes: 

This cam should work with CHDK as is, no special notes existing.


********************************

02 - Installation


- Exract the archive onto your SD card using an SD card-reader. You MUST use a card-reader. You cannot copy files to your SD card by just using "Windows File Explorer" and your camera connected by USB cable. The USB connection to the camera is just for downloading images, not uploading files.

- Now that all the CHDK files are on your SD card, make sure that you have the right version of CHDK for your camera.

- Insert the SD card into your camera.

- Start camera IN PLAYBACK-MODE.

- When you extracted the archive it placed a file on your card called "vers.req" (or "ver.req" depending on the camera model). This will allow you to see, with the right camera-button presses, the TRUE firmware version of your camera (and other interesting information).

- Press your "Set" button, hold it down. While holding down your "Set" button press your "Display" button. You will see the version of the firmware in your camera. Confirm that it is the right firmware to match up with the CHDK that you downloaded. Your real firmware version is NOT 1.0.1.0 nor 1.0.0.0 Your REAL firmware version will look something like: "Firmware Ver GM1.00A". (Pressing "Display" again a few times while still holding down your "Set" button will let you see even more information about your camera, including total number of shots taken since it was made.)

- If all went well, correct camera, correct firmware, correct CHDK, now you can actually load and run CHDK.

- While still in PLAYBACK MODE press your camera's "Menu" button to open Canon's Menu

- Scroll to the bottom of the menu to the "Firm Update" option which should now be available. If by chance that you fail to see the "Firm Update" menu option try pressing your Playback button twice. You might have to wait 2 seconds between presses. When this is done right the lens will retract and go into a power-saving viewer/slideshow playback mode. This seems to be an option on most Powershot Cameras.

- Now that your menu cursor is on the "Firm Update" option, press your "Set" button or "Right" navigation button to enter the "Firmware Update" Screen. Either button press will work.

- Press your "Right" navigational button to select OK. Press your "Set" button to confirm your choice.

- Your camera will now load CHDK. You should see the blue "Print" button on the back of your camera flash a few times to let you know that CHDK is booting, and the CHDK Splash-Screen will appear in your viewfinder or LCD display. When fully loaded you will see a new battery-meter icon and several other things on your LCD or EVF display. Don't worry if they look like clutter, all of them can be turned on and off and repositioned on your screen in CHDK's configuration menu system. (CHDK <ALT> mode / Menu / OSD Parameters / OSD Layout Editor)

- To enter CHDK's alternate menu system, press your "Shortcut" button. A small "<ALT>" will appear at the bottom of your screen. Whenever <ALT> is showing you may now press your camera's "Menu" button to enter CHDK's new menus. To exit <ALT> mode and return to your camera's normal operation just press your "Shortcut" button again. The settings that you apply in CHDK's menus will now be applied when using the camera normally (while not in <ALT> mode). The only time you will use <ALT> mode for actually taking pictures is if you run an automated CHDK script to take your photos for you. If you want to use your "Shortcut" button's normal function just press and hold it down a little longer. Some cameras allow you to reconfigure your CHDK "<ALT>" toggle button in the CHDK "Miscellaneous Stuff" menu in case you don't like it being the "Shortcut" button.

- If you would like to have CHDK auto-load every time you power on your camera, then go into CHDK's menu system. (Press "Shortcut" to enter <ALT> mode, then your "Menu" button to enter CHDK's menus.) Scroll to the bottom of the main CHDK menu to the "Debug Parameters" option.

- Enter the "Debug" menu and scroll to "Make Card Bootable...". Press your "Set" button.

- Now remove your SD card and slide its little "write protect" tab to the locked position. Insert the card back in your camera. Now when you power-up your camera CHDK will automatically load. If you want to turn off CHDK's auto-loading feature just take out the SD card and put the write-protect tab back to the unlocked position. Don't worry about using the card either way. CHDK is designed to work with a locked card in this manner and all photos taken will be written to the card even when it is locked/write-protected.

- Or for Windows users: use the "CardTricks" program (will be included here later).


(to be expanded)

****************************************

03 - FAQ

1. What is CHDK?

    CHDK is not just one thing! The term CHDK refers to free software – currently available for many (but not all) Canon PowerShot compact digital cameras – that you can load onto your camera's memory card to give your camera greatly enhanced capabilities. 

2. Am I likely to be interested in CHDK?

    The enhanced capabilities that CHDK provides are most likely to be of interest to experienced photographers - if you believe that your Canon PowerShot camera already has more features than you will ever need, you probably won't be interested in CHDK. 

3. Is CHDK safe to use?

    Yes CHDK is safe. CHDK doesn't make any actual changes to your camera. If you delete the CHDK software from your memory card, or if you choose not to activate the CHDK software on the card (or remove and replace the batteries), then the camera will behave absolutely normally - nothing has been (or ever is) changed, so the warranty is not affected. 

4. How does CHDK work?

    CHDK makes use of the microprocessor that controls the camera (every digital camera contains a microprocessor) to act as a programmable computer that provides the extra capabilities. 

5. What extra capabilities does CHDK provide?

    The current set of extra capabilities fall into six categories:

        a. Enhanced ways of recording images - you can capture still pictures in RAW format (as well as JPEG), and for video images you can have increased recording time and length (1 hour or 2 GB), and a greatly increased range of compression options. 
        b. Additional data displays on the LCD screen - histogram, battery life indicator, depth of field, and many more. 
        c. Additional photographic settings that are not available on the camera by itself - longer exposure times (up to 65 seconds), faster shutter speeds (1/25,000 sec, and faster in some cases), automatic bracketing of exposure, etc. 
        d. The ability for the camera to run programs ('scripts', written in a micro-version of the BASIC language) stored on the memory card - these programs allow you to set the camera to perform a sequence of operations under the control of the program. For example, a camera can be programmed to take multiple pictures for focus bracketing, or take a picture when it detects that something in the field of view moves or changes brightness. 
        e. The ability to take a picture, or start a program on the memory card, by sending a signal into the USB port - you can use the USB cable to take a picture remotely. 
        f. The ability to do a number of other more useful (and fun) things, such as act as a mini file browser for the memory card, let you play games on the LCD screen, etc. 

6. What else should I know?

    Developers around the world are continuing to add new features to CHDK. Because the idea of using the camera's microprocessor is so flexible, various developers have made different versions of CHDK, and new features continue to be developed - for example, one version of CHDK has features assist in taking stereo photographs, and even allows two cameras to be synchronized to take pictures at the same time (with an accuracy of better than 0.1 milliseconds, providing they are the same camera model). 

(to be expanded)

********************************

04 - URLs, Links


For more information visit the following links:

CHDK Wiki: http://chdk.wikia.com/wiki/Main_Page

Main CHDK Manual: http://chdk.wikia.com/wiki/CHDK_firmware_usage

Allbest CHDK Manual: http://chdk.wikia.com/wiki/CHDK_firmware_usage/AllBest

JuciPhoX CHDK Manual: http://chdk.wikia.com/wiki/CHDK/MoreBest

CHDK Forum: http://chdk.setepontos.com/index.php

In-Depth Guide explaining a lot of things: http://chdk.setepontos.com/index.php/topic,1167.0.html

Timeline (changelog) of chdk: http://tools.assembla.com/chdk/timeline

For more information about this build visit: http://chdk.setepontos.com/index.php/topic,688.0.html

Download the sources of this build here: http://tools.assembla.com/chdk/changeset/head/branches/juciphox?old_path=%2F&format=zip

You can get a nice app that will help you making your card bootable on windows: http://chdk.setepontos.com/index.php/topic,964.0.html

<insert text with small description of chdk here>

<insert text with installation tips for vxworks here>

<insert more links and especially tricks for OS other than Windows> 


*********************************

05 - GPL


/*
 * This file is part of CHDK.
 * Copyright (C) 2008 The CHDK Team
 * CHDK - CHDK Wiki
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA,
 * 02110-1301  USA
 */

