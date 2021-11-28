
    puts("### Melakukan UNDO ###");
    Pop(&Round, &ArrPlayer);
    Pop(&Round, &ArrPlayer);
    puts("### Hasil UNDO ###");
    for (int i = 0; i < jumlahPlayer; i++)
    {
        RandomSkill(&(PlayerSkills(ArrayPlayer(ArrPlayer)[i])), i);
    }
    for (int i = 0; i < jumlahPlayer; i++)
    {
        printf("Menu skill Player ke %d\n", i + 1);
        PrintMenuSkill((PlayerSkills(ArrayPlayer(ArrPlayer)[i])));
        puts("");
    }