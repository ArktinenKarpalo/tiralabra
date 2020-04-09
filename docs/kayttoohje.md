Kääntämiseen tarvitaan vähintään version 3.10 CMake ja g++ c++17 tuella, esim. versio 9.3.0

```
mkdir -p build/
cd build
cmake ..
make
```

Ohjelman voi suorittaa sijainnista `./build/src/tiralabra_run`

Testit suoritetaan sijainnista `./build/test/test_all`

Testikattavuus vaatii -Dcoverage=ON flagin, ja kattavuuden saa generoitua esim. gcovr-komenolla esim. seuraavasti
```
mkdir -p build/
cd build
cmake .. -Dcoverage=ON
make test_all
./test/test_all
gcovr -r ../src/ .
```
Huom. git submodulejen takia on syytä käyttää esim. `--recurse-submodules` argumenttia.

Päivitetty 9.4.
