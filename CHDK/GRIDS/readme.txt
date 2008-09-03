What are Grids?

Grids are an overlay for your EVF/LCD display that can help you with composition, cropping, subject/image alignment, and other novel things. Normally most cameras only offer you one simple option, a "Rule of Thirds" composition grid, but with CHDK the sky is now the limit on what you want displayed on your viewfinder for these handy photographer's tools.

You may Load and run your Grid files from the CHDK <ALT> + Menu path of: "OSD Parameters" > "Grid" > "Load Grid from File..." When not in <ALT> mode you may quickly turn your Grid Overlay (and all other CHDK OSD elements) on or off with a simple Half-Shutter-Press + Right-Navigation button combination. Or put the "Grid" > "Show Grid Lines" menu toggle on your fast-access Custom User-Menu if not wishing to turn off all of CHDK displays.

Grids are drawn as an EVF/LCD overlay by simple graphic commands. You may edit "Grid Files" using any basic text editor. (MAC users should check that they are saved as "plain text encoding", select "Unicode (UTF-8)" when saving your files, the same as when saving uBASIC script files.) For faster loading/searching access save them to your /CHDK/GRIDS/ folder on your SD-card, the default "Load Grid from File..." location.

Grid patterns are drawn on your EVF/LCD display with the coordinates of: X = 0 to 359 (horizontally) and Y = 0 to 239 (vertically), with position 0,0 being in the upper-left corner and 359,239 being in the lower-right corner.

When designing your own Grid patterns you must keep in mind that the 360x240 drawing coordinate area is in a 3:2 aspect ratio, but when displayed on your EVF/LCD display they will appear in a 360x270 or 4:3 aspect ratio. Use whatever method you have to convert your drawing-coordinates between the two. For complex grid designs one prolific grid-designer found it best to draw a new grid using any decent vector-graphic editor on their computer with a 360x270 base canvas and then resizing the final grid-design with "keep proportional" turned off to the required 360x240 ratio. The new, and now-correct, drawing coordinates were then read off from the resulting 3:2 proportional image. All right-angles, complex-angles, curves, and circles were then fully proportional and appeared correctly in the EVF/LCD display. If needing to only do simple circles or squares with the 4:3 / 3:2 offset, take the X radius/dimension and multiply it by 8, then divide that result by 9, to get a proportionally equivalent Y radius/dimension.


Format and commands for Grid Files for CHDK:

@title <text to show in menu>
@line   x0, y0, x1, y1, lineColor
@rect   x0, y0, x1, y1, borderColor
@rectf  x0, y0, x1, y1, borderColor, fillColor
@elps   x0, y0, rx, ry, borderColor
@elpsf  x0, y0, rx, ry, fillColor
# comment <a non-implemented note>

Where:

rect = hollow-rectangle
rectf = filled-rectangle
elps = ellipse, where x0, y0 = ellipse radius center, and rx, ry = the two radiuses/radii
elpsf = ellipse-filled

See the included sample Grid Files on their use. Spaces between commands and numbers on each line are optional. If designing a very complex grid you may need to omit all spaces to get your grid-pattern file to fit within the maximum memory of (approx.) 3886 bytes.

All numbers can be either decimal or hex. Hex numbers are prefixed with "0x", as in "0x16". For color-numbers you may use your CHDK <ALT> Menu of "Miscellaneous Stuff" > "Draw Palette" to choose and preview them, or any of the "Visual Settings" color selections menus for font display colors -- which is sometimes easier because you can see all of the colors at once instead of previewing one at a time in the "Draw Palette" feature.

For the most complete and latest collection of user-designed and submitted Grid Files, as well as a handy utility to create "text-grid designs", see: http://chdk.wikia.com/wiki/Grids


Included are some sample Grid files, these are:

3to2grid.grd
  Match your EVF/LCD display to a 3:2 crop-ratio for prints matching that ratio, 6" x 4" prints.
  
3to8grid.grd
  <i>(Usage Unknown, I'm not sure why this one was included, perhaps someone else can clarify?)</i>
  
golden1.grd
  Compose your subject placement in accordance with the "Golden Ratio". A composition ratio deemed most pleasing to the human-eye. This version is based on "golden-triangles". Place your subject where the two lines meet or aligned along their axes. (This grid may be used in reflections and flips, affording 3 more locations, do it mentally, or edit the grid file to reflect all 4 golden-triangle intersections.)
  
golden2.grd
  Same as above, but showing you one more of the 4 total intersection/alignment possibilities.
  
id.grd
  This grid is based on ISO/IEC 19794-5:2005 values required for administrative identity photo (passports, identity cards, driving licence...). A large red face shape represent the maximum size accepted, whereas the smaller green shape is the minimal size allowed. A grey area represent where eyes have to be. A vertical axis and two horizontal rulers should help for positioning the subject. The picture afterwards has to be resized to 35 x 45 mm before being printed. The best is to make a composition of 6 (2 lines, 3 rows) photo on a 10 x 13 cm format or 8 (2 lines, 4 rows) photo on a 10x15 format. The reprint should be done by a professional, not by your personnal printer...otherwise it might be refused by the administration staff.
  
rulecross.grd
  Fashioned after some aerial-photography and photomicrography grids. Horizontal and vertical rulers bisecting your FOV. Divided horizontally in 4 units of measure and vertically in 3 units of measure. With half and 1/10th unit tic-marks. Small crosshairs in the open areas at 1/2 and 1-unit intervals. May be extremely handy for macro-photography when trying to keep the subject size the same in landscape or portrait orientations. Or when comparing subject size to one another when reframing or refocusing.
  
rulers.grd
  As above, but without the crosshairs in the clear areas.
  
sports.grd
  A "Sports Finder" grid. This grid was designed around the available image sizes of an "S3 IS" camera. When shooting in highest resolution of "L", 2816 x 2112 pixels, this grid displays the cropping areas as if you were using the "M1" - 2271 x 1704 pixels, the "M2" - 1600 x 1200 pixels, and the "S" - 640 x 480 pixel image sizes. This way you can view the full-frame in the viewfinder, but plan ahead for cropping to one of the other available resolutions. You can then watch for any activity outside of those image-resolution boundaries and be better able to follow any fast action in your viewfinder that might be entering or leaving the final-crop image area. One more pair of lines was included to show the "W" - 2816 x 1584 wide-angle FOV so when planning to crop for that resolution you can still watch for activity above and below your final image area, instead of just blacking out those areas as the camera normally does. It is worth noting, that even a 1600 x 1200 resolution image will still print quite nicely even at 7"x5" print size. For that little-league game this might be just the thing you need for following the action and still having photos to print out for relatives and friends.
  
stolen.grd
  Load this grid before putting your camera down and you don't want anyone else to use it. When turning on your camera only the words "STOLEN CAMERA!" will show in the display. The view blacked-out, making subject viewing/framing useless. Unless they know how to turn off CHDK features. :) This is part of an experiment on using CHDK as a theft-deterent. Using this grid combined with an auto-running script file which flashes all your LED lights and triggers all the warning-beep sound-events in your camera, it might be a quite effective way to see/hear if someone is picking up your camera and turning it on without your permission, as well as rendering the camera useless to anyone without CHDK knowledge.
  
third_h.grd
  Divides your FOV into 3rds horizontally. Based on the "Rule of Thirds" composition concept. (A simplified version of the "Golden Ratio" concept.)
  
third_v.grd
  As above but dividing your FOV into 3rds vertically.
