Kääntämiseen tarvitaan vähintään version 3.10 CMake ja c++17 tukeva g++, esim. versio 9.3.0

```
mkdir -p build/
cd build
cmake ..
make
```

Ohjelman voi suorittaa sijainnista `build/src/tiralabra_run`

Syntaksina säännölliselle lausekkeilla ovat operaattorit `(, ), |, *, ., \` sekä ASCII-merkistö.

Testit suoritetaan menemällä kansioon `build/test/` ja suorittamalla `./test_all`

Testikattavuus vaatii -Dcoverage=ON flagin, ja kattavuuden saa generoitua esim. gcovr-ohjelmalla esim. seuraavasti
```
mkdir -p build/
cd build
cmake .. -Dcoverage=ON
make test_all
cd test
./test_all
gcovr -r ../../src/ ..
```

Suorituskykytestit voi suorittaa sijainnista `build/test_perf/test_perf`.

Huom. git submodulejen takia on syytä käyttää esim. `--recurse-submodules` argumenttia git clonessa.

Päivitetty 9.5.
