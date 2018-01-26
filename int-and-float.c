/*C program 
	to print integer
	and floating point numbers
	from a given text file..
	*
	*
	*
 	@author vivek */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#define MAXSIZE 100

int main()
{
	FILE *fp = fopen("source.txt", "r");
	char item;
	long int i_value, d_factor, flag = 0, err_flag = 0;
	double d_value;
	
	item = fgetc(fp);
	while( item != EOF ){
		
		//digit maybe an integer or floating point...
		if( isdigit(item) ){
			err_flag = 0;
			flag = 0;
			i_value = 0;
			while( isdigit(item) ){
				i_value = ( i_value * 10 ) + ( item - '0' );
				item = fgetc(fp);
				
				//'e' menas the digit may be real..
				if( item == 'e' ){
					item = fgetc(fp);
					//case: 'e+' or 'e-'...
					//otherwise not a real number...
					//case: 'e+' means an integer...
					if( item == '+' ){
						//case: must be an integer...
						item = fgetc(fp);
						if( isdigit(item) ){
							d_factor = 0;
							//to fetch the exponential power..
							while( isdigit(item) ){
								d_factor = ( d_factor * 10 ) + ( item - '0' );
								item = fgetc(fp);
							}
							printf("INTEGER: %lde+%ld\n", i_value, d_factor);
						}
						else{
							err_flag = 1;
							break;
						}
					}
					//case: 'e-' means real...
					if( item == '-' ){
						//case: must be an integer...
						item = fgetc(fp);
						if( isdigit(item) ){
							d_factor = 0;
							//to fetch the exponential power..
							while( isdigit(item) ){
								d_factor = ( d_factor * 10 ) + ( item - '0' );
								item = fgetc(fp);
							}
							d_value = i_value;
							printf("REAL: %fe-%ld\n", d_value, d_factor);
						}
						else{
							err_flag = 1;
							break;
						}
					}
					else{
						err_flag = 1;
						break;
					}
				}
				
				//'.' means the digit may be a floating point...
				if( item == '.' ){
					flag = 1;
					item = fgetc(fp);
					//case: 165989.
					if( !isdigit(item) ){
						printf("INTEGER: %ld\n", i_value);
						break;
					}
					//case: 98941.32659
					d_factor = 10;
					d_value = (double)( item - '0' ) / d_factor;
					while( isdigit(item) ){
						d_factor *= 10;
						d_value += (double)( item - '0' ) / d_factor;
						item = fgetc(fp);
						//case: 15898.265.656
						if( item == '.' ){
							err_flag = 1;
							break;
						}
						
						//case: 149.326e+or-898
						if( item == 'e' ){
							item = fgetc(fp);
							//item must be '+' or '-'
							if( item == '+' ){
								//item must be an integer
								item = fgetc(fp);
								if( !isdigit(item) ){
									err_flag = 1;
									break;
								}
								else{
									d_value = d_value + (double)i_value;
									d_factor = 0;
									while( isdigit(item) ){
										d_factor = ( d_factor * 10 ) + ( item - '0' );
										item = fgetc(fp);
									}
									printf("REAL: %fe+%ld\n", d_value, d_factor);
									break;
								}
							}
							if( item == '-' ){
								//item must be an integer
								item = fgetc(fp);
								if( !isdigit(item) ){
									err_flag = 1;
									break;
								}
								else{
									d_value = d_value + (double)i_value;
									d_factor = 0;
									while( isdigit(item) ){
										d_factor = ( d_factor * 10 ) + ( item - '0' );
										item = fgetc(fp);
									}
									printf("REAL: %fe-%ld\n", d_value, d_factor);
									break;
								}
							}
							else{
								err_flag = 1;
								break;
							}
						}	
					}
					if( err_flag == 0 ){
						printf("REAL: %f\n", (double)i_value + d_value);
						break;	
					}
				}
			}
			if( flag == 0 && err_flag == 0 ){
				printf("INTEGER: %ld\n", i_value);
			}
		}
		
		item = fgetc(fp);
	}
	return 0;
}
