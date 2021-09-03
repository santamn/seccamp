void decode(void *addr, int size, longlong data, char *text, int text_len)

{
    void *lVar1;
    longlong local_res18;
    int counter;

    counter = 0;
    local_res18 = data;
    while (counter < size)
    {
        lVar1 = (void *)(local_res18 * 5 + 0x2365f703);
        if ((0xa0 < (byte)(*(char *)((longlong)addr + (longlong)counter) - 1U)) &&
            (*(char *)((longlong)addr + (longlong)counter) != '\0'))
        {
            *(char *)((longlong)addr + (longlong)counter) =
                *(char *)((longlong)addr + (longlong)counter) + -1;
        }
        *(byte *)((longlong)addr + (longlong)counter) =
            *(byte *)((longlong)addr + (longlong)counter) ^ (byte)lVar1;
        local_res18 = ((longlong)lVar1 >> 2) + -0x1ca9;
        *(byte *)((longlong)addr + (longlong)counter) =
            *(byte *)((longlong)addr + (longlong)counter) ^
            text[counter % text_len] + text[counter % text_len] + (char)local_res18;
        counter = counter + 1;
    }
    return;
}