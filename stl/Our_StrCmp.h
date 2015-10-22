
int our_strcmp (const char * a, const char * b)
{
    int val = 0;
    do {
        val = *a - *b;
        if (val || (*a == '\0' && *b == '\0')) {
            break;
        }
        ++a; ++b;
    } while (true);
    return val;
}

