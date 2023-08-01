#include <stdio.h>
#include "bmp.h"

int main(){
	const int WIDTH = 1024;
	const int HEIGHT = 1024;
	int MAX_ITER = 1000;

	double SX = -1.0f;
	double EX = 1.0f;
	double SY = -1.5f;
	double EY = 0.5f;

	double range_x = EX-SX;
	double range_y = EY-SY;

	double step_x = range_x / (double)WIDTH;
	double step_y = range_y / (double)HEIGHT;

	bmp img;
	bmp_init(&img, "img.bmp", WIDTH, HEIGHT);
	bmp_write_header(&img);
	
	static char pixbuff[WIDTH*HEIGHT*3];
	bmp_buff buff;
	bmp_buff_init(&buff, &img, pixbuff);
	for(int i=0; i<WIDTH; ++i){
		for(int j=0; j<HEIGHT; ++j){
			double y0 = SX + ((double)i)*step_x;
			double x0 = SY + ((double)j)*step_y;
			double x = 0.0f;
			double y = 0.0f;
			int iter = 0;

			while( (x*x+y*y)<=4 && iter<MAX_ITER ){
				double xtemp = x*x-y*y+x0;
				y = 2*x*y+y0;
				x = xtemp;
				++iter;
			}


			if(iter<MAX_ITER)
				bmp_buff_push_pixel(&buff, 0xffffff);
			else
				bmp_buff_push_pixel(&buff, 0x000000);
		}
		//bmp_buff_write(&buff);
		//bmp_buff_reset(&buff);
	}
	
	bmp_buff_write(&buff);
	bmp_free(&img);

	return 0;
}


int main2(){
	bmp img;
	bmp_init(&img, "img.bmp", 8, 8);
	bmp_write_header(&img);
	
	char pixbuff[1024];
	bmp_buff buff;
	bmp_buff_init(&buff, &img, pixbuff);
	for(int i=0; i<8; ++i){
		for(int j=0; j<8; ++j){
			if( (j+i)%3==0)
				bmp_buff_push_pixel(&buff, 0xffffff);
			else
				bmp_buff_push_pixel(&buff, 0xaaaaaa);
		}
		bmp_buff_write(&buff);
		bmp_buff_reset(&buff);
	}

	bmp_free(&img);

	return 0;
}

