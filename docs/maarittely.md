Työn tarkoituksena on toteuttaa säännöllisten lauseiden tulkki C++:lla.

Tulkki toteutetaan useammalla eri algoritmilla, ja algoritmien tehokkuutta mitataan erilaisilla syötteillä.
Säännöllisestä lausekkeesta muodostetaan NFA Thompsonin konstruktiolla.
NFA Muutetaan DFA Robin-Scott powerset konstruktiolla.
DFA tilojen määrä vielä minimoidaan Hopcroftin algoritmilla.

Syötteeksi ohjelma saa säännöllisen lausekkeen, joka koostuu syntaksista . a-z * () |, sekä merkkijonoja. Ohjelma tulostaa ne merkkijonot, jotka ovat osa säännöllisen lausekkeen kuvaamaa kieltä.

Aikavaativuudet NFA muodostamiseen O(n), jossa n on säännöllisen lausekkeen pituus edellä mainitulla syntaksilla. Thompsonin NFA käyttö merkkijonon tunnistamiseen O(nm), jossa n tilojen määrä ja m merkkijonon pituus. DFA muodostamiseen NFA:sta O(2^n), jossa n NFA tilojen määrä ja DFA käyttö merkkijonon tunnistamiseen  O(m), jossa m merkkijonon pituus. Hopcroftilla DFA minimointi O(nm log n), jossa n on minimoitavan DFA tilojen määrä ja m aakkoston koko.

Lähteet: wikipedia, Introduction to automata theory, languages, and computation Hopcroft
