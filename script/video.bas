@title ������������ �����
rem Gans gansek.narod.ru
@param a ���������� ������ 
@default a 5
@param b ����� ������ (���) 
@default b 0
@param c ����� ������ (���) 
@default c 10
@param d �������� ����� ������� (���) 
@default d 0
@param e �������� ����� ������� (���) 
@default e 10

sleep 1000
t=60000*b+1000*c+1000
i=60000*d+1000*e+1000

for s=1 to a
click "shoot_full"
print "������",s,"-� ��",c" �������"
sleep t
click "shoot_full"
print "���",d,"�����",e,"������"
sleep i
next s

print "��������� ���������!"
sleep 2000
end

