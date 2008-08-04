rem Eggtimer by gehtnix from the german forum, didnt feel like translating it - as of now
rem has to be started in record mode, uses sounds (unmute cam!)
rem disables display for energy saving
rem Die Eieruhr - für juciphox User und alle Kameras!!!, Autor: gehtnix  
rem Timer zum Eierkochen
@title Die Eieruhr
@param a Weich Minuten
@default a 5
@param b Mittel Minuten
@default b 7
@param c Hart Minuten
@default c 10
@param d Sekunden f. Mittel
@default d 30
@param e Sekunden f. Alle
@default e 0
@param r USB-Taster 0=ein 1=aus
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
  print             "  **** DIE EIERUHR ****"
  if r=1 then print "  <<<       =     Weich"  else print "  Kurz      =     Weich"	
  if r=1 then print "  Set       =     Mittel" else print "  Lang      =     Mittel"
  if r=1 then print "  >>>       =     Hart" else print "  Länger    =     Hart"
  if r=1 then print "  Ausl.     =     Ende" else print "  Ausl.     =     Ende"
  gosub "taster"
  cls

  select P
    case 0 to X; gosub "weich"
    case X to Y; gosub "mittel"
		case Y to Z; gosub "hart"
	  case_else print "Und nu?"
  end_select
  
wend

end

:weich
select e
	case 0; A=a*60*1000
	case 1 to 59; A=(e+a*60)*1000
end_select
cls
print "************************"
print "*                      *"
print "*      Weiches Ei      *"
print "*                      *"
print "************************"
gosub "eieruhr"
return

:mittel
select e
	case 0; A=(d+b*60)*1000
	case 1 to 59; A=(e+b*60)*1000
end_select
cls
print "************************"
print "*                      *"
print "*   Mittelweiches Ei   *"
print "*                      *"
print "************************"
gosub "eieruhr"
return

:hart
select e
	case 0; A=c*60*1000
	case 1 to 59; A=(e+c*60)*1000
end_select
cls
print "************************"
print "*                      *"
print "*      Hartes Ei       *"
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
print "*  Das Ei ist fertig!   *"
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
 