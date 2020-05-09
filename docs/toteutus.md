# Toteutusdokumentti

## Ohjelman yleisrakenne

Annettu säännöllinen lauseke muutetaan postfix-muotoon shunting-yard algoritmilla, tämän jälkeen lausekkeen pohjalta muodostetaan NFA käyttäen Thompson's construction algoritmia.

NFA pohjalta muodostetaan tarvittaessa DFA powerset construction algoritmilla.

Ohjelmassa on myös Hopcroftin algoritmi DFA tilojen määrän minimoimiseen.

Kaikki tietorakenteet string ja I/O lukuun ottamatta on toteutettu itse, ja ne sijaitsevat  kansiossa `src/ds`.

## Saavutetut aika- ja tilavaativuudet

Säännöllisen lausekkeen esikäsittely on lineaarinen sekä muisti- että aikavaativuuden kannalta lausekkeen pituuden mukaan.

NFA muodostaminen toteutetaan Thompsonin algoritmilla, jota on kuitenkin hieman muokattu, jotta syöte `.` olisi tehokkaampi. NFA muodostetaan siis lineaarisesti  O(n), jossa n on säännöllisen lausekkeen pituus.

DFA muodostetaan powerset construction algoritmilla, aika- ja tilavaativuus on siis O(2^n), jossa n on NFA tilojen määrä.

Hopcroftia käytetään DFAn minimointiin, joten aika- ja tilavaativuus ovat molemmat O(n log n), jossa n on minimoitavan DFA tilojen määrä.

Muut toteutetut tietorakenteet vastaavat aikavaativuuksiltaan std-kirjaston rakenteita.

## Puutteet ja parannusehdotukset

Tällä hetkellä säännöllisten lausekkeiden parseri tukee vain yksinkertaista syntaksia, joka on kuitenkin ilmaisuvoimaltaan NFA sekä DFA riittävä. Tukea monimutkaisemmille operaatioille, kuten `[a-z]` voisi kuitenkin lisätä, sillä tämä helpottaisi lausekkeiden kirjoittamista. Parseria voisi muutenkin parantaa esim. lisäämällä virheviestejä esim. syötteisiin joissa sulut ovat väärin.

DFA muodostamista voisi tehostaa, sillä vaikka powerset construction tuottaakin pahimmassa tapauksessa 2^n tilaa, voidaan jättää turhia tiloja generoimatta, jolloin useilla syötteillä tiloja tulee huomattavasti vähemmän, mahdollistaen DFA muodostamisen suuremmista syötteistä.

Ohjelma tukee vain ASCII-aakkostoa, tuen suuremmalle aakkostolle kuten UTF-8 saisi kuitenkin helposti lisättyä juurikaan koskematta algoritmien toteutuksiin. Aika- ja tilavaativuudet sekä yleinen suorituskyky saattaisivat kuitenkin kärsiä, jos aakkoston koko olisi vapaasti valittavissa.

### Lähteet

[Hopcroft, J. (1971). an n log n algorithm for minimizing states in a finite automaton](https://www.cs.cmu.edu/~cdm/resources/Hopcroft71.pdf)

[Thompson's construction](https://en.wikipedia.org/wiki/Thompson%27s_construction)

[Shunting-yard algorithm](https://en.wikipedia.org/wiki/Shunting-yard_algorithm)
