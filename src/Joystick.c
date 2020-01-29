/*
Nintendo Switch Fightstick - Proof-of-Concept

Based on the LUFA library's Low-Level Joystick Demo
	(C) Dean Camera
Based on the HORI's Pokken Tournament Pro Pad design
	(C) HORI

This project implements a modified version of HORI's Pokken Tournament Pro Pad
USB descriptors to allow for the creation of custom controllers for the
Nintendo Switch. This also works to a limited degree on the PS3.

Since System Update v3.0.0, the Nintendo Switch recognizes the Pokken
Tournament Pro Pad as a Pro Controller. Physical design limitations prevent
the Pokken Controller from functioning at the same level as the Pro
Controller. However, by default most of the descriptors are there, with the
exception of Home and Capture. Descriptor modification allows us to unlock
these buttons for our use.
*/
#include "asis.h"
#include "script_config.h"
#include "Joystick.h"

#define ECHOES 2
#define LED_PORT 0x40 //Teensy2.0 uses PD6
bool asis_done = false;
bool asis_overflow = false;
int echoes = 0;
uint16_t asis_wc = 0;
USB_JoystickReport_Input_t last_report;
asis_packet_t packet;

void set_led(int on){
  PORTD = on ? LED_PORT : 0;
}
// Main entry point.
int main(void) {
  // Hardware and peripheral setup, enable interrupt
	SetupHardware();
	GlobalInterruptEnable();
  
  //Initialize ASIS
  asis_sys_init();
  //Call the global script setup
  asis_sys_main();
  //Prepare ASIS to run
  asis_sys_prepare();
  //Check compile time overflow
  asis_sys_ovfl(&asis_overflow);
  if(asis_overflow){
    //We indicate a compile time overflow by flashing LED twice
    while(1){
      set_led(1);
      _delay_ms(100);
      set_led(0);
      _delay_ms(100);
      set_led(1);
      _delay_ms(100);
      set_led(0);
      _delay_ms(1000);
    }
  }
	while (1)
	{
    if(asis_overflow){
      //We indicate a run time overflow by flashing LED 3 times
      while(1){
        set_led(1);
        _delay_ms(100);
        set_led(0);
        _delay_ms(100);
        set_led(1);
        _delay_ms(100);
        set_led(0);
        _delay_ms(100);
        set_led(1);
        _delay_ms(1000);
        set_led(0);
        _delay_ms(1000);
      }
    }
    
		// We need to run our task to process and deliver data for our IN and OUT endpoints.
		HID_Task();
		// We also need to run the main USB management task.
		USB_USBTask();
	}
}


// Configures hardware and peripherals, such as the USB peripherals.
void SetupHardware(void) {
	// We need to disable watchdog if enabled by bootloader/fuses.
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	// We need to disable clock division before initializing the USB hardware.
	clock_prescale_set(clock_div_1);
	// We can then initialize our hardware and peripherals, including the USB stack.
  // LED Setup
  DDRD  = LED_PORT;
  set_led(0);

	USB_Init();
}

// Fired to indicate that the device is enumerating.
void EVENT_USB_Device_Connect(void) {
	// We can indicate that we're enumerating here (via status LEDs, sound, etc.).
}

// Fired to indicate that the device is no longer connected to a host.
void EVENT_USB_Device_Disconnect(void) {
	// We can indicate that our device is not ready (via status LEDs, sound, etc.).
}

// Fired when the host set the current configuration of the USB device after enumeration.
void EVENT_USB_Device_ConfigurationChanged(void) {
	bool ConfigSuccess = true;

	// We setup the HID report endpoints.
	ConfigSuccess &= Endpoint_ConfigureEndpoint(JOYSTICK_OUT_EPADDR, EP_TYPE_INTERRUPT, JOYSTICK_EPSIZE, 1);
	ConfigSuccess &= Endpoint_ConfigureEndpoint(JOYSTICK_IN_EPADDR, EP_TYPE_INTERRUPT, JOYSTICK_EPSIZE, 1);

	// We can read ConfigSuccess to indicate a success or failure at this point.
}

// Process control requests sent to the device from the USB host.
void EVENT_USB_Device_ControlRequest(void) {
	// We can handle two control requests: a GetReport and a SetReport.
	// Not used here, it looks like we don't receive control request from the Switch.
}

// Process and deliver data from IN and OUT endpoints.
void HID_Task(void) {
	// If the device isn't connected and properly configured, we can't do anything here.
	if (USB_DeviceState != DEVICE_STATE_Configured)
		return;

  // Clear the out endpoint because we don't need it
	Endpoint_SelectEndpoint(JOYSTICK_OUT_EPADDR);
	if (Endpoint_IsOUTReceived())
	{
		Endpoint_ClearOUT();
	}

	// We'll then move on to the IN endpoint.
	Endpoint_SelectEndpoint(JOYSTICK_IN_EPADDR);
  // ASIS wait implemented here, so we are not busy waiting
  if(asis_wc>0){
    PORTD = ~PORTD;//Flash LED regularly to indicate we are waiting
    if(asis_wc<ASIS_WAIT_PERIOD){
      _delay_ms(ASIS_WAIT_PERIOD);
      asis_wc = 0;
    }else{
      _delay_ms(ASIS_WAIT_PERIOD);
      asis_wc -= ASIS_WAIT_PERIOD;
    }
  }

  if (Endpoint_IsINReady()) {//If we are not waiting, send data
    if(!asis_done && asis_wc == 0){
      // Create next report
		  USB_JoystickReport_Input_t JoystickInputData;
      GetNextReport(&JoystickInputData);
      // Write the report to the endpoint
      while(Endpoint_Write_Stream_LE(&JoystickInputData, sizeof(JoystickInputData), NULL) != ENDPOINT_RWSTREAM_NoError);
    }
    //Regardless of a report was sent or not, clear the in endpoint
		Endpoint_ClearIN();
	}

  //If we are done, perform LED blinking task to indicate
  if(asis_done && !asis_overflow){
    set_led(1);
    _delay_ms(250);
    set_led(0);
    _delay_ms(3000);
  }

}

// Prepare the next report for the host.
void GetNextReport(USB_JoystickReport_Input_t* const ReportData) {

	// Repeat ECHOES times the last report
	if (echoes > 0)
	{
		memcpy(ReportData, &last_report, sizeof(USB_JoystickReport_Input_t));
		echoes--;
		return;
	}

  // Let ASIS fill the packet
  asis_sys_cycle(&packet);
  //Overflow protection
  asis_sys_ovfl(&asis_overflow);
  if(asis_overflow){
    return;
  }

  if(packet.exit){
    asis_wc = 0;
    asis_done = true;
    return;
  }

  asis_wc = packet.wait;

  // Process ASIS packet
  ReportData->Button = packet.button;
  ReportData->HAT    = packet.hat;
  ReportData->LX     = (packet.stick_x >> 8) & 0xFF;
  ReportData->LY     = (packet.stick_y >> 8) & 0xFF;
  ReportData->RX     = (packet.stick_x & 0xFF);
  ReportData->RY     = (packet.stick_y & 0xFF);
  ReportData->VendorSpec = 0;

	// Prepare to echo this report
	memcpy(&last_report, ReportData, sizeof(USB_JoystickReport_Input_t));
	echoes = ECHOES;

}
