#include "tube.h"

uchar num_code[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xBF};// ?????0~9????(?????????)

//-----------------------------------------------------------------
//               IO ????
//-----------------------------------------------------------------
//    3641BH         |    51         |   STM32L4
//     Pin1         -->   P0^4			-->	 E53_20_Pin
//     Pin2         -->   P0^3			-->	 E53_19_Pin
//     Pin3         -->   P0^7			-->	 E53_18_Pin
//     Pin4         -->   P0^2			-->	 E53_17_Pin
//     Pin5         -->   P0^6			-->	 E53_16_Pin
//     Pin6         -->   P2^0			-->	 E53_15_Pin
//     Pin7         -->   P0^1			-->	 P58_Pin
//     Pin8         -->   P2^1			-->	 WAN_P32_Pin
//     Pin9         -->   P2^2			-->	 WAN_P33_Pin
//     Pin10        -->   P0^5			-->	 WAN_P34_Pin
//     Pin11        -->   P0^0			-->	 WAN_P35_Pin
//     Pin12        -->   P2^3			-->	 E53_1
//-----------------------------------------------------------------

void delay(unsigned int k)
{
	while(k--);
}

void write_segment_code(uchar num_code_16){
	uchar bin[8];
	bin[7] = num_code_16 / 128;
	bin[6] = num_code_16 / 64 % 2;
	bin[5] = num_code_16 / 32 % 2;
	bin[4] = num_code_16 / 16 % 2;
	bin[3] = num_code_16 / 8 % 2;
	bin[2] = num_code_16 / 4 % 2;
	bin[1] = num_code_16 / 2 % 2;
	bin[0] = num_code_16 % 2;
	if(bin[0]) HAL_GPIO_WritePin(GPIOB, WAN_P35_Pin, GPIO_PIN_SET);
	else HAL_GPIO_WritePin(GPIOB, WAN_P35_Pin, GPIO_PIN_RESET);
	
	if(bin[1]) HAL_GPIO_WritePin(GPIOB, P58_Pin, GPIO_PIN_SET);
	else HAL_GPIO_WritePin(GPIOB, P58_Pin, GPIO_PIN_RESET);
	
	if(bin[2]) HAL_GPIO_WritePin(GPIOC, E53_17_Pin, GPIO_PIN_SET);
	else HAL_GPIO_WritePin(GPIOC, E53_17_Pin, GPIO_PIN_RESET);
	
	if(bin[3]) HAL_GPIO_WritePin(GPIOC, E53_19_Pin, GPIO_PIN_SET);
	else HAL_GPIO_WritePin(GPIOC, E53_19_Pin, GPIO_PIN_RESET);
	
	if(bin[4]) HAL_GPIO_WritePin(GPIOA, E53_20_Pin, GPIO_PIN_SET);
	else HAL_GPIO_WritePin(GPIOA, E53_20_Pin, GPIO_PIN_RESET);
	
	if(bin[5]) HAL_GPIO_WritePin(GPIOC, WAN_P34_Pin, GPIO_PIN_SET);
	else HAL_GPIO_WritePin(GPIOC, WAN_P34_Pin, GPIO_PIN_RESET);
	
	if(bin[6]) HAL_GPIO_WritePin(GPIOA, E53_16_Pin, GPIO_PIN_SET);
	else HAL_GPIO_WritePin(GPIOA, E53_16_Pin, GPIO_PIN_RESET);
	
	if(bin[7]) HAL_GPIO_WritePin(GPIOC, E53_18_Pin, GPIO_PIN_SET);
	else HAL_GPIO_WritePin(GPIOC, E53_18_Pin, GPIO_PIN_RESET);
}

void tube_display(uchar left_end, uchar middle_left, uchar middle_right, uchar right_end, uchar digit){
  HAL_GPIO_WritePin(GPIOA, E53_20_Pin|E53_16_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, P58_Pin|WAN_P35_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOC, E53_19_Pin|E53_18_Pin|E53_17_Pin|WAN_P34_Pin, GPIO_PIN_SET);

	if(digit<1) return;	
  HAL_GPIO_WritePin(GPIOA, E53_1_Pin|WAN_P32_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOC, WAN_P33_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, E53_15_Pin, GPIO_PIN_SET);
	if(digit>=4) write_segment_code(num_code[right_end]); // ????????????1
	else{
		HAL_GPIO_WritePin(GPIOA, E53_20_Pin|E53_16_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, P58_Pin|WAN_P35_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, E53_19_Pin|E53_18_Pin|E53_17_Pin|WAN_P34_Pin, GPIO_PIN_SET);
	}
	delay(500); // ??

  HAL_GPIO_WritePin(GPIOA, E53_20_Pin|E53_16_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, P58_Pin|WAN_P35_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOC, E53_19_Pin|E53_18_Pin|E53_17_Pin|WAN_P34_Pin, GPIO_PIN_SET);

  HAL_GPIO_WritePin(GPIOA, WAN_P32_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, E53_15_Pin|E53_1_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOC, WAN_P33_Pin, GPIO_PIN_RESET);
	if(digit>=3) write_segment_code(num_code[middle_right]); // ????????????2
	else{
		HAL_GPIO_WritePin(GPIOA, E53_20_Pin|E53_16_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, P58_Pin|WAN_P35_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, E53_19_Pin|E53_18_Pin|E53_17_Pin|WAN_P34_Pin, GPIO_PIN_SET);
	}
	delay(500); // ??

  HAL_GPIO_WritePin(GPIOA, E53_20_Pin|E53_16_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, P58_Pin|WAN_P35_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOC, E53_19_Pin|E53_18_Pin|E53_17_Pin|WAN_P34_Pin, GPIO_PIN_SET);

  HAL_GPIO_WritePin(GPIOA, E53_15_Pin|E53_1_Pin|WAN_P32_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOC, WAN_P33_Pin, GPIO_PIN_SET);	
	if(digit>=2) write_segment_code(num_code[middle_left]); // ????????????3
	else{
		HAL_GPIO_WritePin(GPIOA, E53_20_Pin|E53_16_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, P58_Pin|WAN_P35_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, E53_19_Pin|E53_18_Pin|E53_17_Pin|WAN_P34_Pin, GPIO_PIN_SET);
	}
	delay(500); // ??

  HAL_GPIO_WritePin(GPIOA, E53_20_Pin|E53_16_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, P58_Pin|WAN_P35_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOC, E53_19_Pin|E53_18_Pin|E53_17_Pin|WAN_P34_Pin, GPIO_PIN_SET);

  HAL_GPIO_WritePin(GPIOA, E53_15_Pin|WAN_P32_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOC, WAN_P33_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, E53_1_Pin, GPIO_PIN_SET);
	if(digit>=1) write_segment_code(num_code[left_end]); // ????????????4
	else{
		HAL_GPIO_WritePin(GPIOA, E53_20_Pin|E53_16_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, P58_Pin|WAN_P35_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, E53_19_Pin|E53_18_Pin|E53_17_Pin|WAN_P34_Pin, GPIO_PIN_SET);
	}
	delay(500); // ??
}
