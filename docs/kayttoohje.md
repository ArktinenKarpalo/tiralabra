Koodin voi kääntää suorittamalla build.sh tiedoston.
Kääntämiseen tarvitaan vähintään version 3.10 CMake ja g++ c++17 tuella, esim. versio 9.3.0

Ohjelman voi suorittaa sijainnista `./build/src/tiralabra_run`

Testit suoritetaan sijainnista `./build/test/test`

Testikattavuuden voi tämän jälkeen tarkistaa `gcovr -r ./src/ ./build` komennolla.

Huom. git submodulejen takia on syytä käyttää esim. `--recurse-submodules` argumenttia.

Päivitetty 28.3.
