int getNbCards(string exp)
{
    int res = 0, ranks=0, suits=0;
    for (auto &c : exp)
    {
        switch(c)
        {
            case '2':  
            case '3':
            case '4':  
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case 'T':
            case 'J':
            case 'Q':
            case 'K':
            case 'A':
                ranks++;
                break;
            case 'C':
            case 'D':
            case 'H':
            case 'S':
                suits++;
                break;

        }
    }

    if(ranks == 0) ranks = 13;
    if(suits == 0) suits = 4;

    return suits*ranks;
}