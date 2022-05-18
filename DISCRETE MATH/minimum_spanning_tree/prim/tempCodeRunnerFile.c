printf("%18s", "VERTICES:");
    for (int v = 1; v <= vertices; v++)
    {
        printf("%3d ", v);
    }
    printf("\n");
    printf("%18s", "PREVIOUS VERTEX:");
    for (int i = 1; i <= vertices; i++)
    {
        printf("%3d ", prev[i]); //PREVIOUS VERTEX
    }
    printf("\n");
    printf("%18s", "SHORTEST DISTANCE:");
    for (int i = 1; i <= vertices; i++)
    {
        printf("%3d ", d[i]); //DISTANCE
    }
    printf("\n");