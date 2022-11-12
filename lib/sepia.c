void sepia(unsigned char *buf, int width, int height) {

    int i;
    unsigned char r,g,b;

    for (i=0; i<width*height; i++) {

        b = buf[i*3 + 0];
        g = buf[i*3 + 1];
        r = buf[i*3 + 2];

        buf[i*3 + 0] = 0.272*r+ 0.534*g+ 0.131*b > 255? 255 : 0.272*r+0.534*g+0.131*b; //b
        buf[i*3 + 1] = 0.349*r+ 0.686*g+ 0.168*b > 255? 255 : 0.349*r+0.686*g+0.168*b; //g
        buf[i*3 + 2] = 0.393*r+ 0.769*g+ 0.189*b > 255? 255 : 0.393*r+0.769*g+0.189*b; //r
    }

}