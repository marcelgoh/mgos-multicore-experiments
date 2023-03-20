/* Copied from https://community.mongoose-os.com/t/here-is-a-freertos-example/945 and then adapted
 * to support multiple cores.
 */

#include "mgos_app.h"
#include "mgos_gpio.h"

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"



const uint8_t LED12 = 12;
const uint8_t LED13 = 13;
const uint8_t LED14 = 14;

typedef struct params_s
{
  uint16_t ticks;
  uint8_t led;
} params_t, *p_params_t;

static void vLEDTask(void* pvParameters)
{
    p_params_t pParams = (p_params_t) pvParameters;

    bool on = true;
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = pParams->ticks / portTICK_PERIOD_MS;

     // Initialise the xLastWakeTime variable with the current time.
     xLastWakeTime = xTaskGetTickCount();

     for(;;)
     {
       on = !on;
       mgos_gpio_write(pParams->led, on);

       vTaskDelayUntil(&xLastWakeTime, xFrequency);
     }
}


// Entry point to app
enum mgos_app_init_result mgos_app_init(void)
{
  mgos_gpio_set_mode(LED12, MGOS_GPIO_MODE_OUTPUT);
  mgos_gpio_set_mode(LED13, MGOS_GPIO_MODE_OUTPUT);
  //mgos_gpio_set_mode(LED14, MGOS_GPIO_MODE_OUTPUT);

  p_params_t pParams1 = (p_params_t) malloc(sizeof(params_t));
  pParams1->led = LED12;
  pParams1->ticks = 1000;

  xTaskCreate(vLEDTask, "LED12", 500, pParams1, 1, NULL );

  p_params_t pParams2 = (p_params_t) malloc(sizeof(params_t));
  pParams2->led = LED13;
  pParams2->ticks = 250;

  xTaskCreate(vLEDTask, "LED13", 500, pParams2, 1, NULL );

  return MGOS_APP_INIT_SUCCESS;
}
