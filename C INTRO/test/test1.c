bool word_check(int a, int b)
{
    for (int i = 0; i < 26; i++)
    {
        occurences[i] = 0;
    }

    for (int i = 1; i < 5; i++)
    {
        int s = letters[a][i] - 97;
        occurences[s]++;
    }

    int count = 0;
    for (int i = 0; i < 5; i++)
    {
        int s = letters[b][i] - 97;
        if (occurences[s] > 0)
        {
            occurences[s]--;
            count++;
        }
    }

    if (count == 4)
        return true;
    return false;
}