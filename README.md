Inainte de main(), am scris cinci functii: prelucrare(), conversie(), ecuatia_dreptei(), colorare_poza() si umplere().
Prima functie citeste inputul, transformand caracterele NEWLINE in spatii pentru a
putea parcurge mai usor sirul dat. Functia conversie() parcurge un numar care este 
citit drept un sir de caractere, transformandu-l intr-un int si returnandu-l. Functia 
ecuatia_dreptei() calculeza coordonatele ce apartin unei drepte (aceasta fiind 
linia dintre doua puncte). Se afla unde se gaseste intervalul maxim al punctelor
(pe axa Oy sau Ox), iar, ulterior, se procedeaza conform formulei date in enuntul problemei.
A patra functie, colorare_poza(), parcurge lungimea vectorilor ce contin coordonatele dreptei,
modificand in matricea de pixeli culoarea asociata acelor coordonate.
Totodata, modificarea culorii se produce si pe urma formata de creion (marime_creion = line_width).
Ultima functie, umplere(), parcurge recursiv vecinii unui pixel (sus, jos, stanga,
dreapta), modifcandu-le culoarea atunci cand aceasta este egala cu cea a pixelului initial iar
umplerea se realizeaza de mai multe ori. Daca se doreste umplerea intregii poze se 
parcurge vectorul pixeli1 prin doua whileuri, inlocuindu-se acolo unde se afla culoarea
veche cu cea noua.

In main() se aloca dinamic sirul primit ca input, *comanda si sirul *cuvant, care, folosindu-se de
functia strtok imparte sirul in cuvinte, inlocuind cu \0 acolo unde se afla spatii pentru a 
putea fi parcurs mai usor.  In continuare, se aloca dinamic doi vectori ce reprezinta matricile
de pixeli din doua fisiere diferite si doi vectori ce contin coordonatele dreptei (pe Ox si Oy).
Todata, se aloca dinamic sirul de caractere copie (care este copia comenzii) si sirul fill,
folosit pentru a determina cati pixeli umplu imaginea.
Se transforma sirul *comanda folosind functia prelucrare() si se intra intr-un while ce se 
opreste atunci cand nu mai are nimic de citit sau primeste comanda "quit". In cadrul acestuia
se afla mai multe ifuri.

Task 1

Pentru taskul 1, programul copiaza o poza, deschizand un fisier in mod binar din care se citesc 
structurile de date ce contin detalii pretioase  despre aceasta (marimea pozei, marimea fisierului), 
si atribuindu-i vectorului pixeli1 matricea de pixeli a pozei. Atunci cand se apeleaza comanda save, 
structurile de date si vectorul pixeli1 sunt scrisi intr-un alt fisier output,
copiandu-se astfel poza din primul fisier. 

Task 2

Pentru taskul 2, in al doilea if se insereaza o poza peste cea primita in primul if. 
Astfel, se deschide al doilea fisier si se citesc informatiile despre poza inserata 
(structurile si vectorul de pixeli). In continuare sunt citite coordonatele de unde 
se vor suprascrie pixelii din prima poza cu cei din a doua. Aceasta operatiune o realizeaza
while-ul urmator ce inlocuieste octetii lui pixeli1 cu cei ai lui pixeli2 pana ce 
se insereaza poza complet.

Task 3

Pentru taskul 3, se citeste culoarea cu care vrem sa coloram imaginea (sunt trei culori pentru
fiecare canal R G B) si marimea creionului cu care vom ingrosa liniile pe care le desenam. 
In functie de ce input primim, se pot desena linii, triunghiuri si dreptunghiuri, fiecarei
figuri geometrice fiindu-i asociat cate un if. In iful creat pentru trasarea unei linii 
se citesc patru coordonate si se apeleaza o data functiile ecuatia_dreptei() si colorare_poza() 
explicate anterior.
In iful destinat construirii unui triunghi se citesc sase coordonate si se apeleaza functiile
ecuatia_dreptei() si colorare_poza() de trei ori (apelate de trei ori pentru a fi trasate trei linii).
In iful gandit pentru desenarea unui dreptunghi sunt citite coordanetele unui varf al acestuia 
si latimea si inaltimea lui. Avand aceste informatii despre dreptunghi, se afla si celelalte 
varfuri ale acestuia, iar, in final, se apeleaza functiile ecuatia_dreptei() si colorare_poza() 
de patru ori.

Task 4

Pentru taskul 4, se citesc coordonatele unui pixel, a carui culoare va fi inlocuita peste tot 
in matricea de pixeli pana la intalnirea altei culori. Ulterior se apeleaza functia umplere(),
explicata anterior.

La final, cand se apeleaza comanda "quit", se iese din while si se elibereaza memoria
alocata dinamic.