
#include <stdbool.h>
#include <stdio.h>


// typedef struct {
//     float adc_coolant_temp1;
//     float mc_motor_temp;
//     float mc_igbt_temp;
// } TempConfig;

void tempMonitorTask(void){
	//TempConfig *config = (TempConfig *) pvParameters;

	//ALL In celcious 
	float adc_coolant_temp2 = 23;
	float adc_coolant_temp1 = 23;
    float mc_motor_temp = 25;
    float mc_igbt_temp = 25;

	float max_MI_thres = 65;
	float min_MI_thres = 35;
	
	float max_cool_thres = 45;
	float min_cool_thres = 20;

	//optimal theshold estimates

	//coolant 20 - 45
	//motor 40 - 90
	//inverter 35 - 65

	bool is_pump_on = false;
	bool is_fan_on = false;

	for(;;){

		// FOR TESTING

		mc_motor_temp += .1;
		mc_igbt_temp += .1;

		if (is_pump_on){
			adc_coolant_temp1 += .1;
			adc_coolant_temp2 += .1;

			mc_motor_temp -= .2;
			mc_igbt_temp -= .2;
		}

		if (is_fan_on){
			adc_coolant_temp1 -= .2;
			adc_coolant_temp2 -= .2;
		}

		printf("\n");
		printf("MOTOR TEMP (%.2f) ", mc_motor_temp);
		printf("INVERTER TEMP (%.2f) ", mc_igbt_temp);
		printf("COOLANT TEMP (%.2f) ", adc_coolant_temp1);
		printf("COOLANT TEMP 2 (%.2f) ", adc_coolant_temp2);


		if (mc_motor_temp > max_MI_thres || mc_igbt_temp > max_MI_thres){

			if (is_pump_on == false){
				//uvStartCoolantPump();
				

                printf("\n - TURN ON PUMP - ");
				is_pump_on = true;
				printf("pump %d fan %d ", is_pump_on, is_fan_on);
			}


		} else if (mc_motor_temp < min_MI_thres && mc_igbt_temp < min_MI_thres){

			if (is_pump_on == true){
				//uvStopCoolantPump();


                printf("\n - TURN OFF PUMP - ");
				is_pump_on = false;
				printf("pump %d fan %d ", is_pump_on, is_fan_on);
			}

		}

		if (adc_coolant_temp1 > max_cool_thres || adc_coolant_temp2 > max_cool_thres){

			if(is_fan_on == false){
				//uvStartFans(x);


                 printf("\n - TURN ON FAN - ");
				is_fan_on = true;
				 printf("pump %d fan %d ", is_pump_on, is_fan_on);
			}


		} else if (adc_coolant_temp1 < min_cool_thres && adc_coolant_temp2 < min_cool_thres){

			if(is_fan_on == true){
				//uvStopFans(x);


                printf("\n - TURN OFF FAN - ");
				is_fan_on = false;
				printf("pump %d fan %d ", is_pump_on, is_fan_on);
			}

		}

	}
	}

	int main(void) {

        //incroment heat varibles

        //pass through pointers
        //printf("inside main");

        //TempConfig config1 = { .adc_coolant_temp1 = 0, .mc_motor_temp = 0, .mc_igbt_temp = 0};

		tempMonitorTask();

        //xTaskCreate(tempMonitorTask, "Task1", 1000, &config1, 1, NULL);
        //vTaskStartScheduler(); // starts running all tasks concurrently
        
        // for(;;){
        //     config1.adc_coolant_temp1 += 1;
        //     config1.mc_motor_temp += 1;
        //     config1.mc_igbt_temp += 1;
        // }
    
    }
