rem Eggtimer by gehtnix from the german forum, didnt feel like translating it - as of now
rem has to be started in record mode, uses sounds (unmute cam!)
rem disables display for energy saving
rem Die Eieruhr - für juciphox User und alle Kameras!!!, Autor: gehtnix  
rem Timer zum Eierkochen
@title eggtimer
@param a soft minutes
@default a 5
@param b medium minutes
@default b 7
@param c hard minutes
@default c 10
@param d seconds f. medium
@default d 30
@param e seconds f. all
@default e 0
@param r USB-remote 0=On 1=off
@default r 1

rem --- Werte für Taster
X=20
Y=50
Z=200

select get_display_mode
	case 0; T=0
	case 1; T=1
	case 2; T=2
	case 3; T=3
end_select

rem --- Menü
while 1
  cls
  print             "  **** EGGTIMER ****"
  if r=1 then print "  <<<       =     Soft"  else print 	"  short     =     soft"	
  if r=1 then print "  Set       =     medium" else print "  long      =     medium"
  if r=1 then print "  >>>       =     hard" else print 	"  longer    =     hard"
  if r=1 then print "  USB       =     Ende" else print 	"  USB       =     Ende"
  gosub "taster"
  cls

  select P
    case 0 to X; gosub "soft"
    case X to Y; gosub "medium"
		case Y to Z; gosub "hard"
  end_select
  
wend

end

:soft
select e
	case 0; A=a*60*1000
	case 1 to 59; A=(e+a*60)*1000
end_select
cls
print "************************"
print "*                      *"
print "*   Softboiled egg     *"
print "*                      *"
print "************************"
gosub "eieruhr"
return

:medium
select e
	case 0; A=(d+b*60)*1000
	case 1 to 59; A=(e+b*60)*1000
end_select
cls
print "************************"
print "*                      *"
print "*   mediumboiled egg   *"
print "*                      *"
print "************************"
gosub "eieruhr"
return

:hard
select e
	case 0; A=c*60*1000
	case 1 to 59; A=(e+c*60)*1000
end_select
cls
print "************************"
print "*                      *"
print "*   hardboiled egg     *"
print "*                      *"
print "************************"
gosub "eieruhr"
return

rem ---eieruhr
:eieruhr
sleep 2000
gosub "dispaus"
sleep A-3000
gosub "dispein"
cls
print "************************"
print "*                      *"
print "*    Yay! Finished!    *"
print "*                      *"
print "************************"
for i=1 to 3
	playsound 3
	sleep 4000
next i
shut_down
cls
return

rem --- taster
:taster
 P=0
 if r=1 then
  gosub "ohnetaster"
  goto "sprung2"
 endif
 do
  P=get_usb_power
 until P>0
:sprung2
return

rem --- ohnetaster
:ohnetaster
:wait 
wait_click 
 is_key k "left" 
  if k=1 then P=X/2 
  if k=1 then goto "sprung3"
 is_key k "set" 
  if k=1 then P=X+1
  if k=1 then goto "sprung3"
 is_key k "right" 
  if k=1 then P=Y+10
  if k=1 then goto "sprung3"
goto "wait" 
:sprung3
k=0
return

:dispaus
 do
 click "display"
 U=get_display_mode
 until (U=2 or U=3)
 return

:dispein
 do
 click "display"
 U=get_display_mode
 until U=T
 return
 