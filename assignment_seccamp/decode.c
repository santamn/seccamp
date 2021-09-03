
void decode(void *addr, int size, char *text, long param_4, int param_5)

{
    void *lVar1;
    char *local_res18;
    int counter;
    long access;
    long value;

    counter = 0;
    local_res18 = text;

    while (counter < size)
    {
        lVar1 = (void *)((long)local_res18 * 5 + 0x2365f703);
        value = param_4 + counter % param_5;
        access = (long)addr + (long)counter;

        if ((0xa0 < (access - 1)) && (*(char *)access != '\0'))
        {
            access -= 1;
        }
        access = access ^ (long)lVar1;

        local_res18 = (char *)(((long)lVar1 >> 2) - 0x1ca9);

        access = access ^ value + value + (long)local_res18;
        counter++;
    }
    return;
}