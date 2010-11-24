@title Интервальное видео
rem Gans gansek.narod.ru
@param a Количество кадров 
@default a 5
@param b Время съемки (мин) 
@default b 0
@param c Время съемки (сек) 
@default c 10
@param d Интервал между съемкой (мин) 
@default d 0
@param e Интервал между съемкой (сек) 
@default e 10

sleep 1000
t=60000*b+1000*c+1000
i=60000*d+1000*e+1000

for s=1 to a
    click "shoot_full"
    print "Снимаю",s,"-й из",c" фильмов"
    sleep t
    click "shoot_full"
    print "Жду",d,"минут",e,"секунд"
    sleep i
next s

print "Приятного просмотра!"
sleep 2000

end
