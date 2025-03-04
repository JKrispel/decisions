Instalacja biblioteki w wybranym folderze (np. zewnętrznego projektu).

Będąc w folderze decisions/build uruchom komendy w tej kolejności (zastąp swoją ścieżką docelową):

cmake .. -DCMAKE_INSTALL_PREFIX=C:/Users/kozoh/source/repos/JKrispel/DecideQuickly/external/decisions
cmake --build . --target install

UWAGA: Dalej staram się rozwiązać problem niepożądanego instalowania plików biblioteki gtest.