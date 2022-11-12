void grayscale(unsigned char *buf, int width, int height) {

    int i,j,avg;

    for (i=0; i<width*height; i++) {
        avg = (buf[i*3 + 0] + buf[i*3 + 1] + buf[i*3 + 2])/3;
        buf[i*3 + 0] = avg;
        buf[i*3 + 1] = avg;
        buf[i*3 + 2] = avg;
    }

}