# Testaus

## Testauksen toteutus

Testaus on automatisoitu gtest-kirjastolla.

Kansio `test` sisältää testaukseen käytettävät tiedostot, jotka käännetään erilliseksi suoritettavaksi ohjelmaksi. Käyttöohje sisältää ohjeet ohjelman kääntämiseen, kääntämisen jälkeen riittää suorittaa `test/test_all` tiedosto.

Ohjelman tietorakenteita testataan yksikkötestein, ja muita algoritmeja kattavammin testein, jotka testaavat koko algoritmin toimintaa useilla eri syötteillä, lukien tiedostosta esilasketut odotetut tulokset. Muistin käytön ja vapautuksen toimivuutta on testattu valgrindillä.


## Suorituskykytestaus

Ohjelmassa toteutettujen algoritmien suorituskyky on kuitenkin vaikeahkosti testattavissa, sillä erityisesti DFA tietyt syötteet saattavat aiheuttaa eksponentiaalisen määrän tiloja, mutta näin ei käytännössä käy kovin usein.

Suorituskyvyn testaamiseen on kuitenkin joitain testejä kansiossa `test_perf/`. Ohjeet koodin suorittamiseen ovat käyttöohjeessa. Suorituskykytesteissä etsitään erinäisiä sanoja englanninkielisestä sanalistasta sekä kirjasta "The World Factbook".


## Rivikattavuus

Testien rivikattavuus generoidaan automaattisesti, ja on seurattavissa codecovilla.

![codecov](https://codecov.io/gh/ArktinenKarpalo/tiralabra/branch/master/graph/badge.svg)