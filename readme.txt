Instalacja biblioteki w wybranym folderze (np. zewnętrznego projektu).

Będąc w folderze decisions/build uruchom komendy w tej kolejności (zastąp swoją ścieżką docelową):

cmake .. -DCMAKE_INSTALL_PREFIX=C:\Users\kozoh\source\repos\JKrispel\projektDyplomowy\thirdparty\decisions
cmake --build . --config Debug
cmake --install . --config Debug

UWAGA: Dalej staram się rozwiązać problem nieporządanego instalowania plików biblioteki gtest.