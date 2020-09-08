static void set_int_in_char(unsigned char *start, int value)
{
    start[0] = (unsigned char)(value);
    start[1] = (unsigned char)(value >> 8);
    start[2] = (unsigned char)(value >> 16);
    start[3] = (unsigned char)(value >> 24);
}
static int  get_color(t_cub *cub, int x, int y)
{
    int rgb;
    int color;
    color = *(int*)(cub->data
        + (4 * (int)cub->width * ((int)cub->height - 1 - y))
        + (4 * x));
    rgb = (color & 0xFF0000) | (color & 0x00FF00) | (color & 0x0000FF);
    return (rgb);
}
static int  write_bmp_header(int fd, int filesize, t_cub *cub)
{
    int             i;
    unsigned char   bmpfileheader[54];
    i = 0;
    while (i < 54)
        bmpfileheader[i++] = (unsigned char)(0);
    bmpfileheader[0] = (unsigned char)('B');
    bmpfileheader[1] = (unsigned char)('M');
    set_int_in_char(bmpfileheader + 2, filesize);
    bmpfileheader[10] = (unsigned char)(54);
    bmpfileheader[14] = (unsigned char)(40);
    set_int_in_char(bmpfileheader + 18, cub->width);
    set_int_in_char(bmpfileheader + 22, cub->height);
    bmpfileheader[27] = (unsigned char)(1);
    bmpfileheader[28] = (unsigned char)(24);
    return (!(write(fd, bmpfileheader, 54) < 0));
}
static int  write_bmp_data(int file, t_cub *cub, int pad)
{
    const unsigned char zero[3] = {0, 0, 0};
    int                 y;
    int                 x;
    int                 color;
    y = 0;
    while (y < (int)cub->height)
    {
        x = 0;
        while (x < (int)cub->width)
        {
            color = get_color(cub, x, y);
            if (write(file, &color, 3) < 0)
                return (0);
            if (pad > 0)
                write(file, &zero, pad);
            x++;
        }
        y++;
    }
    return (1);
}
void        ft_screenshot(t_cub *cub)
{
    int file;
    int filesize;
    int pad;
    pad = (4 - ((int)cub->width * 3) % 4) % 4;
    filesize = 54 + (3 * ((int)cub->width + pad) * (int)cub->height);
    if ((file = open("screenshot.bmp", O_WRONLY | O_CREAT
        | O_TRUNC | O_APPEND, 777)) < 0)
        ft_error();
    if (!write_bmp_header(file, filesize, cub))
        ft_error();
    if (!write_bmp_data(file, cub, pad))
        ft_error();
    close(file);
}
