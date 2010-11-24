@title mddemov1

@param a Columns
@default a 8

@param b Rows
@default b 6

@param c Threshold (0-255)
@default c 10

@param d compare Interval (millisecs)
@default d 80

@param e Begin Triggering Delay(secs)
@default e 20

@param f Detect Timeout (seconds)
@default f 30

@param g pix step(speed/accuracy adj)
@default g 8

@param h  reg mode(0-no,1-incl,2-excl)
@default h 2

@param i measure mode(1-Y,0-U,2-V)
@default i 1

if a<1 then let a=1
if b<1 then let b=1
if c<0 then let c=0
if g<1 then let g=1
if f<1 then let f=1

let f=f*1000
let e=e*1000

print_screen 1

print ">[";a;",";b;"] threshold: ";c

for z=0 to 10000
    let t=0

rem              /--/-columns, rows to split picture into
rem              |  |
rem              |  |  measure mode (Y,U,V R,G,B) - U-0, Y-1, V-2, 3-R, 4-G, 5-B
rem              |  |  |                     
rem              |  |  |  timeout
rem              |  |  |  |  comparison interval (msec)
rem              |  |  |  |  |  threshold ( difference in cell to trigger detection)
rem              |  |  |  |  |  |  draw_grid (0-no, 1-yes)
rem              |  |  |  |  |  |  |  return variable. number of cells with motion detected
rem              |  |  |  |  |  |  |  |
rem              |  |  |  |  |  |  |  |  VVVVVV  OPTIONAL PARAMETERS: VVVV
rem              |  |  |  |  |  |  |  |
rem              |  |  |  |  |  |  |  |  region (masking) mode: 0-no regions, 1-include,  2-exclude
rem              |  |  |  |  |  |  |  |  |  region first column
rem              |  |  |  |  |  |  |  |  |  |  region first row
rem              |  |  |  |  |  |  |  |  |  |  |   region last column
rem              |  |  |  |  |  |  |  |  |  |  |   |    region last row
rem              |  |  |  |  |  |  |  |  |  |  |   |    |   parameters- 1-make immediate shoot, 2-log debug information into file. OR-ed values are accepted
rem              |  |  |  |  |  |  |  |  |  |  |   |    |   |  pixels step - speed vs. Accuracy adjustments (1-use every pixel, 2-use every second pixel, etc)
rem              |  |  |  |  |  |  |  |  |  |  |   |    |   |  |  number of milliseconds to wait before begin triggering - can be useful for calibration with "draw_grid" option
rem              |  |  |  |  |  |  |  |  |  |  |   |    |   |  |  |
rem              V  V  V  V  V  V  V  V  V  V  V   V    V   V  V  V
md_detect_motion a, b, i, f, d, c, 1, t, h, 2, 2, a-1, b-1, 0, g, e

rem                 <minimal variables set>
rem md_detect_motion a, b, i, f, d, c, j, f

rem if t>0 then shoot

if t>0 then print "detected cells:",t else print "Timeout"

next z

end
