/*
*********************************************************************************************************
*
*	ģ������ : BSPģ��(For STM32F4XX)
*	�ļ����� : bsp.c
*	��    �� : V1.1
*	˵    �� : ����Ӳ���ײ�������������ļ���ÿ��c�ļ����� #include "bsp.h" ���������е���������ģ�顣
*			   bsp = Borad surport packet �弶֧�ְ�
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    2013-03-01  armfly   ��ʽ����
*		V1.1    2013-06-20  armfly   �淶ע�ͣ����ӱ�Ҫ˵��
*
*	Copyright (C), 2013-2014, ���������� www.armfly.com
*
*********************************************************************************************************
*/
#include "includes.h"
#include "MainTask.h"

//extern GUI_CONST_STORAGE GUI_FONT GUI_Fontsong36;
/*
*********************************************************************************************************
*	�� �� ��: bsp_Init
*	����˵��: ��ʼ�����е�Ӳ���豸���ú�������CPU�Ĵ���������ļĴ�������ʼ��һЩȫ�ֱ�����ֻ��Ҫ����һ��
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_Init(void)
{
//	FATFS fs;
//	FRESULT result;
	/*
		����ST�̼���������ļ��Ѿ�ִ����CPUϵͳʱ�ӵĳ�ʼ�������Բ����ٴ��ظ�����ϵͳʱ�ӡ�
		�����ļ�������CPU��ʱ��Ƶ�ʡ��ڲ�Flash�����ٶȺͿ�ѡ���ⲿSRAM FSMC��ʼ����

		ϵͳʱ��ȱʡ����Ϊ168MHz�������Ҫ���ģ������޸� system_stm32f4xx.c �ļ�
	*/
	/* ʹ��CRC ��Ϊʹ��STemWinǰ����Ҫʹ�� */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);
	
	/* ���ȼ���������Ϊ4��������0-15����ռʽ���ȼ���0�������ȼ����������������ȼ���*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
	SystemCoreClockUpdate();	/* ����PLL���ø���ϵͳʱ��Ƶ�ʱ��� SystemCoreClock */

	bsp_InitDWT();       /* ��ʼDWT */
	bsp_InitUart(); 	/* ��ʼ������ */
	bsp_InitKey();		/* ��ʼ������������������ bsp_InitTimer() ֮ǰ���ã� */
	
	bsp_InitExtIO();    /* FMC��������չ��32λ���IO, ����LED����������ʼ�� */
	bsp_InitLed(); 		/* ��ʼLEDָʾ�ƶ˿� */
	
	bsp_InitI2C();		/* ����I2C���� */
	bsp_InitSPIBus();	/* ����SPI���� */
	
	bsp_InitSFlash();   /* ��ʼ��SPI Flash */
	
	bsp_InitExtSDRAM();
//	bsp_DetectLcdType(); /* ��ⴥ�����LCD����ͺ�, �������ȫ�ֱ��� g_TouchType, g_LcdType */
	
//	TOUCH_InitHard();	 /* ��ʼ�����ô���оƬ */
	LCD_ConfigLTDC();    /* ��ʼ������LTDC */
	BEEP_InitHard();
	
	can1_Init();			/* ��ʼ��STM32 CAN1Ӳ�� */
	can1_NVIC_Config();		/* ����CAN1�ж� */
	
//	result = f_mount(&fs, "0:/", 0); 	/* �����ļ�ϵͳ */
}

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/