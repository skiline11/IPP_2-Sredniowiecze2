AI mockowane przez coś, co oczekuje na dany input i tyle linijek czyta i zapisuje oraz wypisuje podane polecenia.
GUI mockowane przez coś, co oczekuje na dane, zapisuje je oraz wypisuje podane polecenia.
gui.in z byle czym (np. INIT ???) służy do tego, by nie było porównywane co do poprawności, ale by mock GUI wiedział, kiedy ma przestać czytać i się zakończyć.
1. 1 tura AI vs AI
2. 1 tura AI vs HUMAN
3. 1 tura HUMAN vs AI
4. 1 tura HUMAN vs HUMAN
5. HUMAN vs HUMAN do wygranej pierwszego
6. AI vs HUMAN do wygranej HUMAN
7. HUMAN vs AI do wygranej AI + k=MAX
8. AI vs AI do wygranej drugiego + n=MAX
9. Czy z -s 3 gra AI 3-turowa trwa ok. 15 sekund (6 END_TURN)
10. Dłuższa rozgrywka AI vs AI z remisem, 2000 tur
11. Dłuższa rozgrywka AI vs AI z wygraną pierwszego, 1000 tur
12. Default n, k, s, HUMAN vs HUMAN, nic nie robienie, draw
13. Sprawdzenie losowości -p1 i -p2 - czy różne conajmniej 8 initów w kolejnych 8 rozgrywkach (16 wiadomościach INIT), na AI studenta
14. Sprawdzenie losowości -p1 przy ustalonym -p2 - czy różne conajmniej 5 initów w kolejnych 8 rozgrywkach (16 wiadomościach INIT), na AI studenta
15. Sprawdzenie losowości -p1 przy ustalonym -p2 - czy różne conajmniej 5 initów w kolejnych 8 rozgrywkach (16 wiadomościach INIT), na AI studenta
16. Czy skrypt się nie zawiesza dla -n i -p1 takiego, że nie ma jak dobrać poprawnego -p2
17. Czy dla -p1 z pustym argumentem kończy się z kodem 1
18. Czy dla -n tekst kończy sie z kodem 1
19. Czy dla -n 18a kończy się z kodem 1
20. Czy dla -n 4500000000 kończy się z kodem 1
21. Czy dla -p1 1;2 kończy się z kodem 1
22. Wykrycie niepoprawnego argumentu (-x 1)
23. Czy dla -ai1 będącym złym plikiem (nie wykonywalnym), a -ai2 nieistniejącym kończy się z kodem 1
24. Czy w AI vs AI, przy złym inpucie od AI1, wszystko się poprawnie kończy z kodem 1
25. Czy w HUMAN vs AI, przy crashu AI, wszystko się poprawnie kończy z kodem 1
26. Brak zostających procesów w tle 3 sekundy po normalnym zakończeniu gry
27. Usuniety.
28. Kończenie programu po wczesnym poprawnym zakończeniu GUI z AI-mockami (robiącymi podprocesy)
29. Walka mock AI vs AI studenta wygrana przez AI studenta
30. Sprawdzenie poprawności zwracanego kodu przez AI studenta dla remisu przez wyczerpanie tur (1)
31. Sprawdzenie poprawności zwracanego kodu przez AI studenta dla remisu przez walkę król vs król (1)
32. Sprawdzenie poprawności zwracanego kodu przez AI studenta dla przegranej (2)
33. Sprawdzenie poprawności zwracanego kodu przez AI studenta dla błędnego wejścia (42)
34. Sprawdzenie poprawności zwracanego kodu przez AI studenta dla wygranej (0)
